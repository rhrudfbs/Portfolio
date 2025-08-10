////////////////////////////////////////////////////////////////
// 과제명: 이진 연산기
// 과제개요: 이진(2비트) 연산을 하는 계산기 프로그램 제작
// 
// 사용한 하드웨어(기능): GPIO, SW, LED, LCD, JOY-STICK, EXEPTION
// 제출일: 2023-06-10
// 제출자 클래스: 수요일반
// 학번: 2019132003
// 이름: 고경륜
//////////////////////////////////////////////////////////////////


#include "stm32F4xx.h"
#include "GLCD.h" //LCD를 사용하기 위한 헤더 파일
#include "FRAM.h" //Fram을 사용하기 위한 헤더 파일

void GPIO_INIT(); //GPIO 초기화 함수
void Set_Lcd(); //설정한 값으로 LCD를 사용하기 위한 함수
void EXTI_INIT(); //인터럽트(EXEPTION 사용하기 위한 초기화 함수)

uint16_t KEY_Scan(void); //Key 값을 받아오기 위한 함수
void BEEP(void); //부저 1회 울리기 위한 함수
void DelayMS(unsigned short wMS); //시간 지연 함수
void DelayUS(unsigned short wUS); //시간 지연 함수

uint8_t A_1 = 0; //A의 MSB 0으로 초기화
uint8_t A_0 = 0; //A의 LSB 0으로 초기화
uint8_t B_1 = 0; //B의 MSB 0으로 초기화
uint8_t B_0 = 0; //B의 LSB 0으로 초기화
uint8_t C_3 = 0; //C의 MSB 0으로 초기화
uint8_t C_2 = 0; //C의 MSB 다음 자리수 0으로 초기화
uint8_t C_1 = 0; //C의 MSB 다음 다음 자리수 0으로 초기화
uint8_t C_0 = 0; //C의 LSB 0으로 초기화

uint8_t Aopnd; //A의 각 자리수로 계산해 10진수 값으로 변환하여 저장하는 변수
uint8_t Bopnd; //B의 각 자리수로 계산해 10진수 값으로 변환하여 저장하는 변수
uint8_t Cresult; //C의 각 자리수로 계산해 10진수 값으로 변환하여 저장하는 변수

char* Row_Mode = "+1"; //설정한 문자열을 사용하기 위한 문자열 변수(연속 모드O)
char* InRow_Mode = "+0"; //설정한 문자열을 사용하기 위한 문자열 변수(연속 모드X)

char Result_Sign = '+'; //결과 값의 부호를 저장하기 위한 변수
char Operator = '+'; //연산자를 저장하기 위한 변수
char* Mode = NULL; //연속 모드인지 아닌지를 저장하기 위한 변수

uint8_t flag; //연속모드에서 무한 반복하기 위해 설정해두는 플래그 변수

