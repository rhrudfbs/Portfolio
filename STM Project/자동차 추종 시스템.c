/////////////////////////////////////////////////////////////
// PR1: Car Tracking system
// ������: 2019132003 ����
// �ֿ� ����
// - �����ڵ��� 2�밡 ���� ���� �����ϰ� �ִ�. �������� random
//   �ϰ� �����ϰ�, �������� ���������� �Ÿ��� �ε����� �Ÿ���
//   ��� �����ϸ鼭 �ӵ��� ������ �����ϸ� �������� ���󰡾�
//   �Ѵ�. �׿� ���� ������ �ý��� ���α׷���
// - �Ÿ�����1: ������ŰƮ���� ��������, PA1(ADC3_IN1)
// - �Ÿ�����2: 40pin Box header connector�� ����� �ܺ� ��������, PF3(ADC3_IN9)
// - ������ ����: PB7(TIM4_CH2(PWM mode)), LED�� PWM ��ȭȮ��
// - ������ �ڵ�: PF9(TIM14_CH1(PWM mode)), Buzzer�� PWM ��ȭȮ��
// - Off-line ������ �õ�: Move-key(SW4(EXTI12)), Stop-key(SW6(EXTI14))
// - ����(PC ������α׷�) ������ �õ�: Move-key(��M��), Stop-key(��S��)
// - �Ÿ��� ǥ��: GLCD(D), PC
// - ������ �ӵ� ǥ��: GLCD(DR)
// - ������ ���� ǥ��: GLCD(��L��, ��R��, ��F��)
/////////////////////////////////////////////////////////////


#include "stm32f4xx.h" // stm�� ���� ������� �߰�
#include "GLCD.h" //LCD�� ����ϱ� ���� ������� �߰�
#include "FRAM.h" //FRAM�� ����ϱ� ���� ������� �߰�

void TIM1_Init(void); // TIM1 ���� �Լ�
void TIM4_Init(void); // TIM4 ���� �Լ�
void TIM14_Init(void); // TIM14 ���� �Լ�
void _ADC3_Init(void); // ADC3 ���� �Լ�
void DMA2_Init_(void); // DMA2 ���� �Լ�
void USART1_Init(void); // USART1 ���� �Լ�
void EXTI_Init_(void); // �ܺ� ���ͷ�Ʈ ���� �Լ�
void USART_BRR_Configuration(uint32_t USART_BaudRate); // USART1 Baudrate ���� �Լ�

void LCD_display1(void); // �ʱ� ������ �ʴ� LCD ��� �Լ�
void LCD_display2(void); // �����ϴ� ���� ���� LCD ��� �Լ�

void Set_speed(uint32_t D); // �������� �ӵ� ���� �Լ�(PWM Duty Ratio ����)
void Set_Dir(uint32_t D); // �������� ���� ���� �Լ�(PWM Duty Ratio ����)

void SerialSendChar(uint8_t c); // USART1 8bit �� ���� ���� �Լ�
void SerialSendString(char *s); // USART1 ���ڿ� ���� �Լ�

void DelayMS(unsigned short wMS); // MS ������ �Լ�
void DelayUS(unsigned short wUS); // MS ������ �Լ�

uint16_t get_distance[2] = {0, 0}; // ADC3�� ���� ������ ���� ���� �迭
float distance_to_voltage[2] = {0, 0}; // ADC�� ���� ������ �������� ��ȯ �� ���� ���� �迭
uint32_t distance[2] = {0, 0}; // ���а� �Ÿ������� ��ȯ �� ���� ���� �迭
char go_stop = 'S'; // ��ɾ� ���� ����

