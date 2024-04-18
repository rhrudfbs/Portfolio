////////////////////////////////////////////////////////////////
// 과제명: Two Elevators
// 과제개요: 두 개의 엘리베이터가 있고 출발층과 목표층을 설정하여
// 엘리베이터를 유기적으로 운행할 수 있게 하는 시스템을 구축한다
// 사용한 하드웨어(기능): GPIO, SW, LED, LCD, EXEPTION
// 제출일: 2023-06-08
// 제출자 클래스: 수요일반
// 학번: 2019132003
// 이름: 고경륜
//////////////////////////////////////////////////////////////////


#include "stm32f4xx.h"
#include "GLCD.h"   //LCD를 사용하기 위해 헤더파일 추가
#include "FRAM.h" //FRAM을 사용하기 위해 헤더파일 추가
#include <string.h> //문자열 비교하기 위해 헤더파일 추가

void EXTI_INIT();
void GPIO_INIT();
uint16_t KEY_Scan(void);
void BEEP(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

void Set_Lcd(); //전역변수를 사용하여 LCD를 그려내는 함수

//전역 변수에 넣어줄 데이터들을 보기 쉽게 사용하기 위해 초기화
char* Left_Elevator = "L-E"; //왼쪽 엘리베이터
char* Right_Elevator = "R-E"; //오른쪽 엘리베이터
char Stop = 'S'; //엘레베이터 상태 : Stop
char Up = 'U'; //엘레베이터 상태 : Up
char Down = 'D'; //엘레베이터 상태 : Down
char* FL = "FL"; //엘리베이터 모드 : 층 선택 모드
char* EX = "EX"; //엘레베이터 모드 : 실행 모드
char* HD = "HD"; //엘리베이터 모드 : 중단 모드

//함수에서 다른 매개변수를 주지 않아도 동작할 수 있도록 전역변수 선언
char* Select_Elevator = "L-E"; //동작 모드 때 사용할 엘리베이터 변수
char* Select_Mode = "FL"; //현재 모드를 저장할 변수
char Select_State = 'S'; //동작 모드 때 사용할 엘리베이터의 상태를 저장하는 변수
uint8_t Left_Floor = 1; //왼쪽 엘리베이터 층 수를 저장할 변수, 초기화 1
uint8_t Right_Floor = 1; //오른쪽 엘리베이터 층 수를 저장할 변수, 초기화 1
uint8_t Cur_Floor = 1; //출발층 층 수를 저장할 변수, 초기화 1
uint8_t Des_Floor = 1; //목표층 층수를 저장할 변수, 초기화 1

int main()
{
    LCD_Init(); //LCD를 사용하기 위한 초기화 작업 함수
    GPIO_INIT(); //GPIO를 사용하기 위한 초기화 작업 함수
    EXTI_INIT(); //EXTI를 사용하기 위한 초기화 작업 함수

    Fram_Init(); //Fram을 사용하기 위한 초기화 작업 함수(H/W)
    Fram_Status_Config(); //Fram S/W 초기화

    GPIOG->ODR &= ~0x00FF; //시작, LED0~7 OFF하고 시작
    GPIOG->ODR |= 0x0080; //처음 층 선택 모드, LED7 ON

    Left_Floor = Fram_Read(2023); //왼쪽 엘레베이터 Fram2023번지에 저장된 값으로 초기화
    Right_Floor = Fram_Read(2024); //오른쪽 엘레베이터 Fram2023번지에 저장된 값으로 초기화
    Cur_Floor = Left_Floor; //출발층 Fram2023번지에 저장된 값으로 초기화
    Des_Floor = Right_Floor; //목표층 Fram2023번지에 저장된 값으로 초기화

    //Fram 2023, 2024 주소에 잘못된 데이터값이 있을 때 모두 1로 초기화 해주는 조건 설정
    if (!(Left_Floor >= 1 && Left_Floor <= 6 && Right_Floor >= 1 && Right_Floor <= 6))
    {
        Left_Floor = 1;
        Right_Floor = 1;
        Cur_Floor = 1;
        Des_Floor = 1;
    }


    Set_Lcd(); //초기 조건 설정 후 Lcd 출력

    while (1)
    {
        //층선택 모드진입
        if (strcmp(Select_Mode, FL) != 0)//층선택 모드로 변경되어 있는지 확인
        {
            //안되어 있으면
            Select_Mode = FL; //층선택 모드로 변경
            Set_Lcd(); //변경 후 조건으로 LCD 출력
            GPIOG->ODR &= ~0x00FF; //층 선택 모드, 다른 LED 다 끄고
            GPIOG->ODR |= 0x0080; //LED7만 키기
        }

        switch (KEY_Scan())
        {
        case 0xFD00: //SW1 눌렀을 때
            Cur_Floor++; //출발층 1씩 증가
            if (Cur_Floor == 7 || Cur_Floor == 0) //7로 넘어갔을 때 
            {
                Cur_Floor = 1; //다시 1로 되돌아 오도록
            }

            BEEP(); //부저 1회

            GPIOG->ODR |= 0x0002; //LED1 ON
            GPIOG->ODR &= ~0x0004; //LED2 OFF

            Set_Lcd(); //설정된 조건으로 LCD 출력

            break; //탈출
        case 0xFB00: //SW2 눌렀을 때
            Des_Floor++; //목표층 1씩 증가
            if (Des_Floor == 7 || Des_Floor == 0) //7로 넘어갔을 때
            {
                Des_Floor = 1;//다시 1로 되돌아 오도록
            }

            BEEP();//부저 1회

            GPIOG->ODR |= 0x0004;//LED2 ON
            GPIOG->ODR &= ~0x0002;//LED1 OFF

            Set_Lcd();//설정된 조건으로 LCD 출력

            break;//탈출
        }
    }
}

void EXTI_INIT()
{
    RCC->AHB1ENR |= 0x00000080; //EXTI로 사용할 GPIOH Enable
    RCC->APB2ENR |= 0x00004000; //SYSCFG Enable

    GPIOH->MODER &= ~0xC03F0000; //EXTI8, 15를 사용하기 위해 PH8, PH15 Input 모드 설정

    SYSCFG->EXTICR[2] &= ~0x000F;//EXTI8을 PH로 사용하기 위해 0bxxxx xxxx xxxx 0000 으로 초기화 후
    SYSCFG->EXTICR[2] |= 0x0007;//EXTI8을 PH로 사용하기 위해 0bxxxx xxxx xxxx 0111 설정

    SYSCFG->EXTICR[3] &= ~0xF000; //EXTI15을 PH로 사용하기 위해 0b0000 xxxx xxxx xxxx 으로 초기화 후
    SYSCFG->EXTICR[3] |= 0x7000;//EXTI15을 PH로 사용하기 위해 0b0111 xxxx xxxx xxxx 설정

    EXTI->FTSR |= 0x00000100; //EXTI8 Falling Edge에 실행되도록 설정

    EXTI->FTSR |= 0x00008000; //EXTI15 Falling Edge에 실행되도록 설정

    EXTI->IMR |= 0x00000100; //EXTI 마스크 없애주기 위해 8번 비트에 1 설정

    NVIC->ISER[0] |= 1 << 23; //EXTI9_5을 사용하기 위해 벡터 테이블 23번 지정
    NVIC->ISER[1] |= 1 << (40 - 32); //EXTI15_10을 사용하기 위해 벡터 테이블 40번 지정

    SCB->AIRCR &= ~0x00000700; //우선순위 결정할 때 NVIC_PRIORITGROUP_4 사용하기 위해 설정

    NVIC->IP[23] = 0x2 << 4; //벡터테이블 23번 우선순위 2로 설정

    NVIC->IP[40] = 0x1 << 4; //벡터테이블 40번 우선순위 1로 설정
}

void GPIO_INIT()
{
    RCC->AHB1ENR |= 0x00000040; //GPIOG -> LED
    GPIOG->MODER &= ~0x0000FFFF; //GPIOG 0 ~ 7 설정을 위해 0으로 초기화
    GPIOG->MODER |= 0x00005555; //GPIOG 0 ~ 7 LED OUTPUT Mode
    GPIOG->OTYPER &= ~0x00ff; //GPIOG0~7 Push-Pull 타입으로 설정
    GPIOG->OSPEEDR |= 0x00005555; //GPIOG0~7 medium speed로 설정

    RCC->AHB1ENR |= 0x00000080; //GPIOH -> SW
    GPIOH->MODER &= ~0xC03F0000; //GPIO 8,9,10,15 SW INPUT Mode
    GPIOH->PUPDR &= ~0xC03F0000; //no-pull-up-down으로 설정

    RCC->AHB1ENR |= 0x00000020;	//GPIOF -> BUZZER
    GPIOF->MODER &= ~0x000C0000; //GPIOF 9 설정을 위해 0으로 초기화
    GPIOF->MODER |= 0x00040000; //GPIOF 9 BUZZER OUTPUT Mode
    GPIOF->OTYPER &= ~0x0200; //GPIOF 0  Push-Pull 타입으로 설정
    GPIOF->OSPEEDR |= 0x00040000;//GPIOF 0 medium speed로 설정
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

void Set_Lcd()
{
    LCD_Clear(RGB_WHITE); // 화면 흰 색으로 클리어
    LCD_SetFont(&Gulim8); //굴림체 8 사용
    LCD_SetBackColor(RGB_WHITE); //글씨 배경 흰 색 설정
    LCD_SetTextColor(RGB_BLACK); //글씨 검정색 설정
    LCD_DisplayText(0, 0, "MC-Elevator(GGR)");// 제목 텍스트 출력
    LCD_DisplayChar(6, 9, '>'); //이동방향 출력
    LCD_SetTextColor(RGB_RED);//글씨 빨간색 설정
    LCD_DrawText(68, 25, Select_Mode); //Select_Mode 변수에 저장되어 있는 모드값 출력
    LCD_DisplayChar(5, 9, Select_State); //Select_State 변수에 저장되어 있는 엘레베이터 상태값 출력
    LCD_DisplayChar(6, 8, Cur_Floor + 48); //정수형으로 되어 있는 출발층 정보 48을 더해 아스키코드값으로 변경해 출력
    LCD_DisplayChar(6, 10, Des_Floor + 48);//정수형으로 되어 있는 목표층 정보 48을 더해 아스키코드값으로 변경해 출력
    if (strcmp(Select_Elevator, "L-E") == 0) //왼쪽 엘레베이터가 선택되어 있으면
    {
        LCD_SetTextColor(RGB_BLUE); //글씨 파란색 설정
    }
    else if (strcmp(Select_Elevator, "R-E") == 0) //오른쪽 엘레베이터가 선택되어 있으면
    {
        LCD_SetTextColor(RGB_GREEN); //글씨 초록색 설정
    }
    LCD_DisplayText(4, 8, Select_Elevator); //선택된 엘레베이터를 출력
    LCD_SetTextColor(RGB_BLUE); //글씨 파란색 설정
    for (uint8_t i = 1; i <= 6; i++)
    {
        LCD_DisplayChar(8 - i, 4, i + 48); //왼쪽 엘레베이터 막대 옆 숫자 표시
    }
    LCD_SetBrushColor(RGB_BLUE); //브러시 파란색 설정
    for (uint8_t i = 1; i <= Left_Floor; i++) //왼쪽 엘레베이터 현재층에 따라
    {
        LCD_DrawFillRect(22, 26 + (13 * (6 - i)), 9, 13); //왼쪽 엘레베이터 막대 출력
    }
    LCD_SetTextColor(RGB_GREEN); // 글씨 초록색 변경
    for (uint8_t i = 1; i <= 6; i++)
    {
        LCD_DisplayChar(8 - i, 14, i + 48); //오른쪽 엘레베이터 막대 옆 숫자 표시
    }
    LCD_SetBrushColor(RGB_GREEN); //브러쉬 초록색 설정
    for (uint8_t i = 1; i <= Right_Floor; i++) //오른쪽 엘레베이터 현재층에 따라
    {
        LCD_DrawFillRect(121, 26 + (13 * (6 - i)), 9, 13); //오른쪽 엘레베이터 막대 출력
    }
}

void EXTI9_5_IRQHandler(void) //실행모드 EXTI8 사용하기 위한 인터럽트 핸들러
{
    if (EXTI->PR & 0x00000100) //EXTI8이면
    {
        EXTI->PR |= 0x00000100; //EXTI->PR 1 넣어줘서 다시 초기화

        EXTI->IMR |= 0x00008000; //EXTI15 홀드 모드를 사용할 수 있게 마스크 해제

        GPIOG->ODR &= ~0x00C7; //LED0 빼고 다 끄기
        GPIOG->ODR |= 0x0001; //LED0만 키기

        Select_Mode = EX; //실행 모드로 변경

        BEEP(); //BUZZER 1회

        uint8_t Dif_Left = abs(Cur_Floor - Left_Floor); //출발층과 왼쪽 엘레베이터 현재층 차이 확인
        uint8_t Dif_Right = abs(Cur_Floor - Right_Floor);//출발층과 오른쪽 엘레베이터 현재층 차이 확인

        if (Dif_Left <= Dif_Right)//출발층과 왼쪽 엘레베이터 현재층 차이가 더 작다면
        {
            Select_Elevator = Left_Elevator;//왼쪽 엘레베이터 선택
            if (Cur_Floor - Left_Floor > 0) //출발층이 현재층보다 높으면
            {
                Select_State = Up; //엘레베이터 올라가도록 상태 설정
                Set_Lcd(); //변경된 조건으로 출력
                while (Left_Floor < Cur_Floor) //출발층에 도달할 때까지
                {
                    DelayMS(500);
                    Left_Floor++; //현재층 1씩 증가하면서
                    Set_Lcd();  //변경된 조건으로 출력
                }
                DelayMS(500);
                Select_State = Stop; // 출발층 도달 시 엘레베이터 상태 멈춤
                Set_Lcd(); //변경된 조건으로 출력
                DelayMS(500);
            }
            else if (Cur_Floor - Left_Floor < 0)//출발층이 현재층보다 낮으면
            {
                Select_State = Down; //엘레베이터 내려가도록 상태 설정
                Set_Lcd(); //변경된 조건으로 출력
                while (Left_Floor > Cur_Floor)//출발층에 도달할 때까지
                {
                    DelayMS(500);
                    Left_Floor--;//현재층 1씩 감소하면서
                    Set_Lcd();//변경된 조건으로 출력
                }
                DelayMS(500);
                Select_State = Stop;// 출발층 도달 시 엘레베이터 상태 멈춤
                Set_Lcd(); //변경된 조건으로 출력
                DelayMS(500);
            }
        }
        else if (Dif_Left > Dif_Right)//출발층과 오른쪽 엘레베이터 현재층 차이가 더 작다면
        {
            Select_Elevator = Right_Elevator;//오른쪽 엘레베이터 선택
            if (Cur_Floor - Right_Floor > 0)//출발층이 현재층보다 높으면
            {
                Select_State = Up;//엘레베이터 올라가도록 상태 설정
                Set_Lcd();//변경된 조건으로 출력
                while (Right_Floor < Cur_Floor)//출발층에 도달할 때까지
                {
                    DelayMS(500);
                    Right_Floor++;//현재층 1씩 증가하면서
                    Set_Lcd();//변경된 조건으로 출력
                }
                DelayMS(500);
                Select_State = Stop;// 출발층 도달 시 엘레베이터 상태 멈춤
                Set_Lcd(); //변경된 조건으로 출력
                DelayMS(500);
            }
            else if (Cur_Floor - Right_Floor < 0)//출발층이 현재층보다 낮으면
            {
                Select_State = Down;//엘레베이터 내려가도록 상태 설정
                Set_Lcd();//변경된 조건으로 출력
                while (Right_Floor > Cur_Floor)//출발층에 도달할 때까지
                {
                    DelayMS(500);
                    Right_Floor--;//현재층 1씩 감소하면서
                    Set_Lcd();//변경된 조건으로 출력
                }
                DelayMS(500);
                Select_State = Stop;// 출발층 도달 시 엘레베이터 상태 멈춤
                Set_Lcd();//변경된 조건으로 출력
                DelayMS(500);
            }
        }


        if (Cur_Floor < Des_Floor) //출발층이 목표층보다 낮으면
        {
            Select_State = Up; //엘레베이터 올라가도록 상태 설정
            Set_Lcd();//변경된 조건으로 출력
            if (strcmp(Select_Elevator, "L-E") == 0)//왼쪽 엘레베이터가 선택되어 있으면
            {
                while (Left_Floor < Des_Floor) //현재층이 목표층에 도달할 때까지
                {
                    DelayMS(500);
                    Left_Floor++; //현재층 1씩 증가
                    Set_Lcd();//변경된 조건으로 출력
                }
            }
            else if (strcmp(Select_Elevator, "R-E") == 0)//오른쪽 엘레베이터가 선택되어 있으면
            {
                while (Right_Floor < Des_Floor) //현재층이 목표층에 도달할 때까지
                {
                    DelayMS(500);
                    Right_Floor++; //현재층 1씩 증가
                    Set_Lcd();//변경된 조건으로 출력
                }
            }
            DelayMS(500);
            Select_State = Stop;//목표층 도달 후 엘레베이터 상태 멈춤
            Set_Lcd();//변경된 조건으로 출력
            DelayMS(500);
        }
        else if (Cur_Floor > Des_Floor) //목표층이 출발층보다 낮으면
        {
            Select_State = Down; //엘레베이터 상태 내려감
            Set_Lcd();//변경된 조건으로 출력
            if (strcmp(Select_Elevator, "L-E") == 0) //왼쪽 엘레베이터 선택되어 있으면
            {
                while (Left_Floor > Des_Floor) //현재층이 목표층에 도달할 때까지
                {
                    DelayMS(500);
                    Left_Floor--;//1씩 감소
                    Set_Lcd();//변경된 조건으로 출력
                }
            }
            else if (strcmp(Select_Elevator, "R-E") == 0) //오른쪽 엘레베이터 선택되어 있으면
            {
                while (Right_Floor > Des_Floor) //현재층이 목표층에 도달할 때까지
                {
                    DelayMS(500);
                    Right_Floor--; //1씩 감소
                    Set_Lcd();//변경된 조건으로 출력
                }
            }
            DelayMS(500);
            Select_State = Stop;//목표 층 도달 후 엘레베이터 상태 멈춤
            Set_Lcd();//변경된 조건으로 출력
            DelayMS(500);
        }
        else if (Cur_Floor == Des_Floor) //목표층, 출발층이 같을 경우
        {
            Set_Lcd();//변경된 조건으로 출력
            DelayMS(1000);//1초 대기
        }

        Fram_Write(2023, Left_Floor); //도달한 왼쪽 엘레베이터 층수 Fram 2023번지에 저장
        Fram_Write(2024, Right_Floor); //도달한 오른쪽 엘레베이터 층수 Fram 2024번지에 저장

        //부저 3회
        BEEP();
        DelayMS(250);
        BEEP();
        DelayMS(250);
        BEEP();

        //실행모드 아니면 홀드모드 사용하지 못하게 EXTI15번 마스크
        EXTI->IMR &= ~0x00008000;
    }
}

void EXTI15_10_IRQHandler(void) //홀드 모드
{
    if (EXTI->PR & 0x8000) //EXTI15 이면
    {
        EXTI->PR |= 0x8000; //EXTI->PR 15번 1로 초기화
        GPIOG->ODR &= ~0x00C1; //LED 6번만 키기 위해 LED들 OFF
        GPIOG->ODR |= 0x0040; //LED6 ON
        Select_Mode = HD; //엘레베이터 모드 홀드모드
        Set_Lcd();//변경된 조건으로 출력
        for (uint8_t i = 0; i < 10; i++) //0.5초마다 부저 1회 10번 반복 -> 5초 지연
        {
            DelayMS(500);
            BEEP();
        }
        Select_Mode = EX; //엘레베이터 모드 실행모드로 변경
        Set_Lcd();//변경된 조건으로 출력
        GPIOG->ODR &= ~0x00C1; //실행모드에 맞는 LED 키기 위해 다른 LED들 OFF
        GPIOG->ODR |= 0x0001; //LED1 ON
    }
}