int main()
{
    LCD_Init(); //LCD를 사용하기 위한 초기화 작업 함수
    Fram_Init(); //Fram을 사용하기 위한 초기화 작업 함수(H/W)
    Fram_Status_Config(); //Fram S/W 초기화

    GPIO_INIT(); //GPIO를 사용하기 위한 초기화 작업 함수
    EXTI_INIT(); //EXTI를 사용하기 위한 초기화 작업 함수

    Aopnd = (A_1 << 1) + A_0; //A의 각 자리수로 10진수 수로 변환 해 저장
    Bopnd = (B_1 << 1) + B_0; //B의 각 자리수로 10진수 수로 변환 해 저장

    Operator = Fram_Read(530); //연산자를 Fram 530 주소로 부터 가져와 연산자 변수에 저장
    Cresult = Fram_Read(531); //결과값을 Fram 531 주소로 부터 가져와 결과값 변수에 저장
    Result_Sign = Fram_Read(529); //결과값 부호를 Fram 529 주소로 부터 가져와 결과값 부호 변수에 저장

    if (Operator != '+' && Operator != '-' && Operator != 'x' && Operator != '&' && Operator != '|' && Operator != '^') //Fram에서 불러온 데이터가 유효한 연산자가 아니라면
    {
        Operator = '+'; //'+'로 초기화
    }

    if (Cresult > 15) //Fram에서 불러온 데이터가 유효한 결과값이 아니라면
    {
        Cresult = 0; //0으로 초기화
    }

    if (Result_Sign != '+' && Result_Sign != '-') //Fram에서 불러온 데이터가 유효한 결과값 부호가 아니라면
    {
        Result_Sign = '+'; //'+'로 초기화
    }

    //10진수 수로 되어 있는 결과값 변수를 이용해 C의 각 자릿수에 맞는 수 저장
    C_3 = (Cresult & 0x8) >> 3;
    C_2 = (Cresult & 0x4) >> 2;
    C_1 = (Cresult & 0x2) >> 1;
    C_0 = (Cresult & 0x1);

    Mode = InRow_Mode; //모드를 연속 모드X로 초기화

    Set_Lcd(); //설정한 값으로 LCD 출력

    while (1) //무한 반복
    {
        switch (KEY_Scan()) //KEY_Scan()함수로 부터 받은 데이터를 인자로
        {
        case 0xFB00: //SW2가 눌리면
            A_1 ^= 1; //A의 MSB 토글
            Aopnd = (A_1 << 1) + A_0; //A를 10진수 수로 바꾸어 저장
            BEEP(); //부저 1회
            Set_Lcd(); //설정한 값으로 LCD 출력
            break;
        case 0xF700: //SW3이 눌리면
            A_0 ^= 1; //A의 LSB 토글
            Aopnd = (A_1 << 1) + A_0; //A를 10진수 수로 바꾸어 저장
            BEEP(); //부저 1회
            Set_Lcd(); //설정한 값으로 LCD 출력
            break;
        case 0xEF00: //SW4가 눌리면
            B_1 ^= 1; //B의 MSB 토글
            Bopnd = (B_1 << 1) + B_0; //B를 10진수 수로 바꾸어 저장
            BEEP(); //부저 1회
            Set_Lcd(); //설정한 값으로 LCD 출력
            break;
        case 0xDF00: //SW5가 눌리면
            B_0 ^= 1; //B의 LSB 토글
            Bopnd = (B_1 << 1) + B_0; //B를 10진수 수로 바꾸어 저장
            BEEP(); //부저 1회
            Set_Lcd(); //설정한 값으로 LCD 출력
            break;
        }
    }
}

uint8_t key_flag = 0;
uint16_t KEY_Scan(void)	// input key SW0 - SW7 
{
    uint16_t key;
    key = GPIOH->IDR & 0xFF00;	// any key pressed ?
    if (key == 0xFF00)		// if no key, check key off
    {
        if (key_flag == 0)
            return key;
        else
        {
            DelayMS(10);
            key_flag = 0;
            return key;
        }
    }
    else				// if key input, check continuous key
    {
        if (key_flag != 0)	// if continuous key, treat as no key input
            return 0xFF00;
        else			// if new key,delay for debounce
        {
            key_flag = 1;
            DelayMS(10);
            return key;
        }
    }
}

void BEEP(void)			/* beep for 30 ms */
{
    GPIOF->ODR |= 0x0200;	// PF9 'H' Buzzer on
    DelayMS(30);			// Delay 30 ms
    GPIOF->ODR &= ~0x0200;	// PF9 'L' Buzzer off
}

void DelayMS(unsigned short wMS)
{
    register unsigned short i;
    for (i = 0; i < wMS; i++)
        DelayUS(1000);	// 1000us => 1ms
}

void DelayUS(unsigned short wUS)
{
    volatile int Dly = (int)wUS * 17;
    for (; Dly; Dly--);
}