int main(void)
{
  LCD_Init(); // LCD ���� �Լ�
  DelayMS(10); // LCD���� ������
  
  Fram_Init(); // Fram�� ����ϱ� ���� �ʱ�ȭ �۾� �Լ�(H/W)
  Fram_Status_Config(); // Fram S/W �ʱ�ȭ
  
  LCD_display1(); // �ʱ� ������ �ʴ� LCD ��� �Լ�

  TIM1_Init(); // TIM1 ���� �Լ�
  TIM4_Init(); // TIM4 ���� �Լ�
  TIM14_Init(); // TIM14 ���� �Լ�
  _ADC3_Init(); // ADC3 ���� �Լ�
  DMA2_Init_(); // DMA2 ���� �Լ�
  USART1_Init(); // USART1 ���� �Լ�
  EXTI_Init_(); // �ܺ� ���ͷ�Ʈ ���� �Լ�
  
  go_stop = (char)Fram_Read(1201); // Fram 1201�ּҿ� ����Ǿ� �ִ� 8bit ������ �о ��ɾ� ���� ������ ����
  if(go_stop != 'M' && go_stop != 'S') // Fram 1201�ּҿ� �����Ⱚ ���� �� ���� ó��
  {
    go_stop = 'S'; // Stop ���
  }
  
  if(go_stop == 'S') // Stop ����̸�
  {
    ADC3->CR2 &= ~(1 << 0); // ADC3 disable
    distance[0] = 0; // �Ÿ��� 0���� ��ȯ
    distance[1] = 1; // �Ÿ��� 1�� ��ȯ
    TIM4->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
    TIM14->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
  }
  else if(go_stop == 'M') // Move ����̸�
  {
    distance[0] = 0; // �Ÿ��� 0���� ��ȯ
    distance[1] = 1; // �Ÿ��� 1�� ��ȯ
    TIM4->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
    TIM14->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
    ADC3->CR2 |= (1 << 0); // ADC3 Enable
  }
  
  LCD_DisplayChar(1, 18, go_stop); // ��ɾ� LCD�� ���
  LCD_display2(); // ���� �����͵��� �������� LCD ���
  
  while(1) // ���� �ݺ�
  {
    
  }
}

void LCD_display1(void) // ������ �ʴ� LCD ��� �κ� ���
{
  LCD_Clear(RGB_WHITE); // ȭ�� Ŭ����
  LCD_SetFont(&Gulim8); // ��Ʈ : ���� 8
  LCD_SetBackColor(RGB_WHITE); // ���ڹ��� : White
  LCD_SetTextColor(RGB_BLACK); // ���ڻ� : Black
  
  LCD_DisplayText(0, 0, "GGR 2019132003"); // �̸� �̴ϼ�, �й� ���
  LCD_DisplayText(1, 0, "Tracking Car"); // ������Ʈ�� ���
  LCD_DisplayText(2, 0, "D1:"); // �� ������ �Ÿ� ǥ�ø� ���� ĭ
  LCD_DisplayText(3, 0, "D2:"); // �ε����� �Ÿ� ǥ�ø� ���� ĭ
  LCD_DisplayText(4, 0, "SP(DR):  %DIR(DR):"); // �����ӵ�, ����(PWM Duty Ratio) ǥ�ø� ���� ĭ
  LCD_SetTextColor(RGB_BLUE); // ���ڻ� �Ķ������� ����
}

void LCD_display2(void) // ���ϴ� �����͵鿡 ���� LCD ��� �Լ�
{
  if(distance[0] >= 10) // ���� �� ������ �Ÿ��� 10���� ũ�ų� ������
  {
    LCD_DisplayChar(2, 17, distance[0] / 10 + 48); // 10�� �ڸ��� �ƽ�Ű �ڵ�� ��ȯ �� ���
    LCD_DisplayChar(2, 18, distance[0] % 10 + 48); // 1�� �ڸ��� �ƽ�Ű �ڵ�� ��ȯ �� ���
  }
  else // �� �ܿ�
  {
    LCD_DisplayChar(2, 17, ' '); // 10�� �ڸ��� �����
    LCD_DisplayChar(2, 18, distance[0] + 48); // 1�� �ڸ��� �ƽ�Ű �ڵ�� ��ȯ �� ���
  }
  
  LCD_DisplayChar(3, 18, distance[1] + 48); // �ε����� �Ÿ� �ƽ�Ű �ڵ�� ��ȯ �� ���

  LCD_SetBrushColor(RGB_WHITE); // �귯�� �� �Ͼ������ ��ȯ
  LCD_DrawFillRect(25, 27, 105, 10); // �� ������ �Ÿ� ��� ����� ����� (������ ���� �����)
  LCD_DrawFillRect(25, 40, 105, 10); // �ε����� �Ÿ� ��� ����� ����� (�ʷϻ� ���� �����)
  LCD_SetBrushColor(RGB_RED); // �귯�� �� ���������� ��ȯ
  LCD_DrawFillRect(25, 27, distance[0] * 105 / 19, 10); // �� ������ �Ÿ� ��� ����� �׸��� (������ ���� �׸���)
  LCD_SetBrushColor(RGB_GREEN); // �귯�� �� �ʷϻ����� ��ȯ
  LCD_DrawFillRect(25, 40, (distance[1] + 1) * 105 / 4, 10); // �ε����� �Ÿ� ��� ����� �׸��� (�ʷϻ� ���� �׸���)
  Set_speed(distance[0]); // �� ������ �Ÿ��� ���� �ӵ�, LCD ����(TIM4 PWM Duty Ratio ����)
  Set_Dir(distance[1]); // �ε����� �Ÿ��� ���� ����, LCD ����(TIM14 PWM Duty Ratio ����)
}

