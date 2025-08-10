////////////////////////////////////////////////////////////////
// ������: ���� �����
// ��������: ����(2��Ʈ) ������ �ϴ� ���� ���α׷� ����
// 
// ����� �ϵ����(���): GPIO, SW, LED, LCD, JOY-STICK, EXEPTION
// ������: 2023-06-10
// ������ Ŭ����: �����Ϲ�
// �й�: 2019132003
// �̸�: ����
//////////////////////////////////////////////////////////////////


#include "stm32F4xx.h"
#include "GLCD.h" //LCD�� ����ϱ� ���� ��� ����
#include "FRAM.h" //Fram�� ����ϱ� ���� ��� ����

void GPIO_INIT(); //GPIO �ʱ�ȭ �Լ�
void Set_Lcd(); //������ ������ LCD�� ����ϱ� ���� �Լ�
void EXTI_INIT(); //���ͷ�Ʈ(EXEPTION ����ϱ� ���� �ʱ�ȭ �Լ�)

uint16_t KEY_Scan(void); //Key ���� �޾ƿ��� ���� �Լ�
void BEEP(void); //���� 1ȸ �︮�� ���� �Լ�
void DelayMS(unsigned short wMS); //�ð� ���� �Լ�
void DelayUS(unsigned short wUS); //�ð� ���� �Լ�

uint8_t A_1 = 0; //A�� MSB 0���� �ʱ�ȭ
uint8_t A_0 = 0; //A�� LSB 0���� �ʱ�ȭ
uint8_t B_1 = 0; //B�� MSB 0���� �ʱ�ȭ
uint8_t B_0 = 0; //B�� LSB 0���� �ʱ�ȭ
uint8_t C_3 = 0; //C�� MSB 0���� �ʱ�ȭ
uint8_t C_2 = 0; //C�� MSB ���� �ڸ��� 0���� �ʱ�ȭ
uint8_t C_1 = 0; //C�� MSB ���� ���� �ڸ��� 0���� �ʱ�ȭ
uint8_t C_0 = 0; //C�� LSB 0���� �ʱ�ȭ

uint8_t Aopnd; //A�� �� �ڸ����� ����� 10���� ������ ��ȯ�Ͽ� �����ϴ� ����
uint8_t Bopnd; //B�� �� �ڸ����� ����� 10���� ������ ��ȯ�Ͽ� �����ϴ� ����
uint8_t Cresult; //C�� �� �ڸ����� ����� 10���� ������ ��ȯ�Ͽ� �����ϴ� ����

char* Row_Mode = "+1"; //������ ���ڿ��� ����ϱ� ���� ���ڿ� ����(���� ���O)
char* InRow_Mode = "+0"; //������ ���ڿ��� ����ϱ� ���� ���ڿ� ����(���� ���X)

char Result_Sign = '+'; //��� ���� ��ȣ�� �����ϱ� ���� ����
char Operator = '+'; //�����ڸ� �����ϱ� ���� ����
char* Mode = NULL; //���� ������� �ƴ����� �����ϱ� ���� ����

uint8_t flag; //���Ӹ�忡�� ���� �ݺ��ϱ� ���� �����صδ� �÷��� ����

int main()
{
    LCD_Init(); //LCD�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�
    Fram_Init(); //Fram�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�(H/W)
    Fram_Status_Config(); //Fram S/W �ʱ�ȭ

    GPIO_INIT(); //GPIO�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�
    EXTI_INIT(); //EXTI�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�

    Aopnd = (A_1 << 1) + A_0; //A�� �� �ڸ����� 10���� ���� ��ȯ �� ����
    Bopnd = (B_1 << 1) + B_0; //B�� �� �ڸ����� 10���� ���� ��ȯ �� ����

    Operator = Fram_Read(530); //�����ڸ� Fram 530 �ּҷ� ���� ������ ������ ������ ����
    Cresult = Fram_Read(531); //������� Fram 531 �ּҷ� ���� ������ ����� ������ ����
    Result_Sign = Fram_Read(529); //����� ��ȣ�� Fram 529 �ּҷ� ���� ������ ����� ��ȣ ������ ����

    if (Operator != '+' && Operator != '-' && Operator != 'x' && Operator != '&' && Operator != '|' && Operator != '^') //Fram���� �ҷ��� �����Ͱ� ��ȿ�� �����ڰ� �ƴ϶��
    {
        Operator = '+'; //'+'�� �ʱ�ȭ
    }

    if (Cresult > 15) //Fram���� �ҷ��� �����Ͱ� ��ȿ�� ������� �ƴ϶��
    {
        Cresult = 0; //0���� �ʱ�ȭ
    }

    if (Result_Sign != '+' && Result_Sign != '-') //Fram���� �ҷ��� �����Ͱ� ��ȿ�� ����� ��ȣ�� �ƴ϶��
    {
        Result_Sign = '+'; //'+'�� �ʱ�ȭ
    }

    //10���� ���� �Ǿ� �ִ� ����� ������ �̿��� C�� �� �ڸ����� �´� �� ����
    C_3 = (Cresult & 0x8) >> 3;
    C_2 = (Cresult & 0x4) >> 2;
    C_1 = (Cresult & 0x2) >> 1;
    C_0 = (Cresult & 0x1);

    Mode = InRow_Mode; //��带 ���� ���X�� �ʱ�ȭ

    Set_Lcd(); //������ ������ LCD ���

    while (1) //���� �ݺ�
    {
        switch (KEY_Scan()) //KEY_Scan()�Լ��� ���� ���� �����͸� ���ڷ�
        {
        case 0xFB00: //SW2�� ������
            A_1 ^= 1; //A�� MSB ���
            Aopnd = (A_1 << 1) + A_0; //A�� 10���� ���� �ٲپ� ����
            BEEP(); //���� 1ȸ
            Set_Lcd(); //������ ������ LCD ���
            break;
        case 0xF700: //SW3�� ������
            A_0 ^= 1; //A�� LSB ���
            Aopnd = (A_1 << 1) + A_0; //A�� 10���� ���� �ٲپ� ����
            BEEP(); //���� 1ȸ
            Set_Lcd(); //������ ������ LCD ���
            break;
        case 0xEF00: //SW4�� ������
            B_1 ^= 1; //B�� MSB ���
            Bopnd = (B_1 << 1) + B_0; //B�� 10���� ���� �ٲپ� ����
            BEEP(); //���� 1ȸ
            Set_Lcd(); //������ ������ LCD ���
            break;
        case 0xDF00: //SW5�� ������
            B_0 ^= 1; //B�� LSB ���
            Bopnd = (B_1 << 1) + B_0; //B�� 10���� ���� �ٲپ� ����
            BEEP(); //���� 1ȸ
            Set_Lcd(); //������ ������ LCD ���
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

void GPIO_INIT() //GPIO �ʱ�ȭ �Լ�
{
    RCC->AHB1ENR |= 0x000001E0; //GPIO F, G, H, I Enable

    //LED7 Enable
    GPIOG->MODER &= ~0x0000C000; //PG 7 �� output ���� ������ �ֱ� ���� 0���� �ʱ�ȭ
    GPIOG->MODER |= 0x00004000; //PG 7 �� output ���� ����

    GPIOG->OTYPER &= ~0x0080; //PG 7 Push-Pull ��� ����

    GPIOG->OSPEEDR &= ~0x0000C000; //PG 7 Medium speed�� ������ �ֱ� ���� 0���� �ʱ�ȭ
    GPIOG->OSPEEDR |= 0x00004000; //PG 7 Medium speed�� ����

    //SW 1~6 Enable
    GPIOH->MODER &= ~0x3FFC0000; //PH 1 ~ 6 Input mode ����

    GPIOH->PUPDR &= ~0x3FFC0000; //PH 1 ~ 6 No pull-up, pull-down

    //JoyStick Up, Right Enable
    GPIOI->MODER &= ~0x00033000; //PI 6, 8 Input mode ����

    GPIOI->PUPDR &= ~0x00033000; //PI 6, 8 No pull-up, pull-down

    //BUZZER Enable
    GPIOF->MODER &= ~0x000C0000; //PF 9�� output ���� ������ �ֱ� ���� 0���� �ʱ�ȭ
    GPIOF->MODER |= 0x00040000; //PF 9�� output ���� ����

    GPIOF->OTYPER &= ~0x0200; //PF 9 Push-Pull ��� ����

    GPIOF->OSPEEDR &= ~0x000C0000; //PF 9 Medium speed�� ������ �ֱ� ���� 0���� �ʱ�ȭ
    GPIOF->OSPEEDR |= 0x00040000; //PF 9 Medium speed�� ����
}

void EXTI_INIT() //EXTI �ʱ�ȭ �Լ�
{
    RCC->AHB1ENR |= 0x00000180; //EXTI�� ����ϱ� ���� GPIO H, I Enable
    RCC->APB2ENR |= 0x00004000; //SYSCFG Enable

    GPIOH->MODER &= ~0x3FFC0000; //PH 1 ~ 6 Input mode ����
    GPIOI->MODER &= ~0x00033000;//PI 6, 8 Input mode ����

    SYSCFG->EXTICR[1] &= ~0x0F00; //PI 6�� EXTI pin���� ����ϱ� ���� EXTI6�� 0b 0000���� �ʱ�ȭ
    SYSCFG->EXTICR[1] |= 0x0800; //PI 6�� EXTI pin���� ����ϱ� ���� I -> 0b 1000���� �ʱ�ȭ

    SYSCFG->EXTICR[2] &= ~0x00FF; //PI 8, PH 9�� EXTI pin���� ����ϱ� ���� EXTI8, EXTI9�� 0b 0000���� �ʱ�ȭ
    SYSCFG->EXTICR[2] |= 0x0078; //PI 8, PH 9�� EXTI pin���� ����ϱ� ���� H -> 0b 0111, I -> 0b 1000���� �ʱ�ȭ

    SYSCFG->EXTICR[3] &= ~0x0F00; //PH 14�� EXTI pin���� ����ϱ� ���� EXTI14�� 0b 0000���� �ʱ�ȭ
    SYSCFG->EXTICR[3] |= 0x0700; //PH 14�� EXTI pin���� ����ϱ� ���� H -> 0b 0111�� �ʱ�ȭ

    EXTI->FTSR |= 0x00004340; //EXTI 6, 8, 9, 14�� Falling Edge �Է� �÷� ����ϱ� ���� �ʱ�ȭ
    EXTI->IMR |= 0x00004340; //EXTI 6, 8, 9, 14 ����ũ ����

    NVIC->ISER[0] |= 1 << 23; //EXTI9_5_ ���� ���̺� ��ȣ �ڸ��� Interrupt Enable
    NVIC->ISER[1] |= 1 << (40 - 32); //EXTI15_10_ ���� ���̺� ��ȣ �ڸ��� Interrupt Enable

    SCB->AIRCR &= ~0x00000700; //�켱���� ������ �� NVIC_PRIORITGROUP_4 ����ϱ� ���� ����

    NVIC->IP[23] = 0x2 << 4; //�������̺� 23�� �켱���� 2�� ����

    NVIC->IP[40] = 0x1 << 4; //�������̺� 23�� �켱���� 2�� ����
}

void Set_Lcd()
{
    LCD_Clear(RGB_WHITE); //�� ������ LCD Ŭ����
    LCD_SetFont(&Gulim8); //��Ʈ ����ü8 ���
    LCD_SetPenColor(RGB_GREEN); //�� �� �ʷϻ� ����
    LCD_SetTextColor(RGB_BLACK); //���� �� ������ ����
    LCD_DrawRectangle(67, 14, 26, 100); //�߾ӿ� �簢�� �׸���

    LCD_SetPenColor(RGB_BLUE); //�� �� �Ķ��� ����

    //�߾� �簢�� �� �� �� �׸���
    LCD_DrawHorLine(57, 21, 10);
    LCD_DrawHorLine(57, 41, 10);
    LCD_DrawHorLine(57, 86, 10);
    LCD_DrawHorLine(57, 106, 10);

    LCD_DrawHorLine(94, 22, 9);
    LCD_DrawHorLine(94, 47, 9);
    LCD_DrawHorLine(94, 67, 9);
    LCD_DrawHorLine(94, 87, 9);
    LCD_DrawHorLine(94, 107, 9);

    LCD_SetPenColor(RGB_BLACK); //�� �� �ٲٱ�
    LCD_SetBrushColor(RGB_YELLOW); //�귯�� �� ����� ����
    LCD_SetBackColor(RGB_YELLOW); //���� ��� �� ����� ����

    LCD_DrawFillRect(42, 14, 15, 15); //A MSB �簢�� �� ä���
    LCD_DrawRectangle(42, 14, 15, 15); //A MSB �簢�� �׵θ� �׸���
    LCD_DrawChar(46, 16, A_1 + 48); //A MSB �簢�� �ȿ� A MSB�� �´� ������ ����� ������ ���

    LCD_DrawFillRect(42, 36, 15, 15); //A LSB �簢�� �� ä���
    LCD_DrawRectangle(42, 36, 15, 15); //A LSB �簢�� �׵θ� �׸���
    LCD_DrawChar(46, 38, A_0 + 48); //A LSB �簢�� �ȿ� A LSB�� �´� ������ ����� ������ ���

    LCD_DrawFillRect(42, 79, 15, 15); //B MSB �簢�� �� ä���
    LCD_DrawRectangle(42, 79, 15, 15); //B MSB �簢�� �׵θ� �׸���
    LCD_DrawChar(46, 81, B_1 + 48); //B MSB �簢�� �ȿ� B MSB�� �´� ������ ����� ������ ���

    LCD_DrawFillRect(42, 99, 15, 15); //B LSB �簢�� �� ä���
    LCD_DrawRectangle(42, 99, 15, 15); //B LSB �簢�� �׵θ� �׸���
    LCD_DrawChar(46, 101, B_0 + 48); //B LSB �簢�� �ȿ� B LSB�� �´� ������ ����� ������ ���


    LCD_DrawFillRect(103, 14, 15, 15); //����� ��ȣ �簢�� �� ä���
    LCD_DrawRectangle(103, 14, 15, 15); //����� ��ȣ �簢�� �׵θ� �׸���
    LCD_DrawChar(107, 16, Result_Sign); //����� ��ȣ �簢�� �ȿ� ����� ��ȣ�� �´� ������ ����� ������ ���

    LCD_DrawFillRect(103, 40, 15, 15); //C MSB �簢�� �� ä���
    LCD_DrawRectangle(103, 40, 15, 15); //C MSB �簢�� �׵θ� �׸���
    LCD_DrawChar(107, 42, C_3 + 48); //C MSB �簢�� �ȿ� C MSB�� �´� ������ ����� ������ ���

    LCD_DrawFillRect(103, 60, 15, 15); //C MSB ���� �簢�� �� ä���
    LCD_DrawRectangle(103, 60, 15, 15); //C MSB ���� �簢�� �׵θ� �׸���
    LCD_DrawChar(107, 62, C_2 + 48); //C MSB ���� �簢�� �ȿ� C MSB ������ �´� ������ ����� ������ ���

    LCD_DrawFillRect(103, 80, 15, 15); //C MSB ���� ���� �簢�� �� ä���
    LCD_DrawRectangle(103, 80, 15, 15); //C MSB ���� ���� �簢�� �׵θ� �׸���
    LCD_DrawChar(107, 82, C_1 + 48); //C MSB ���� ���� �簢�� �ȿ� C MSB ���� ������ �´� ������ ����� ������ ���

    LCD_DrawFillRect(103, 100, 15, 15); //C LSB �簢�� �� ä���
    LCD_DrawRectangle(103, 100, 15, 15); //C LSB �簢�� �׵θ� �׸���
    LCD_DrawChar(107, 102, C_0 + 48); //C LSB �簢�� �ȿ� C LSB�� �´� ������ ����� ������ ���

    LCD_SetPenColor(RGB_GREEN); //�� �� �ʷϻ����� ����
    LCD_SetBackColor(RGB_WHITE); //���� ��� �� ������ ����

    LCD_DrawRectangle(22, 24, 15, 15); //A �簢�� �׸���
    LCD_DrawChar(26, 26, 'A'); //A �簢�� �ȿ� A ���

    LCD_DrawRectangle(22, 89, 15, 15); //B �簢�� �׸���
    LCD_DrawChar(26, 91, 'B'); //B �簢�� �ȿ� B ���


    LCD_DrawRectangle(123, 70, 15, 15); //C �簢�� �׸���
    LCD_DrawChar(127, 72, 'C'); //C �簢�� �ȿ� C ���


    LCD_SetPenColor(RGB_BLACK); //�� �� ������ ����
    LCD_SetBackColor(GET_RGB(255, 192, 203)); //��� �� ��ũ�� ����
    LCD_SetBrushColor(GET_RGB(255, 192, 203)); //�귯�� �� ��ũ�� ����
    LCD_DrawFillRect(72, 50, 16, 15); //������ �簢�� �� ä���
    LCD_DrawRectangle(72, 50, 16, 15); //������ �簢�� �׵θ� �׸���
    LCD_DrawChar(77, 52, Operator); //������ �簢�� �ȿ� ������ ������ ����� ������ ���

    LCD_SetBackColor(RGB_YELLOW); //���� ���� ����� ����
    LCD_SetBrushColor(RGB_YELLOW); //�귯�� �� ����� ����

    LCD_DrawFillRect(70, 94, 20, 15); //���� ��� ���� ���� �簢�� �� ä���
    LCD_DrawRectangle(70, 94, 20, 15); // ���� ��� ���� ���� �簢�� �׵θ� �׸���
    LCD_DrawText(72, 96, Mode); // ���� ��� ���� ���� �簢�� �ȿ� ���� ��� ���� ���� ������ ����� ������ ���
}

void EXTI9_5_IRQHandler()
{
    if (EXTI->PR & 0x00000100) //EXTI8, ���̽�ƽ �������� �Է� �� �� �ν�
    {
        EXTI->PR |= 0x00000100; //EXTI->PR 8�� 1�� �ʱ�ȭ
        if (Operator == '+') //���� �����ڰ� '+'�̸�
        {
            Operator = '-'; //'-'�� ����
        }
        else if (Operator == '-') //���� �����ڰ� '-'�̸�
        {
            Operator = 'x'; //'x'�� ����
        }
        else if (Operator == 'x') //���� �����ڰ� 'x'�̸�
        {
            Operator = '&'; //'&'�� ����
        }
        else if (Operator == '&') //���� �����ڰ� '&'�̸�
        {
            Operator = '|'; //'|'�� ����
        }
        else if (Operator == '|') //���� �����ڰ� '|'�̸�
        {
            Operator = '^'; //'^'�� ����
        }
        else if (Operator == '^') //���� �����ڰ� '^'�̸�
        {
            Operator = '+'; //'+'�� ����
        }
        Fram_Write(530, Operator); //������ Fram 530 �ּҿ� ����
        Fram_Write(531, Cresult); //����� Fram 531 �ּҿ� ����
        Fram_Write(529, Result_Sign); //����� �η� Fram 529 �ּҿ� ����
        BEEP(); //���� 1ȸ
        Set_Lcd(); //������ ������ LCD ���
    }
    if (EXTI->PR & 0x00000200) //EXTI9, SW1 ���� �� �ν�
    {
        EXTI->PR |= 0x00000200;//EXTI->PR 9�� 1�� �ʱ�ȭ
        if (Operator == '+') //�����ڰ� ���ϱ��
        {
            Cresult = Aopnd + Bopnd; //���ؼ� ����� ������ 10������ ����
            Result_Sign = '+'; //��ȣ ���
        }
        else if (Operator == '-') //�����ڰ� �����
        {
            if (Aopnd >= Bopnd) //A�� B���� ũ��
            {
                Cresult = Aopnd - Bopnd; //������� �״�� ���� ����
                Result_Sign = '+'; //��ȣ ���
            }
            else if (Aopnd < Bopnd) //A�� B���� ������
            {
                Cresult = Bopnd - Aopnd; //������� �ݴ�� ���� ��� ����
                Result_Sign = '-'; //��ȣ ������ �ٲ��ֱ�
            }
        }
        else if (Operator == 'x') //�����ڰ� ���ϱ��
        {
            Cresult = Aopnd * Bopnd; //���ؼ� 10������ ����
            Result_Sign = '+'; //��ȣ ���
        }
        else if (Operator == '&') //And �����ڸ�
        {
            Cresult = Aopnd & Bopnd; //And �����ؼ� 10������ ����
            Result_Sign = '+'; //��ȣ ���
        }
        else if (Operator == '|') //Or �����ڸ�
        {
            Cresult = Aopnd | Bopnd; //Or �����ؼ� 10������ ����
            Result_Sign = '+'; //��ȣ ���
        }
        else if (Operator == '^') //��� �����̸�
        {
            Cresult = Aopnd ^ Bopnd; //��� �����ؼ� 10������ ����
            Result_Sign = '+'; //��ȣ ���
        }
        Fram_Write(530, Operator); //������ Fram 530 �ּҿ� ����
        Fram_Write(531, Cresult); //����� Fram 531 �ּҿ� ����
        Fram_Write(529, Result_Sign); //����� ��ȣ Fram 529 �ּҿ� ����
        
        //10���� ���� �Ǿ� �ִ� ����� ������ �̿��� C�� �� �ڸ����� �´� �� ����
        C_3 = (Cresult & 0x8) >> 3;
        C_2 = (Cresult & 0x4) >> 2;
        C_1 = (Cresult & 0x2) >> 1;
        C_0 = (Cresult & 0x1);
        BEEP(); //���� 1ȸ
        Set_Lcd(); //������ ������ LCD ���
    }
    if (EXTI->PR & 0x00000040) //EXTI6, ���̽�ƽ ���� �ν�
    {
        EXTI->PR |= 0x00000040; //EXTI->PR 6�� 1 �Է��ؼ� �ʱ�ȭ
        GPIOG->ODR |= 0x0080; //LED7 ���
        BEEP(); //���� 1ȸ
        Mode = Row_Mode; //���Ӹ�� ����
        Result_Sign = '+'; //��ȣ ���
        flag = 1; //���� �ݺ��� �����Ű�� ���� flag ���� 1�� ����
        while (flag) //flag ������ 1�� �� ���� ���� �ݺ�
        {
            DelayMS(500); //0.5�ʸ���
            Cresult++; //����� 1�� ������Ű��
            //10���� ���� �Ǿ� �ִ� ����� ������ �̿��� C�� �� �ڸ����� �´� �� ����
            C_3 = (Cresult & 0x8) >> 3;
            C_2 = (Cresult & 0x4) >> 2;
            C_1 = (Cresult & 0x2) >> 1;
            C_0 = (Cresult & 0x1);
            Fram_Write(530, Operator); //������ Fram 530 �ּҿ� ����
            Fram_Write(531, Cresult); //����� Fram 531 �ּҿ� ����
            Fram_Write(529, Result_Sign); //����� ��ȣ Fram 529 �ּҿ� ����
            Set_Lcd(); //������ ������ LCD ���
        }
        //�ݺ��� Ż�� ��
        Mode = InRow_Mode; //���� ���X
        Set_Lcd();//������ ������ LCD ���
        //���� 3ȸ
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
    if (EXTI->PR & 0x00004000) //EXTI 14, SW6 ���� �� �ν�
    {
        EXTI->PR |= 0x00004000; //EXTI->PR 14�� 1�� �ʱ�ȭ
        BEEP(); //���� 1ȸ
        DelayMS(1000); //1�� ����
        flag = 0; //�÷��� ���� ������ 0���� �ٲ㼭 ���Ӹ�� Ż��
    }
}