void GPIO_INIT() //GPIO 초기화 함수
{
    RCC->AHB1ENR |= 0x000001E0; //GPIO F, G, H, I Enable

    //LED7 Enable
    GPIOG->MODER &= ~0x0000C000; //PG 7 만 output 모드로 설정해 주기 위해 0으로 초기화
    GPIOG->MODER |= 0x00004000; //PG 7 만 output 모드로 설정

    GPIOG->OTYPER &= ~0x0080; //PG 7 Push-Pull 모드 설정

    GPIOG->OSPEEDR &= ~0x0000C000; //PG 7 Medium speed로 설정해 주기 위해 0으로 초기화
    GPIOG->OSPEEDR |= 0x00004000; //PG 7 Medium speed로 설정

    //SW 1~6 Enable
    GPIOH->MODER &= ~0x3FFC0000; //PH 1 ~ 6 Input mode 설정

    GPIOH->PUPDR &= ~0x3FFC0000; //PH 1 ~ 6 No pull-up, pull-down

    //JoyStick Up, Right Enable
    GPIOI->MODER &= ~0x00033000; //PI 6, 8 Input mode 설정

    GPIOI->PUPDR &= ~0x00033000; //PI 6, 8 No pull-up, pull-down

    //BUZZER Enable
    GPIOF->MODER &= ~0x000C0000; //PF 9만 output 모드로 설정해 주기 위해 0으로 초기화
    GPIOF->MODER |= 0x00040000; //PF 9만 output 모드로 설정

    GPIOF->OTYPER &= ~0x0200; //PF 9 Push-Pull 모드 설정

    GPIOF->OSPEEDR &= ~0x000C0000; //PF 9 Medium speed로 설정해 주기 위해 0으로 초기화
    GPIOF->OSPEEDR |= 0x00040000; //PF 9 Medium speed로 설정
}

void EXTI_INIT() //EXTI 초기화 함수
{
    RCC->AHB1ENR |= 0x00000180; //EXTI로 사용하기 위한 GPIO H, I Enable
    RCC->APB2ENR |= 0x00004000; //SYSCFG Enable

    GPIOH->MODER &= ~0x3FFC0000; //PH 1 ~ 6 Input mode 설정
    GPIOI->MODER &= ~0x00033000;//PI 6, 8 Input mode 설정

    SYSCFG->EXTICR[1] &= ~0x0F00; //PI 6을 EXTI pin으로 사용하기 위해 EXTI6를 0b 0000으로 초기화
    SYSCFG->EXTICR[1] |= 0x0800; //PI 6을 EXTI pin으로 사용하기 위해 I -> 0b 1000으로 초기화

    SYSCFG->EXTICR[2] &= ~0x00FF; //PI 8, PH 9를 EXTI pin으로 사용하기 위해 EXTI8, EXTI9를 0b 0000으로 초기화
    SYSCFG->EXTICR[2] |= 0x0078; //PI 8, PH 9를 EXTI pin으로 사용하기 위해 H -> 0b 0111, I -> 0b 1000으로 초기화

    SYSCFG->EXTICR[3] &= ~0x0F00; //PH 14를 EXTI pin으로 사용하기 위해 EXTI14를 0b 0000으로 초기화
    SYSCFG->EXTICR[3] |= 0x0700; //PH 14를 EXTI pin으로 사용하기 위해 H -> 0b 0111로 초기화

    EXTI->FTSR |= 0x00004340; //EXTI 6, 8, 9, 14를 Falling Edge 입력 시로 사용하기 위해 초기화
    EXTI->IMR |= 0x00004340; //EXTI 6, 8, 9, 14 마스크 해제

    NVIC->ISER[0] |= 1 << 23; //EXTI9_5_ 벡터 테이블 번호 자리에 Interrupt Enable
    NVIC->ISER[1] |= 1 << (40 - 32); //EXTI15_10_ 벡터 테이블 번호 자리에 Interrupt Enable

    SCB->AIRCR &= ~0x00000700; //우선순위 결정할 때 NVIC_PRIORITGROUP_4 사용하기 위해 설정

    NVIC->IP[23] = 0x2 << 4; //벡터테이블 23번 우선순위 2로 설정

    NVIC->IP[40] = 0x1 << 4; //벡터테이블 23번 우선순위 2로 설정
}