void TIM1_Init(void) // TIM1 ���� �Լ�
{
  RCC->APB2ENR |= (1 << 0); // TIM1 Clock Enable
  
  TIM1->CR1 &= ~(1 << 1); // UEV Enable
  TIM1->CR1 &= ~(1 << 2); // Counter over/underflow, Setting the UG bit, Update generation through the slave mode controller can be event
  TIM1->CR1 &= ~(1 << 3); // disable one-pulse-mode
  TIM1->CR1 &= ~(1 << 4); // Counter used as upcounter
  TIM1->CR1 &= ~(3 << 5); // Edge-Alligned mode
  TIM1->CR1 &= ~(1 << 7); // preload disable
  TIM1->CR1 &= ~(3 << 8); // No Clock Division
  
  TIM1->PSC = 16800 - 1; // 168,000,000 / 16,800 = 10,000Hz
  
  TIM1->ARR = 4000 - 1; // 1 / 10,000 * 4,000 = 0.4s
  
  TIM1->EGR |= (1 << 0); // Set Update generation No action
  
  TIM1->CCMR2 &= ~(3 << 0); // TIM1_CC3 is configured as output
  TIM1->CCMR2 &= ~(1 << 2); // CC3 behaves normally depending on counter
  TIM1->CCMR2 &= ~(1 << 3); // OC3 preload disable
  TIM1->CCMR2 |= (3 << 4); // OC3 mode - toggle
  
  TIM1->CCER |= (1 << 8); // CC3 output enable
  TIM1->CCER &= ~(1 << 9); // CC3 output polarity-active high
  
  TIM1->BDTR |= (1 << 15); // TIM1 Main output enable
  
  TIM1->CCR3 = 2000; // Counter compare�� �� 2000 ����
  
  TIM1->DIER |= (1 << 3); // TIM1 CC3 interrupt enable
  NVIC->ISER[0] |= (1 << 27); // TIM1_CC interrupt handler
  
  TIM1->CR1 |= (1 << 0); // TIM1 disable
}

void TIM1_CC_IRQHandler(void)
{
  TIM1->SR &= ~(1 << 3); // set interrupt flag to 0
  if(distance[0] >= 10) // �� ������ �Ÿ��� 10���� ũ��
  {
    char str[5] = {distance[0] / 10 + 48, distance[0] % 10 + 48, 'm', '\n', '\0'}; // ���� �迭�� �Ÿ��� ������ ���� �� ������ ������ ������ ���ڿ� ����
    SerialSendString(str); // USART1���� ���ڿ� ����
  }
  else // �� �ܿ�
  {
    char str[4] = {distance[0] + 48,  'm', '\n', '\0'}; // ���� �迭�� �Ÿ��� ������ ���� �� ������ ������ ������ ���ڿ� ����
    SerialSendString(str); // USART1���� ���ڿ� ����
  }
}

