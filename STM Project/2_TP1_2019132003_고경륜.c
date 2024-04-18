////////////////////////////////////////////////////////////////
// ������: Two Elevators
// ��������: �� ���� ���������Ͱ� �ְ� ������� ��ǥ���� �����Ͽ�
// ���������͸� ���������� ������ �� �ְ� �ϴ� �ý����� �����Ѵ�
// ����� �ϵ����(���): GPIO, SW, LED, LCD, EXEPTION
// ������: 2023-06-08
// ������ Ŭ����: �����Ϲ�
// �й�: 2019132003
// �̸�: ����
//////////////////////////////////////////////////////////////////


#include "stm32f4xx.h"
#include "GLCD.h"   //LCD�� ����ϱ� ���� ������� �߰�
#include "FRAM.h" //FRAM�� ����ϱ� ���� ������� �߰�
#include <string.h> //���ڿ� ���ϱ� ���� ������� �߰�

void EXTI_INIT();
void GPIO_INIT();
uint16_t KEY_Scan(void);
void BEEP(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

void Set_Lcd(); //���������� ����Ͽ� LCD�� �׷����� �Լ�

//���� ������ �־��� �����͵��� ���� ���� ����ϱ� ���� �ʱ�ȭ
char* Left_Elevator = "L-E"; //���� ����������
char* Right_Elevator = "R-E"; //������ ����������
char Stop = 'S'; //���������� ���� : Stop
char Up = 'U'; //���������� ���� : Up
char Down = 'D'; //���������� ���� : Down
char* FL = "FL"; //���������� ��� : �� ���� ���
char* EX = "EX"; //���������� ��� : ���� ���
char* HD = "HD"; //���������� ��� : �ߴ� ���

//�Լ����� �ٸ� �Ű������� ���� �ʾƵ� ������ �� �ֵ��� �������� ����
char* Select_Elevator = "L-E"; //���� ��� �� ����� ���������� ����
char* Select_Mode = "FL"; //���� ��带 ������ ����
char Select_State = 'S'; //���� ��� �� ����� ������������ ���¸� �����ϴ� ����
uint8_t Left_Floor = 1; //���� ���������� �� ���� ������ ����, �ʱ�ȭ 1
uint8_t Right_Floor = 1; //������ ���������� �� ���� ������ ����, �ʱ�ȭ 1
uint8_t Cur_Floor = 1; //����� �� ���� ������ ����, �ʱ�ȭ 1
uint8_t Des_Floor = 1; //��ǥ�� ������ ������ ����, �ʱ�ȭ 1

int main()
{
    LCD_Init(); //LCD�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�
    GPIO_INIT(); //GPIO�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�
    EXTI_INIT(); //EXTI�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�

    Fram_Init(); //Fram�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�(H/W)
    Fram_Status_Config(); //Fram S/W �ʱ�ȭ

    GPIOG->ODR &= ~0x00FF; //����, LED0~7 OFF�ϰ� ����
    GPIOG->ODR |= 0x0080; //ó�� �� ���� ���, LED7 ON

    Left_Floor = Fram_Read(2023); //���� ���������� Fram2023������ ����� ������ �ʱ�ȭ
    Right_Floor = Fram_Read(2024); //������ ���������� Fram2023������ ����� ������ �ʱ�ȭ
    Cur_Floor = Left_Floor; //����� Fram2023������ ����� ������ �ʱ�ȭ
    Des_Floor = Right_Floor; //��ǥ�� Fram2023������ ����� ������ �ʱ�ȭ

    //Fram 2023, 2024 �ּҿ� �߸��� �����Ͱ��� ���� �� ��� 1�� �ʱ�ȭ ���ִ� ���� ����
    if (!(Left_Floor >= 1 && Left_Floor <= 6 && Right_Floor >= 1 && Right_Floor <= 6))
    {
        Left_Floor = 1;
        Right_Floor = 1;
        Cur_Floor = 1;
        Des_Floor = 1;
    }


    Set_Lcd(); //�ʱ� ���� ���� �� Lcd ���

    while (1)
    {
        //������ �������
        if (strcmp(Select_Mode, FL) != 0)//������ ���� ����Ǿ� �ִ��� Ȯ��
        {
            //�ȵǾ� ������
            Select_Mode = FL; //������ ���� ����
            Set_Lcd(); //���� �� �������� LCD ���
            GPIOG->ODR &= ~0x00FF; //�� ���� ���, �ٸ� LED �� ����
            GPIOG->ODR |= 0x0080; //LED7�� Ű��
        }

        switch (KEY_Scan())
        {
        case 0xFD00: //SW1 ������ ��
            Cur_Floor++; //����� 1�� ����
            if (Cur_Floor == 7 || Cur_Floor == 0) //7�� �Ѿ�� �� 
            {
                Cur_Floor = 1; //�ٽ� 1�� �ǵ��� ������
            }

            BEEP(); //���� 1ȸ

            GPIOG->ODR |= 0x0002; //LED1 ON
            GPIOG->ODR &= ~0x0004; //LED2 OFF

            Set_Lcd(); //������ �������� LCD ���

            break; //Ż��
        case 0xFB00: //SW2 ������ ��
            Des_Floor++; //��ǥ�� 1�� ����
            if (Des_Floor == 7 || Des_Floor == 0) //7�� �Ѿ�� ��
            {
                Des_Floor = 1;//�ٽ� 1�� �ǵ��� ������
            }

            BEEP();//���� 1ȸ

            GPIOG->ODR |= 0x0004;//LED2 ON
            GPIOG->ODR &= ~0x0002;//LED1 OFF

            Set_Lcd();//������ �������� LCD ���

            break;//Ż��
        }
    }
}

void EXTI_INIT()
{
    RCC->AHB1ENR |= 0x00000080; //EXTI�� ����� GPIOH Enable
    RCC->APB2ENR |= 0x00004000; //SYSCFG Enable

    GPIOH->MODER &= ~0xC03F0000; //EXTI8, 15�� ����ϱ� ���� PH8, PH15 Input ��� ����

    SYSCFG->EXTICR[2] &= ~0x000F;//EXTI8�� PH�� ����ϱ� ���� 0bxxxx xxxx xxxx 0000 ���� �ʱ�ȭ ��
    SYSCFG->EXTICR[2] |= 0x0007;//EXTI8�� PH�� ����ϱ� ���� 0bxxxx xxxx xxxx 0111 ����

    SYSCFG->EXTICR[3] &= ~0xF000; //EXTI15�� PH�� ����ϱ� ���� 0b0000 xxxx xxxx xxxx ���� �ʱ�ȭ ��
    SYSCFG->EXTICR[3] |= 0x7000;//EXTI15�� PH�� ����ϱ� ���� 0b0111 xxxx xxxx xxxx ����

    EXTI->FTSR |= 0x00000100; //EXTI8 Falling Edge�� ����ǵ��� ����

    EXTI->FTSR |= 0x00008000; //EXTI15 Falling Edge�� ����ǵ��� ����

    EXTI->IMR |= 0x00000100; //EXTI ����ũ �����ֱ� ���� 8�� ��Ʈ�� 1 ����

    NVIC->ISER[0] |= 1 << 23; //EXTI9_5�� ����ϱ� ���� ���� ���̺� 23�� ����
    NVIC->ISER[1] |= 1 << (40 - 32); //EXTI15_10�� ����ϱ� ���� ���� ���̺� 40�� ����

    SCB->AIRCR &= ~0x00000700; //�켱���� ������ �� NVIC_PRIORITGROUP_4 ����ϱ� ���� ����

    NVIC->IP[23] = 0x2 << 4; //�������̺� 23�� �켱���� 2�� ����

    NVIC->IP[40] = 0x1 << 4; //�������̺� 40�� �켱���� 1�� ����
}

void GPIO_INIT()
{
    RCC->AHB1ENR |= 0x00000040; //GPIOG -> LED
    GPIOG->MODER &= ~0x0000FFFF; //GPIOG 0 ~ 7 ������ ���� 0���� �ʱ�ȭ
    GPIOG->MODER |= 0x00005555; //GPIOG 0 ~ 7 LED OUTPUT Mode
    GPIOG->OTYPER &= ~0x00ff; //GPIOG0~7 Push-Pull Ÿ������ ����
    GPIOG->OSPEEDR |= 0x00005555; //GPIOG0~7 medium speed�� ����

    RCC->AHB1ENR |= 0x00000080; //GPIOH -> SW
    GPIOH->MODER &= ~0xC03F0000; //GPIO 8,9,10,15 SW INPUT Mode
    GPIOH->PUPDR &= ~0xC03F0000; //no-pull-up-down���� ����

    RCC->AHB1ENR |= 0x00000020;	//GPIOF -> BUZZER
    GPIOF->MODER &= ~0x000C0000; //GPIOF 9 ������ ���� 0���� �ʱ�ȭ
    GPIOF->MODER |= 0x00040000; //GPIOF 9 BUZZER OUTPUT Mode
    GPIOF->OTYPER &= ~0x0200; //GPIOF 0  Push-Pull Ÿ������ ����
    GPIOF->OSPEEDR |= 0x00040000;//GPIOF 0 medium speed�� ����
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
    LCD_Clear(RGB_WHITE); // ȭ�� �� ������ Ŭ����
    LCD_SetFont(&Gulim8); //����ü 8 ���
    LCD_SetBackColor(RGB_WHITE); //�۾� ��� �� �� ����
    LCD_SetTextColor(RGB_BLACK); //�۾� ������ ����
    LCD_DisplayText(0, 0, "MC-Elevator(GGR)");// ���� �ؽ�Ʈ ���
    LCD_DisplayChar(6, 9, '>'); //�̵����� ���
    LCD_SetTextColor(RGB_RED);//�۾� ������ ����
    LCD_DrawText(68, 25, Select_Mode); //Select_Mode ������ ����Ǿ� �ִ� ��尪 ���
    LCD_DisplayChar(5, 9, Select_State); //Select_State ������ ����Ǿ� �ִ� ���������� ���°� ���
    LCD_DisplayChar(6, 8, Cur_Floor + 48); //���������� �Ǿ� �ִ� ����� ���� 48�� ���� �ƽ�Ű�ڵ尪���� ������ ���
    LCD_DisplayChar(6, 10, Des_Floor + 48);//���������� �Ǿ� �ִ� ��ǥ�� ���� 48�� ���� �ƽ�Ű�ڵ尪���� ������ ���
    if (strcmp(Select_Elevator, "L-E") == 0) //���� ���������Ͱ� ���õǾ� ������
    {
        LCD_SetTextColor(RGB_BLUE); //�۾� �Ķ��� ����
    }
    else if (strcmp(Select_Elevator, "R-E") == 0) //������ ���������Ͱ� ���õǾ� ������
    {
        LCD_SetTextColor(RGB_GREEN); //�۾� �ʷϻ� ����
    }
    LCD_DisplayText(4, 8, Select_Elevator); //���õ� ���������͸� ���
    LCD_SetTextColor(RGB_BLUE); //�۾� �Ķ��� ����
    for (uint8_t i = 1; i <= 6; i++)
    {
        LCD_DisplayChar(8 - i, 4, i + 48); //���� ���������� ���� �� ���� ǥ��
    }
    LCD_SetBrushColor(RGB_BLUE); //�귯�� �Ķ��� ����
    for (uint8_t i = 1; i <= Left_Floor; i++) //���� ���������� �������� ����
    {
        LCD_DrawFillRect(22, 26 + (13 * (6 - i)), 9, 13); //���� ���������� ���� ���
    }
    LCD_SetTextColor(RGB_GREEN); // �۾� �ʷϻ� ����
    for (uint8_t i = 1; i <= 6; i++)
    {
        LCD_DisplayChar(8 - i, 14, i + 48); //������ ���������� ���� �� ���� ǥ��
    }
    LCD_SetBrushColor(RGB_GREEN); //�귯�� �ʷϻ� ����
    for (uint8_t i = 1; i <= Right_Floor; i++) //������ ���������� �������� ����
    {
        LCD_DrawFillRect(121, 26 + (13 * (6 - i)), 9, 13); //������ ���������� ���� ���
    }
}

void EXTI9_5_IRQHandler(void) //������ EXTI8 ����ϱ� ���� ���ͷ�Ʈ �ڵ鷯
{
    if (EXTI->PR & 0x00000100) //EXTI8�̸�
    {
        EXTI->PR |= 0x00000100; //EXTI->PR 1 �־��༭ �ٽ� �ʱ�ȭ

        EXTI->IMR |= 0x00008000; //EXTI15 Ȧ�� ��带 ����� �� �ְ� ����ũ ����

        GPIOG->ODR &= ~0x00C7; //LED0 ���� �� ����
        GPIOG->ODR |= 0x0001; //LED0�� Ű��

        Select_Mode = EX; //���� ���� ����

        BEEP(); //BUZZER 1ȸ

        uint8_t Dif_Left = abs(Cur_Floor - Left_Floor); //������� ���� ���������� ������ ���� Ȯ��
        uint8_t Dif_Right = abs(Cur_Floor - Right_Floor);//������� ������ ���������� ������ ���� Ȯ��

        if (Dif_Left <= Dif_Right)//������� ���� ���������� ������ ���̰� �� �۴ٸ�
        {
            Select_Elevator = Left_Elevator;//���� ���������� ����
            if (Cur_Floor - Left_Floor > 0) //������� ���������� ������
            {
                Select_State = Up; //���������� �ö󰡵��� ���� ����
                Set_Lcd(); //����� �������� ���
                while (Left_Floor < Cur_Floor) //������� ������ ������
                {
                    DelayMS(500);
                    Left_Floor++; //������ 1�� �����ϸ鼭
                    Set_Lcd();  //����� �������� ���
                }
                DelayMS(500);
                Select_State = Stop; // ����� ���� �� ���������� ���� ����
                Set_Lcd(); //����� �������� ���
                DelayMS(500);
            }
            else if (Cur_Floor - Left_Floor < 0)//������� ���������� ������
            {
                Select_State = Down; //���������� ���������� ���� ����
                Set_Lcd(); //����� �������� ���
                while (Left_Floor > Cur_Floor)//������� ������ ������
                {
                    DelayMS(500);
                    Left_Floor--;//������ 1�� �����ϸ鼭
                    Set_Lcd();//����� �������� ���
                }
                DelayMS(500);
                Select_State = Stop;// ����� ���� �� ���������� ���� ����
                Set_Lcd(); //����� �������� ���
                DelayMS(500);
            }
        }
        else if (Dif_Left > Dif_Right)//������� ������ ���������� ������ ���̰� �� �۴ٸ�
        {
            Select_Elevator = Right_Elevator;//������ ���������� ����
            if (Cur_Floor - Right_Floor > 0)//������� ���������� ������
            {
                Select_State = Up;//���������� �ö󰡵��� ���� ����
                Set_Lcd();//����� �������� ���
                while (Right_Floor < Cur_Floor)//������� ������ ������
                {
                    DelayMS(500);
                    Right_Floor++;//������ 1�� �����ϸ鼭
                    Set_Lcd();//����� �������� ���
                }
                DelayMS(500);
                Select_State = Stop;// ����� ���� �� ���������� ���� ����
                Set_Lcd(); //����� �������� ���
                DelayMS(500);
            }
            else if (Cur_Floor - Right_Floor < 0)//������� ���������� ������
            {
                Select_State = Down;//���������� ���������� ���� ����
                Set_Lcd();//����� �������� ���
                while (Right_Floor > Cur_Floor)//������� ������ ������
                {
                    DelayMS(500);
                    Right_Floor--;//������ 1�� �����ϸ鼭
                    Set_Lcd();//����� �������� ���
                }
                DelayMS(500);
                Select_State = Stop;// ����� ���� �� ���������� ���� ����
                Set_Lcd();//����� �������� ���
                DelayMS(500);
            }
        }


        if (Cur_Floor < Des_Floor) //������� ��ǥ������ ������
        {
            Select_State = Up; //���������� �ö󰡵��� ���� ����
            Set_Lcd();//����� �������� ���
            if (strcmp(Select_Elevator, "L-E") == 0)//���� ���������Ͱ� ���õǾ� ������
            {
                while (Left_Floor < Des_Floor) //�������� ��ǥ���� ������ ������
                {
                    DelayMS(500);
                    Left_Floor++; //������ 1�� ����
                    Set_Lcd();//����� �������� ���
                }
            }
            else if (strcmp(Select_Elevator, "R-E") == 0)//������ ���������Ͱ� ���õǾ� ������
            {
                while (Right_Floor < Des_Floor) //�������� ��ǥ���� ������ ������
                {
                    DelayMS(500);
                    Right_Floor++; //������ 1�� ����
                    Set_Lcd();//����� �������� ���
                }
            }
            DelayMS(500);
            Select_State = Stop;//��ǥ�� ���� �� ���������� ���� ����
            Set_Lcd();//����� �������� ���
            DelayMS(500);
        }
        else if (Cur_Floor > Des_Floor) //��ǥ���� ��������� ������
        {
            Select_State = Down; //���������� ���� ������
            Set_Lcd();//����� �������� ���
            if (strcmp(Select_Elevator, "L-E") == 0) //���� ���������� ���õǾ� ������
            {
                while (Left_Floor > Des_Floor) //�������� ��ǥ���� ������ ������
                {
                    DelayMS(500);
                    Left_Floor--;//1�� ����
                    Set_Lcd();//����� �������� ���
                }
            }
            else if (strcmp(Select_Elevator, "R-E") == 0) //������ ���������� ���õǾ� ������
            {
                while (Right_Floor > Des_Floor) //�������� ��ǥ���� ������ ������
                {
                    DelayMS(500);
                    Right_Floor--; //1�� ����
                    Set_Lcd();//����� �������� ���
                }
            }
            DelayMS(500);
            Select_State = Stop;//��ǥ �� ���� �� ���������� ���� ����
            Set_Lcd();//����� �������� ���
            DelayMS(500);
        }
        else if (Cur_Floor == Des_Floor) //��ǥ��, ������� ���� ���
        {
            Set_Lcd();//����� �������� ���
            DelayMS(1000);//1�� ���
        }

        Fram_Write(2023, Left_Floor); //������ ���� ���������� ���� Fram 2023������ ����
        Fram_Write(2024, Right_Floor); //������ ������ ���������� ���� Fram 2024������ ����

        //���� 3ȸ
        BEEP();
        DelayMS(250);
        BEEP();
        DelayMS(250);
        BEEP();

        //������ �ƴϸ� Ȧ���� ������� ���ϰ� EXTI15�� ����ũ
        EXTI->IMR &= ~0x00008000;
    }
}

void EXTI15_10_IRQHandler(void) //Ȧ�� ���
{
    if (EXTI->PR & 0x8000) //EXTI15 �̸�
    {
        EXTI->PR |= 0x8000; //EXTI->PR 15�� 1�� �ʱ�ȭ
        GPIOG->ODR &= ~0x00C1; //LED 6���� Ű�� ���� LED�� OFF
        GPIOG->ODR |= 0x0040; //LED6 ON
        Select_Mode = HD; //���������� ��� Ȧ����
        Set_Lcd();//����� �������� ���
        for (uint8_t i = 0; i < 10; i++) //0.5�ʸ��� ���� 1ȸ 10�� �ݺ� -> 5�� ����
        {
            DelayMS(500);
            BEEP();
        }
        Select_Mode = EX; //���������� ��� ������� ����
        Set_Lcd();//����� �������� ���
        GPIOG->ODR &= ~0x00C1; //�����忡 �´� LED Ű�� ���� �ٸ� LED�� OFF
        GPIOG->ODR |= 0x0001; //LED1 ON
    }
}