void Set_Lcd()
{
    LCD_Clear(RGB_WHITE); //흰 색으로 LCD 클리어
    LCD_SetFont(&Gulim8); //폰트 굴림체8 사용
    LCD_SetPenColor(RGB_GREEN); //펜 색 초록색 설정
    LCD_SetTextColor(RGB_BLACK); //문자 색 검정색 설정
    LCD_DrawRectangle(67, 14, 26, 100); //중앙에 사각형 그리기

    LCD_SetPenColor(RGB_BLUE); //펜 색 파란색 설정

    //중앙 사각형 양 옆 선 그리기
    LCD_DrawHorLine(57, 21, 10);
    LCD_DrawHorLine(57, 41, 10);
    LCD_DrawHorLine(57, 86, 10);
    LCD_DrawHorLine(57, 106, 10);

    LCD_DrawHorLine(94, 22, 9);
    LCD_DrawHorLine(94, 47, 9);
    LCD_DrawHorLine(94, 67, 9);
    LCD_DrawHorLine(94, 87, 9);
    LCD_DrawHorLine(94, 107, 9);

    LCD_SetPenColor(RGB_BLACK); //펜 색 바꾸기
    LCD_SetBrushColor(RGB_YELLOW); //브러시 색 노란색 설정
    LCD_SetBackColor(RGB_YELLOW); //문자 배경 색 노란색 설정

    LCD_DrawFillRect(42, 14, 15, 15); //A MSB 사각형 색 채우기
    LCD_DrawRectangle(42, 14, 15, 15); //A MSB 사각형 테두리 그리기
    LCD_DrawChar(46, 16, A_1 + 48); //A MSB 사각형 안에 A MSB에 맞는 변수에 저장된 데이터 출력

    LCD_DrawFillRect(42, 36, 15, 15); //A LSB 사각형 색 채우기
    LCD_DrawRectangle(42, 36, 15, 15); //A LSB 사각형 테두리 그리기
    LCD_DrawChar(46, 38, A_0 + 48); //A LSB 사각형 안에 A LSB에 맞는 변수에 저장된 데이터 출력

    LCD_DrawFillRect(42, 79, 15, 15); //B MSB 사각형 색 채우기
    LCD_DrawRectangle(42, 79, 15, 15); //B MSB 사각형 테두리 그리기
    LCD_DrawChar(46, 81, B_1 + 48); //B MSB 사각형 안에 B MSB에 맞는 변수에 저장된 데이터 출력

    LCD_DrawFillRect(42, 99, 15, 15); //B LSB 사각형 색 채우기
    LCD_DrawRectangle(42, 99, 15, 15); //B LSB 사각형 테두리 그리기
    LCD_DrawChar(46, 101, B_0 + 48); //B LSB 사각형 안에 B LSB에 맞는 변수에 저장된 데이터 출력


    LCD_DrawFillRect(103, 14, 15, 15); //결과값 부호 사각형 색 채우기
    LCD_DrawRectangle(103, 14, 15, 15); //결과값 부호 사각형 테두리 그리기
    LCD_DrawChar(107, 16, Result_Sign); //결과값 부호 사각형 안에 결과값 부호에 맞는 변수에 저장된 데이터 출력

    LCD_DrawFillRect(103, 40, 15, 15); //C MSB 사각형 색 채우기
    LCD_DrawRectangle(103, 40, 15, 15); //C MSB 사각형 테두리 그리기
    LCD_DrawChar(107, 42, C_3 + 48); //C MSB 사각형 안에 C MSB에 맞는 변수에 저장된 데이터 출력

    LCD_DrawFillRect(103, 60, 15, 15); //C MSB 다음 사각형 색 채우기
    LCD_DrawRectangle(103, 60, 15, 15); //C MSB 다음 사각형 테두리 그리기
    LCD_DrawChar(107, 62, C_2 + 48); //C MSB 다음 사각형 안에 C MSB 다음에 맞는 변수에 저장된 데이터 출력

    LCD_DrawFillRect(103, 80, 15, 15); //C MSB 다음 다음 사각형 색 채우기
    LCD_DrawRectangle(103, 80, 15, 15); //C MSB 다음 다음 사각형 테두리 그리기
    LCD_DrawChar(107, 82, C_1 + 48); //C MSB 다음 다음 사각형 안에 C MSB 다음 다음에 맞는 변수에 저장된 데이터 출력

    LCD_DrawFillRect(103, 100, 15, 15); //C LSB 사각형 색 채우기
    LCD_DrawRectangle(103, 100, 15, 15); //C LSB 사각형 테두리 그리기
    LCD_DrawChar(107, 102, C_0 + 48); //C LSB 사각형 안에 C LSB에 맞는 변수에 저장된 데이터 출력

    LCD_SetPenColor(RGB_GREEN); //펜 색 초록색으로 변경
    LCD_SetBackColor(RGB_WHITE); //글자 배경 흰 색으로 변경

    LCD_DrawRectangle(22, 24, 15, 15); //A 사각형 그리기
    LCD_DrawChar(26, 26, 'A'); //A 사각형 안에 A 출력

    LCD_DrawRectangle(22, 89, 15, 15); //B 사각형 그리기
    LCD_DrawChar(26, 91, 'B'); //B 사각형 안에 B 출력


    LCD_DrawRectangle(123, 70, 15, 15); //C 사각형 그리기
    LCD_DrawChar(127, 72, 'C'); //C 사각형 안에 C 출력


    LCD_SetPenColor(RGB_BLACK); //펜 색 검정색 설정
    LCD_SetBackColor(GET_RGB(255, 192, 203)); //배경 색 핑크색 설정
    LCD_SetBrushColor(GET_RGB(255, 192, 203)); //브러시 색 핑크색 설정
    LCD_DrawFillRect(72, 50, 16, 15); //연산자 사각형 색 채우기
    LCD_DrawRectangle(72, 50, 16, 15); //연산자 사각형 테두리 그리기
    LCD_DrawChar(77, 52, Operator); //연산자 사각형 안에 연산자 변수에 저장된 데이터 출력

    LCD_SetBackColor(RGB_YELLOW); //글자 배경색 노란색 설정
    LCD_SetBrushColor(RGB_YELLOW); //브러시 색 노란색 설정

    LCD_DrawFillRect(70, 94, 20, 15); //연속 모드 실행 여부 사각형 색 채우기
    LCD_DrawRectangle(70, 94, 20, 15); // 연속 모드 실행 여부 사각형 테두리 그리기
    LCD_DrawText(72, 96, Mode); // 연속 모드 실행 여부 사각형 안에 연속 모드 실행 여부 변수에 저장된 데이터 출력
}