void TIM4_Init(void)
{
  RCC->AHB1ENR |= (1 << 1); // GPIOB clock Enable
  GPIOB->MODER |= (2 << 14); // PB7 Alternative function
  GPIOB->OSPEEDR |= (3 << 14); // PB7 High speed
  GPIOB->OTYPER &= ~(1 << 7); // PB7 Output push-pull
  GPIOB->PUPDR |= (1 << 14); // PB7 Pull-up
  GPIOB->AFR[0] |= (2 << 28); // Connect TIM4 and PB7
  
  RCC->APB1ENR |= (1 << 2); // TIM4 clock Enable
  
  TIM4->CR1 &= ~(1 << 1); // UEV Enable
  TIM4->CR1 &= ~(1 << 2); // Counter over/underflow, Setting the UG bit, Update generation through the slave mode controller can be event
  TIM4->CR1 &= ~(1 << 3); // disable one-pulse-mode
  TIM4->CR1 &= ~(1 << 4); // Counter used as upcounter
  TIM4->CR1 &= ~(3 << 5); // Edge-Alligned mode
  TIM4->CR1 &= ~(1 << 7); // preload disable
  TIM4->CR1 &= ~(3 << 8); // No Clock Division
  
  TIM4->PSC = 8400 - 1; // 84,000,000 / 8,400 = 10,000Hz
  
  TIM4->ARR = 50000 - 1; // 1 / 10,000 * 50,000 = 5s
  
  TIM4->EGR |= (1 << 0); // Set Update generation No action
  
  TIM4->CCMR1 &= ~(3 << 8); // CC2 is configured as output
  TIM4->CCMR1 &= ~(1 <<10); // CC2 behaves normally depending on counter
  TIM4->CCMR1 &= ~(1 << 11); // OC2 preload disable -> �ﰢ���� ������ ���� off
  TIM4->CCMR1 |= (6 << 12); // Set PWM mode1
  
  TIM4->CCER |= (1 << 4); // CC2 output enable
  TIM4->CCER &= ~(1 << 5); // CC2 output active high
  
  TIM4->CCR2 = 0; // �ʱ� �ӵ� 0���� ���� DR = 0%
  
  TIM4->CR1 |= (1 << 0); // TIM4 Enable
}

void TIM14_Init(void) // TIM14 ���� �Լ�
{
  RCC->AHB1ENR |= (1 << 5); // GPIOF clock Enable
  GPIOF->MODER |= (2 << 18); // PF7 Alternative function
  GPIOF->OSPEEDR |= (3 << 18); // PF7 High speed
  GPIOF->OTYPER &= ~(1 << 9); // PF7 Output push-pull
  GPIOF->PUPDR |= (1 << 18); // PF7 Pull-up
  GPIOF->AFR[1] |= (9 << 4); // connect TIM14 and PF7
  
  RCC->APB1ENR |= (1 << 8);
  
  TIM14->CR1 &= ~(1 << 1); // UEV Enable
  TIM14->CR1 &= ~(1 << 2); // Counter over/underflow, Setting the UG bit, Update generation through the slave mode controller can be event
  TIM14->CR1 &= ~(1 << 3); // disable one-pulse-mode
  TIM14->CR1 &= ~(1 << 4); // Counter used as upcounter
  TIM14->CR1 &= ~(3 << 5); // Edge-Alligned mode
  TIM14->CR1 &= ~(1 << 7); // preload disable
  TIM14->CR1 &= ~(3 << 8); // No Clock Division
  
  TIM14->PSC = 420 - 1; // 84,000,000 / 420 = 200,000Hz
  
  TIM14->ARR = 80 - 1; // 1 / 200,000 * 80 = 0.0004s
  
  TIM14->EGR = (1 << 0); // Set Update generation No action
  
  TIM14->CCMR1 &= ~(3 << 0); // CC1 is configured as output
  TIM14->CCMR1 &= ~(1 << 2); // CC1 behaves normally depending on counter
  TIM14->CCMR1 &= ~(1 << 3); // OC1 preload disable ->�ﰢ���� ������ ���� off
  TIM14->CCMR1 |= (6 << 4); // Set PWM mode1
  
  TIM14->CCER |= (1 << 0); // CC1 output enable
  TIM14->CCER &= ~(1 << 1); // CC1 output active high
  
  TIM14->CCR1 = 0; //�ʱ� ���� DR = 0%
  
  TIM14->CR1 |= (1 << 0); // TIM14 Enable
}

void Set_speed(uint32_t D) // �� ������ �Ÿ��� ���� �ӵ�, LCD ��� ���� �Լ�
{
  if(D == 0) // �Ÿ��� 0�̶��
  {
    TIM4->CCR2 = 0; // DR 10%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "00"); // LCD DR ���
  }
  else if(D >= 3 && D <= 4) // �Ÿ��� 3 or 4���
  {
    TIM4->CCR2 = 5000; // DR 10%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "10"); // LCD DR ���
  }
  else if(D >= 5 && D <= 6) // �Ÿ��� 5 or 6�̶��
  {
    TIM4->CCR2 = 10000; // DR 20%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "20"); // LCD DR ���
  }
  else if(D >= 7 && D <= 8) // �Ÿ��� 7 or 8�̶��
  {
    TIM4->CCR2 = 15000; // DR 30%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "30"); // LCD DR ���
  }
  else if(D >= 9 && D <= 10) // �Ÿ��� 9 or 10�̶��
  {
    TIM4->CCR2 = 20000; // DR 40%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "40"); // LCD DR ���
  }
  else if(D >= 11 && D <= 12) // �Ÿ��� 11 or 12���
  {
    TIM4->CCR2 = 25000; // DR 50%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "50"); // LCD DR ���
  }
  else if(D >= 13 && D <= 14) // �Ÿ��� 13 or 14���
  {
    TIM4->CCR2 = 30000; // DR 60%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "60"); // LCD DR ���
  }
  else if(D >= 15 && D <= 16) // �Ÿ��� 15 or 16�̶��
  {
    TIM4->CCR2 = 35000; // DR 70%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "70"); // LCD DR ���
  }
  else if(D >= 17 && D <= 18) // �Ÿ��� 17 or 18�̶��
  {
    TIM4->CCR2 = 40000; // DR 80%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "80"); // LCD DR ���
  }
  else if(D == 19) // �Ÿ��� 19���
  {
    TIM4->CCR2 = 45000; // DR 90%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "90"); // LCD DR ���
  }
  else // ����ó��
  {
    TIM4->CCR2 = 0; // ����ó��
    LCD_DisplayText(4, 7, " 00"); // LCD DR ���
  }
}

void Set_Dir(uint32_t D) // �ε����� �Ÿ��� ���� ����, LCD ��� ���� �Լ�
{
  if(D == 0) // �Ÿ��� 0�̶��
  {
    LCD_DisplayChar(4, 18, 'R'); // LCD ���� ���
    TIM14->CCR1 = 24; // DR 30%, PWM1 mode -> High state before CC
  }
  else if(D == 1) // �Ÿ��� 1�̶��
  {
    LCD_DisplayChar(4, 18, 'F'); // LCD ���� ���
    TIM14->CCR1 = 0; // DR 0%, PWM1 mode -> High state before CC
  }
  else if(D == 2 || D == 3) // �Ÿ��� 2 or 3�̶��
  {
    LCD_DisplayChar(4, 18, 'L'); // LCD ���� ���
    TIM14->CCR1 = 72; // DR 90%, PWM1 mode -> High state before CC
  }
  else TIM14->CCR1 = 0; // ����ó��
}

void _ADC3_Init(void) // ADC3 ���� �Լ�
{
  RCC->AHB1ENR |= (1 << 0); // GPIOA Enable
  RCC->AHB1ENR |= (1 << 5); // GPIOF Enable
  RCC->APB2ENR |= (1 << 10); // ADC3 Enable
  
  GPIOA->MODER |= (3 << 2); // PA1 Analog in mode
  GPIOF->MODER |= (3 << 6); // PF3 Analog in mode
  
  ADC->CCR &= ~(31 << 0); // All the ADCs independent
  ADC->CCR |=  (1<<16); // 0x00010000 ADCPRE:ADC_Prescaler_Div4 (ADC MAX Clock 36MHz, 84Mhz(APB2)/4 = 21MHz)
  ADC->CCR |= (1 << 14); // ADC_DMAAccessMode_1
  ADC->CCR |= (15 << 8); // ADC_TwoSamplingDelay_20Cycles
  
  ADC3->CR1 |= (1 << 24); // Resolution : 10 bit
  ADC3->CR1 |= (1 << 8); // SCAN Mode Enable
  ADC3->CR1 |= (1 << 5); //  Interrupt enable for EOC
  
  ADC3->CR2 &= ~(1 << 1); // Single Conversion Mode
  ADC3->CR2 |= (2 << 24); // set External trigger to TIM1_CC3
  ADC3->CR2 |= (3 << 28); // Trigger detection on rising&falling edges
  ADC3->CR2 &= ~(1 << 11); // Data Right alligned
  ADC3->CR2 &= ~(1 << 10); // The EOC bit is set at the end of each sequence of regular conversions
  
  ADC3->SQR1 |= (1 << 20); // 2 channel sequence length
  ADC3->SQR3 |= (1 << 0); // channel 1 first
  ADC3->SQR3 |= (9 << 5); // channel 9 second
  
  ADC3->SMPR2 |= (7 << 3); // channel 1 sampling time 480 cycles
  ADC3->SMPR2 |= (7 << 27); // channel 9 sampling time 480 cycles
  
  ADC3->CR2 |= (1 << 9); // DMA request are issued as long as data are converted and DMA=1
  ADC3->CR2 |= (1 << 8); // DMA mode enable
  
  NVIC->ISER[0] |= (1 << 18); // ADC1,2,3 global interrupt handler
  
  ADC3->CR2 |= (1 << 0); // Enable ADC
}