void EXTI9_5_IRQHandler()
{
    if (EXTI->PR & 0x00000100) //EXTI8, 조이스틱 오른쪽이 입력 된 것 인식
    {
        EXTI->PR |= 0x00000100; //EXTI->PR 8번 1로 초기화
        if (Operator == '+') //현재 연산자가 '+'이면
        {
            Operator = '-'; //'-'로 변경
        }
        else if (Operator == '-') //현재 연산자가 '-'이면
        {
            Operator = 'x'; //'x'로 변경
        }
        else if (Operator == 'x') //현재 연산자가 'x'이면
        {
            Operator = '&'; //'&'로 변경
        }
        else if (Operator == '&') //현재 연산자가 '&'이면
        {
            Operator = '|'; //'|'로 변경
        }
        else if (Operator == '|') //현재 연산자가 '|'이면
        {
            Operator = '^'; //'^'로 변경
        }
        else if (Operator == '^') //현재 연산자가 '^'이면
        {
            Operator = '+'; //'+'로 변경
        }
        Fram_Write(530, Operator); //연산자 Fram 530 주소에 저장
        Fram_Write(531, Cresult); //결과값 Fram 531 주소에 저장
        Fram_Write(529, Result_Sign); //결과값 부로 Fram 529 주소에 저장
        BEEP(); //부저 1회
        Set_Lcd(); //설정한 값으로 LCD 출력
    }
    if (EXTI->PR & 0x00000200) //EXTI9, SW1 누른 것 인식
    {
        EXTI->PR |= 0x00000200;//EXTI->PR 9번 1로 초기화
        if (Operator == '+') //연산자가 더하기면
        {
            Cresult = Aopnd + Bopnd; //더해서 결과값 변수에 10진수로 저장
            Result_Sign = '+'; //부호 양수
        }
        else if (Operator == '-') //연산자가 빼기면
        {
            if (Aopnd >= Bopnd) //A가 B보다 크면
            {
                Cresult = Aopnd - Bopnd; //결과값에 그대로 빼서 저장
                Result_Sign = '+'; //부호 양수
            }
            else if (Aopnd < Bopnd) //A가 B보다 작으면
            {
                Cresult = Bopnd - Aopnd; //결과값에 반대로 빼서 양수 저장
                Result_Sign = '-'; //부호 음수로 바꿔주기
            }
        }
        else if (Operator == 'x') //연산자가 곱하기면
        {
            Cresult = Aopnd * Bopnd; //곱해서 10진수로 저장
            Result_Sign = '+'; //부호 양수
        }
        else if (Operator == '&') //And 연산자면
        {
            Cresult = Aopnd & Bopnd; //And 연산해서 10진수로 저장
            Result_Sign = '+'; //부호 양수
        }
        else if (Operator == '|') //Or 연산자면
        {
            Cresult = Aopnd | Bopnd; //Or 연산해서 10진수로 저장
            Result_Sign = '+'; //부호 양수
        }
        else if (Operator == '^') //토글 연산이면
        {
            Cresult = Aopnd ^ Bopnd; //토글 연산해서 10진수로 저장
            Result_Sign = '+'; //부호 양수
        }
        Fram_Write(530, Operator); //연산자 Fram 530 주소에 저장
        Fram_Write(531, Cresult); //결과값 Fram 531 주소에 저장
        Fram_Write(529, Result_Sign); //결과값 부호 Fram 529 주소에 저장
        
        //10진수 수로 되어 있는 결과값 변수를 이용해 C의 각 자릿수에 맞는 수 저장
        C_3 = (Cresult & 0x8) >> 3;
        C_2 = (Cresult & 0x4) >> 2;
        C_1 = (Cresult & 0x2) >> 1;
        C_0 = (Cresult & 0x1);
        BEEP(); //부저 1회
        Set_Lcd(); //설정된 값으로 LCD 출력
    }
    if (EXTI->PR & 0x00000040) //EXTI6, 조이스틱 위쪽 인식
    {
        EXTI->PR |= 0x00000040; //EXTI->PR 6번 1 입력해서 초기화
        GPIOG->ODR |= 0x0080; //LED7 출력
        BEEP(); //부저 1회
        Mode = Row_Mode; //연속모드 변경
        Result_Sign = '+'; //부호 양수
        flag = 1; //무한 반복문 실행시키기 위해 flag 변수 1로 변경
        while (flag) //flag 변수가 1일 때 동안 무한 반복
        {
            DelayMS(500); //0.5초마다
            Cresult++; //결과값 1씩 증가시키고
            //10진수 수로 되어 있는 결과값 변수를 이용해 C의 각 자릿수에 맞는 수 저장
            C_3 = (Cresult & 0x8) >> 3;
            C_2 = (Cresult & 0x4) >> 2;
            C_1 = (Cresult & 0x2) >> 1;
            C_0 = (Cresult & 0x1);
            Fram_Write(530, Operator); //연산자 Fram 530 주소에 저장
            Fram_Write(531, Cresult); //결과값 Fram 531 주소에 저장
            Fram_Write(529, Result_Sign); //결과값 부호 Fram 529 주소에 저장
            Set_Lcd(); //설정된 값으로 LCD 출력
        }
        //반복문 탈출 후
        Mode = InRow_Mode; //연속 모드X
        Set_Lcd();//설정된 값으로 LCD 출력
        //부저 3회
        BEEP();
        DelayMS(250);
        BEEP();
        DelayMS(250);
        BEEP();
        GPIOG->ODR &= ~0x0080;//LED7 OFF
    }
}

void EXTI15_10_IRQHandler()
{
    if (EXTI->PR & 0x00004000) //EXTI 14, SW6 누른 것 인식
    {
        EXTI->PR |= 0x00004000; //EXTI->PR 14번 1로 초기화
        BEEP(); //부저 1회
        DelayMS(1000); //1초 지연
        flag = 0; //플래그 변수 데이터 0으로 바꿔서 연속모드 탈출
    }
}