void ADC_IRQHandler(void) // ADC ���ͷ�Ʈ �ڵ鷯
{
  ADC3->SR &= ~(1 << 1); // EOC flag clear
  distance_to_voltage[0] = (float)get_distance[0] * (float)3.3 / (float)1023; // 10bit ���شɿ� ���� �������� ��ȯ
  distance[0] = (uint32_t)(distance_to_voltage[0] * 5) + 3; // �־��� �Ÿ��� ���Ŀ� ���� ���
  distance_to_voltage[1] = (float)get_distance[1] * (float)3.3 / (float)1023; // 10bit ���شɿ� ���� �������� ��ȯ
  distance[1] = (uint32_t)distance_to_voltage[1]; // �־��� �Ÿ��� ���Ŀ� ���� ���
  
  Set_speed(distance[0]); // �������� �ӵ� ���� �Լ�(PWM Duty Ratio ����)
  Set_Dir(distance[1]); // �������� ���� ���� �Լ�(PWM Duty Ratio ����)
  
  LCD_display2(); // �ٲ� �����Ϳ� ���� LCD ��� �Լ�
}

void DMA2_Init_(void) // DMA2 ���� �Լ�
{
  RCC->AHB1ENR |= (1<<22); //DMA2 clock enable
  DMA2_Stream0->CR |= (2<<25); //DMA2 Stream0 channel 2 selected->ADC3
  
  DMA2_Stream0->PAR |= (uint32_t)&ADC3->DR; //Peripheral address - ADC3->DR(Regular data) Address
  DMA2_Stream0->M0AR |= (uint32_t)&get_distance; //Memory address - get_distance address 
  DMA2_Stream0->CR &= ~(3<<6); //Data transfer direction : Peripheral-to-memory (P=>M)
  DMA2_Stream0->NDTR = 2; //DMA_BufferSize = 2 (get_distance[2])
  
  DMA2_Stream0->CR &= ~(1<<9); //Peripheral increment mode  - Peripheral address pointer is fixed
  DMA2_Stream0->CR |= (1<<10); //Memory increment mode - Memory address pointer is incremented after each data transferd 
  DMA2_Stream0->CR |= (1<<11); //Peripheral data size - halfword(16bit)
  DMA2_Stream0->CR |= (1<<13); //Memory data size - halfword(16bit)   
  DMA2_Stream0->CR |= (1<<8); //Circular mode enabled   
  DMA2_Stream0->CR |= (2<<16); //Priority level - High

  DMA2_Stream0->FCR &= ~(1<<2); //DMA_FIFO_direct mode enabled
  DMA2_Stream0->FCR |= (1<<0); //DMA_FIFO Threshold_HalfFull , Not used in direct mode

  DMA2_Stream0->CR &= ~(3<<23); //Memory burst transfer configuration - single transfer
  DMA2_Stream0->CR &= ~(3<<21); //Peripheral burst transfer configuration - single transfer  
  DMA2_Stream0->CR |= (1<<0); //DMA2_Stream0 enabled
}

void USART1_Init(void) // USART1 ���� �Լ�
{
  // USART1 : TX(PA9)
  RCC->AHB1ENR |= (1<<0); // RCC_AHB1ENR GPIOA Enable
  GPIOA->MODER |= (2<<2*9); // GPIOA PIN9 Output Alternate function mode					
  GPIOA->OSPEEDR |= (3<<2*9); // GPIOA PIN9 Output speed (100MHz Very High speed)
  GPIOA->AFR[1] |= (7<<4); // Connect GPIOA pin9 to AF7(USART1)
  
  // USART1 : RX(PA10)
  GPIOA->MODER |= (2<<2*10); // GPIOA PIN10 Output Alternate function mode
  GPIOA->OSPEEDR |= (3<<2*10); // GPIOA PIN10 Output speed (100MHz Very High speed
  GPIOA->AFR[1] |= (7<<8); // Connect GPIOA pin10 to AF7(USART1)
  
  RCC->APB2ENR |= (1<<4); // RCC_APB2ENR USART1 Enable
  
  USART_BRR_Configuration(19200); // USART Baud rate Configuration
  
  USART1->CR1 &= ~(1<<12); // USART_WordLength 8 Data bit
  USART1->CR1 &= ~(1<<10); // NO USART_Parity
  
  USART1->CR1 |= (1<<2); // 0x0004, USART_Mode_RX Enable
  USART1->CR1 |= (1<<3); // 0x0008, USART_Mode_Tx Enable
  
  USART1->CR2 &= ~(3<<12); // 0b00, USART_StopBits_1
  USART1->CR3 = 0x0000; // No HardwareFlowControl, No DMA
  
  USART1->CR1 |= (1<<5); // 0x0020, RXNE interrupt Enable
  NVIC->ISER[1] |= (1<<(37-32)); // Enable Interrupt USART1 (NVIC 37��)
  
  USART1->CR1 |= (1<<13); // 0x2000, USART1 Enable
}

void SerialSendChar(uint8_t Ch) // 1���� ������ �Լ�
{
  // USART_SR_TXE(1<<7)=0?, TX Buffer NOT Empty? 
  // TX buffer Empty���� ������ ��� ���(�۽� ������ ���±��� ���)
  while((USART1->SR & USART_SR_TXE) == RESET); 
  USART1->DR = (Ch & 0x01FF);	// ���� (�ִ� 9bit �̹Ƿ� 0x01FF�� masking)
}

void SerialSendString(char *str) // �������� ������ �Լ�
{
  while (*str != '\0') // ���Ṯ�ڰ� ������ ������ ����, ���Ṯ�ڰ� �����Ŀ��� ������ �޸� ���� �߻����ɼ� ����.
  {
    SerialSendChar(*str); // �����Ͱ� ����Ű�� ���� �����͸� �۽�
    str++; // ������ ��ġ ����
  }
}

// Baud rate ����
void USART_BRR_Configuration(uint32_t USART_BaudRate) // USART1 Baudrate ���� �Լ�
{ 
  uint32_t tmpreg = 0x00; // USARTDIV ���� ���� 0���� �ʱ�ȭ
  uint32_t APB2clock = 84000000; //PCLK2_Frequency
  uint32_t integerdivider = 0x00; // Mantissa�κ� ����� ���� �ӽ� ���� ����
  uint32_t fractionaldivider = 0x00; // fraction�κ� ����� ���� �ӽ� ���� ����
  
  // Find the integer part 
  if ((USART1->CR1 & USART_CR1_OVER8) != 0) // USART_CR1_OVER8=(1<<15)
    //  #define  USART_CR1_OVER8 ((uint16_t)0x8000) // USART Oversampling by 8 enable   
  { // USART1->CR1.OVER8 = 1 (8 oversampling)
    // Computing 'Integer part' when the oversampling mode is 8 Samples 
    integerdivider = ((25 * APB2clock) / (2 * USART_BaudRate));  // ���Ŀ� 100�� ���� ����(�Ҽ��� �ι�°�ڸ����� �����ϱ� ����)  
  }
  else // USART1->CR1.OVER8 = 0 (16 oversampling)
  {	// Computing 'Integer part' when the oversampling mode is 16 Samples 
    integerdivider = ((25 * APB2clock) / (4 * USART_BaudRate)); // ���Ŀ� 100�� ���� ����(�Ҽ��� �ι�°�ڸ����� �����ϱ� ����)    
  } // 100*(f_CK) / (8*2*Buadrate) = (25*f_CK)/(4*Buadrate)	
  tmpreg = (integerdivider / 100) << 4; // 4bit���� Mantissa�κ��̹Ƿ� 4��Ʈ ����Ʈ
  
  // Find the fractional part 
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4)); // fraction �κ� 10�� �ڸ����� 1�� �ڸ����� ������ �ؼ� ����
  
  // Implement the fractional part in the register 
  if ((USART1->CR1 & USART_CR1_OVER8) != 0)	// oversampling 8�̸� fraction �κ� 2bit�����̹Ƿ�
  {	// 8 oversampling
    tmpreg |= (((fractionaldivider * 8) + 50) / 100) & (0x07); // ��Ʈ ������ ������ �ؼ� ����
  }
  else // oversampling 16�̸� fraction �κ� 3bit�����̹Ƿ�
  {
    tmpreg |= (((fractionaldivider * 16) + 50) / 100) & (0x0F); // ��Ʈ �װ��� ������ �ؼ� ����
  }
  
  // Write to USART BRR register
  USART1->BRR = (uint16_t)tmpreg; // Baudrate resister�� ����
}

void USART1_IRQHandler(void) // USART1 ���ͷ�Ʈ �ڵ鷯 �Լ�
{
  if ( (USART1->SR & USART_SR_RXNE) ) // USART_SR_RXNE= 1? RX Buffer Full?
    // #define  USART_SR_RXNE ((uint16_t)0x0020)    //  Read Data Register Not Empty     
  {
    go_stop = (uint16_t)(USART1->DR & (uint16_t)0x01FF);	// ���ŵ� ���� ����
    LCD_DisplayChar(1, 18, go_stop); // ��ɾ� LCD ���
    if(go_stop == 'M') // ��ɾ Move�̸�
    {
      ADC3->CR2 |= (1 << 0); // ADC3 Enable
      TIM4->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
      TIM14->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
    }
    else if(go_stop == 'S') // ��ɾ Stop�̸�
    {
      ADC3->CR2 &= ~(1 << 0); // ADC3 Disable
      
      distance[0] = 0; // �Ÿ��� 0���� ��ȯ
      distance[1] = 1; // �Ÿ��� 1�� ��ȯ
      TIM4->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
      TIM14->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
      LCD_display2(); // �ٲ� �����Ϳ� ���� LCD ���
    }
    Fram_Write(1201, (uint8_t)go_stop); // ��ɾ� Fram�� 1201�ּҿ� ����
  } 
  // DR �� ������ SR.RXNE bit(flag bit)�� clear �ȴ�. �� clear �� �ʿ���� 
}

void EXTI_Init_(void) // �ܺ� ���ͷ�Ʈ ���� �Լ�
{
  RCC->AHB1ENR |=  0x00000080; // RCC_AHB1ENR : GPIOH(bit#7) Enable	
  RCC->APB2ENR |= (1 << 14); // SYSCFG Enable
  GPIOH->MODER &= ~(3 << 12 * 2); // GPIOH 12 : Input mode (reset state)
  GPIOH->MODER &= ~(3 << 14 * 2); // GPIOH 14 : Input mode (reset state)
  SYSCFG->EXTICR[3] |= (7 << 0); // EXTI12 portH match
  SYSCFG->EXTICR[3] |= (7 << 8); // EXTI14 portH match
  EXTI->FTSR |= (1 << 12); // EXTI12 set falling edge trigger
  EXTI->FTSR |= (1 << 14); // EXTI14 set falling edge trigger
  EXTI->IMR |= (1 << 12); // interrup mask
  EXTI->IMR |= (1 << 14); // interrup mask
  NVIC->ISER[1] |= (1 << (40 - 32)); // Enable Interrupt EXTI15_10 
}

void EXTI15_10_IRQHandler(void) // �ܺ� ���ͷ�Ʈ �ڵ鷯 �Լ�
{
  if(EXTI->PR & (1 << 12)) // EXTI12 ���ͷ�Ʈ
  {
    EXTI->PR |= (1 << 12); // EXTI->PR 1 �־ �ٽ� �ʱ�ȭ
    go_stop = 'M'; // ��ɾ� ����
    LCD_DisplayChar(1, 18, go_stop); // ��ɾ� LCD ���
    TIM4->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
    TIM14->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
    ADC3->CR2 |= (1 << 0); // ADC3 Enable
  }
  if(EXTI->PR & (1 << 14)) // EXTI14 ���ͷ�Ʈ
  {
    EXTI->PR |= (1 << 14); // EXTI->PR 1 �־ �ٽ� �ʱ�ȭ
    go_stop = 'S'; // ��ɾ� ����
    LCD_DisplayChar(1, 18, go_stop); // ��ɾ� LCD ���
    ADC3->CR2 &= ~(1 << 0); // ADC3 Disable
    distance[0] = 0; // �Ÿ��� 0���� ��ȯ
    distance[1] = 1; // �Ÿ��� 1�� ��ȯ
    LCD_display2(); // �ٲ� �����Ϳ� ���� LCD ���
    TIM4->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
    TIM14->CNT = 0; // ���� �̾����� ���� �ʱ�ȭ�ϱ� ����
  }
  Fram_Write(1201, (uint8_t)go_stop); // Fram 1201 �ּҿ� ��� ����
}

void DelayMS(unsigned short wMS) // MS ������ �Լ�
{
  register unsigned short i;
  
  for (i=0; i<wMS; i++)
    DelayUS(1000);		//1000us => 1ms
}

void DelayUS(unsigned short wUS) // MS ������ �Լ�
{
  volatile int Dly = (int)wUS*17;
  for(; Dly; Dly--);
}
