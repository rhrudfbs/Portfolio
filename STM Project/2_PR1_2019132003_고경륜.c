/////////////////////////////////////////////////////////////
// PR1: Car Tracking system
// 제출자: 2019132003 고경륜
// 주요 내용
// - 전기자동차 2대가 길을 따라 운행하고 있다. 선도차는 random
//   하게 운행하고, 추종차는 선도차와의 거리와 인도와의 거리를
//   계속 측정하면서 속도와 방향을 조정하며 선도차를 따라가야
//   한다. 그에 따른 추종차 시스템 프로그래밍
// - 거리센서1: 마이컴키트상의 가변저항, PA1(ADC3_IN1)
// - 거리센서2: 40pin Box header connector에 연결된 외부 가변저항, PF3(ADC3_IN9)
// - 추종차 엔진: PB7(TIM4_CH2(PWM mode)), LED로 PWM 변화확인
// - 추종차 핸들: PF9(TIM14_CH1(PWM mode)), Buzzer로 PWM 변화확인
// - Off-line 추종차 시동: Move-key(SW4(EXTI12)), Stop-key(SW6(EXTI14))
// - 원격(PC 통신프로그램) 추종차 시동: Move-key(‘M’), Stop-key(‘S’)
// - 거리값 표시: GLCD(D), PC
// - 추종차 속도 표시: GLCD(DR)
// - 추종차 방향 표시: GLCD(‘L’, ‘R’, ‘F’)
/////////////////////////////////////////////////////////////


#include "stm32f4xx.h" // stm에 대한 헤더파일 추가
#include "GLCD.h" //LCD를 사용하기 위해 헤더파일 추가
#include "FRAM.h" //FRAM을 사용하기 위해 헤더파일 추가

void TIM1_Init(void); // TIM1 설정 함수
void TIM4_Init(void); // TIM4 설정 함수
void TIM14_Init(void); // TIM14 설정 함수
void _ADC3_Init(void); // ADC3 설정 함수
void DMA2_Init_(void); // DMA2 설정 함수
void USART1_Init(void); // USART1 설정 함수
void EXTI_Init_(void); // 외부 인터럽트 설정 함수
void USART_BRR_Configuration(uint32_t USART_BaudRate); // USART1 Baudrate 설정 함수

void LCD_display1(void); // 초기 변하지 않는 LCD 출력 함수
void LCD_display2(void); // 변경하는 값에 따른 LCD 출력 함수

void Set_speed(uint32_t D); // 추종차량 속도 설정 함수(PWM Duty Ratio 변경)
void Set_Dir(uint32_t D); // 추종차량 방향 설정 함수(PWM Duty Ratio 변경)

void SerialSendChar(uint8_t c); // USART1 8bit 한 글자 전송 함수
void SerialSendString(char *s); // USART1 문자열 전송 함수

void DelayMS(unsigned short wMS); // MS 딜레이 함수
void DelayUS(unsigned short wUS); // MS 딜레이 함수

uint16_t get_distance[2] = {0, 0}; // ADC3로 받은 데이터 저장 변수 배열
float distance_to_voltage[2] = {0, 0}; // ADC로 받은 데이터 전압으로 변환 후 저장 변수 배열
uint32_t distance[2] = {0, 0}; // 전압값 거리값으로 변환 후 저장 변수 배열
char go_stop = 'S'; // 명령어 저장 변수

int main(void)
{
  LCD_Init(); // LCD 구동 함수
  DelayMS(10); // LCD구동 딜레이
  
  Fram_Init(); // Fram을 사용하기 위한 초기화 작업 함수(H/W)
  Fram_Status_Config(); // Fram S/W 초기화
  
  LCD_display1(); // 초기 변하지 않는 LCD 출력 함수

  TIM1_Init(); // TIM1 설정 함수
  TIM4_Init(); // TIM4 설정 함수
  TIM14_Init(); // TIM14 설정 함수
  _ADC3_Init(); // ADC3 설정 함수
  DMA2_Init_(); // DMA2 설정 함수
  USART1_Init(); // USART1 설정 함수
  EXTI_Init_(); // 외부 인터럽트 설정 함수
  
  go_stop = (char)Fram_Read(1201); // Fram 1201주소에 저장되어 있는 8bit 데이터 읽어서 명령어 저장 변수에 저장
  if(go_stop != 'M' && go_stop != 'S') // Fram 1201주소에 쓰레기값 저장 시 예외 처리
  {
    go_stop = 'S'; // Stop 명령
  }
  
  if(go_stop == 'S') // Stop 명령이면
  {
    ADC3->CR2 &= ~(1 << 0); // ADC3 disable
    distance[0] = 0; // 거리값 0으로 전환
    distance[1] = 1; // 거리값 1로 전환
    TIM4->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
    TIM14->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
  }
  else if(go_stop == 'M') // Move 명령이면
  {
    distance[0] = 0; // 거리값 0으로 전환
    distance[1] = 1; // 거리값 1로 전환
    TIM4->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
    TIM14->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
    ADC3->CR2 |= (1 << 0); // ADC3 Enable
  }
  
  LCD_DisplayChar(1, 18, go_stop); // 명령어 LCD에 출력
  LCD_display2(); // 변한 데이터들을 바탕으로 LCD 출력
  
  while(1) // 무한 반복
  {
    
  }
}

void LCD_display1(void) // 변하지 않는 LCD 출력 부분 출력
{
  LCD_Clear(RGB_WHITE); // 화면 클리어
  LCD_SetFont(&Gulim8); // 폰트 : 굴림 8
  LCD_SetBackColor(RGB_WHITE); // 글자배경색 : White
  LCD_SetTextColor(RGB_BLACK); // 글자색 : Black
  
  LCD_DisplayText(0, 0, "GGR 2019132003"); // 이름 이니셜, 학번 출력
  LCD_DisplayText(1, 0, "Tracking Car"); // 프로젝트명 출력
  LCD_DisplayText(2, 0, "D1:"); // 앞 차와의 거리 표시를 위한 칸
  LCD_DisplayText(3, 0, "D2:"); // 인도와의 거리 표시를 위한 칸
  LCD_DisplayText(4, 0, "SP(DR):  %DIR(DR):"); // 차량속도, 방향(PWM Duty Ratio) 표시를 위한 칸
  LCD_SetTextColor(RGB_BLUE); // 글자색 파란색으로 변경
}

void LCD_display2(void) // 변하는 데이터들에 대한 LCD 출력 함수
{
  if(distance[0] >= 10) // 만약 앞 차와의 거리가 10보다 크거나 같으면
  {
    LCD_DisplayChar(2, 17, distance[0] / 10 + 48); // 10의 자리수 아스키 코드로 변환 후 출력
    LCD_DisplayChar(2, 18, distance[0] % 10 + 48); // 1의 자리수 아스키 코드로 변환 후 출력
  }
  else // 그 외에
  {
    LCD_DisplayChar(2, 17, ' '); // 10의 자리수 지우기
    LCD_DisplayChar(2, 18, distance[0] + 48); // 1의 자리수 아스키 코드로 변환 후 출력
  }
  
  LCD_DisplayChar(3, 18, distance[1] + 48); // 인도와의 거리 아스키 코드로 변환 후 출력

  LCD_SetBrushColor(RGB_WHITE); // 브러쉬 색 하얀색으로 변환
  LCD_DrawFillRect(25, 27, 105, 10); // 앞 차와의 거리 출력 막대기 지우기 (빨간색 막대 지우기)
  LCD_DrawFillRect(25, 40, 105, 10); // 인도와의 거리 출력 막대기 지우기 (초록색 막대 지우기)
  LCD_SetBrushColor(RGB_RED); // 브러쉬 색 빨간색으로 변환
  LCD_DrawFillRect(25, 27, distance[0] * 105 / 19, 10); // 앞 차와의 거리 출력 막대기 그리기 (빨간색 막대 그리기)
  LCD_SetBrushColor(RGB_GREEN); // 브러쉬 색 초록색으로 변환
  LCD_DrawFillRect(25, 40, (distance[1] + 1) * 105 / 4, 10); // 인도와의 거리 출력 막대기 그리기 (초록색 막대 그리기)
  Set_speed(distance[0]); // 앞 차와의 거리에 따른 속도, LCD 변경(TIM4 PWM Duty Ratio 변경)
  Set_Dir(distance[1]); // 인도와의 거리에 따른 방향, LCD 변경(TIM14 PWM Duty Ratio 변경)
}

void TIM1_Init(void) // TIM1 설정 함수
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
  
  TIM1->CCR3 = 2000; // Counter compare할 수 2000 설정
  
  TIM1->DIER |= (1 << 3); // TIM1 CC3 interrupt enable
  NVIC->ISER[0] |= (1 << 27); // TIM1_CC interrupt handler
  
  TIM1->CR1 |= (1 << 0); // TIM1 disable
}

void TIM1_CC_IRQHandler(void)
{
  TIM1->SR &= ~(1 << 3); // set interrupt flag to 0
  if(distance[0] >= 10) // 앞 차와의 거리가 10보다 크면
  {
    char str[5] = {distance[0] / 10 + 48, distance[0] % 10 + 48, 'm', '\n', '\0'}; // 문자 배열에 거리값 데이터 저장 후 정해진 데이터 구조로 문자열 저장
    SerialSendString(str); // USART1으로 문자열 전송
  }
  else // 그 외에
  {
    char str[4] = {distance[0] + 48,  'm', '\n', '\0'}; // 문자 배열에 거리값 데이터 저장 후 정해진 데이터 구조로 문자열 저장
    SerialSendString(str); // USART1으로 문자열 전송
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
  TIM4->CCMR1 &= ~(1 << 11); // OC2 preload disable -> 즉각적인 반응을 위해 off
  TIM4->CCMR1 |= (6 << 12); // Set PWM mode1
  
  TIM4->CCER |= (1 << 4); // CC2 output enable
  TIM4->CCER &= ~(1 << 5); // CC2 output active high
  
  TIM4->CCR2 = 0; // 초기 속도 0으로 설정 DR = 0%
  
  TIM4->CR1 |= (1 << 0); // TIM4 Enable
}

void TIM14_Init(void) // TIM14 설정 함수
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
  TIM14->CCMR1 &= ~(1 << 3); // OC1 preload disable ->즉각적인 반응을 위해 off
  TIM14->CCMR1 |= (6 << 4); // Set PWM mode1
  
  TIM14->CCER |= (1 << 0); // CC1 output enable
  TIM14->CCER &= ~(1 << 1); // CC1 output active high
  
  TIM14->CCR1 = 0; //초기 설정 DR = 0%
  
  TIM14->CR1 |= (1 << 0); // TIM14 Enable
}

void Set_speed(uint32_t D) // 앞 차와의 거리에 따른 속도, LCD 출력 변경 함수
{
  if(D == 0) // 거리가 0이라면
  {
    TIM4->CCR2 = 0; // DR 10%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "00"); // LCD DR 출력
  }
  else if(D >= 3 && D <= 4) // 거리가 3 or 4라면
  {
    TIM4->CCR2 = 5000; // DR 10%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "10"); // LCD DR 출력
  }
  else if(D >= 5 && D <= 6) // 거리가 5 or 6이라면
  {
    TIM4->CCR2 = 10000; // DR 20%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "20"); // LCD DR 출력
  }
  else if(D >= 7 && D <= 8) // 거리가 7 or 8이라면
  {
    TIM4->CCR2 = 15000; // DR 30%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "30"); // LCD DR 출력
  }
  else if(D >= 9 && D <= 10) // 거리가 9 or 10이라면
  {
    TIM4->CCR2 = 20000; // DR 40%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "40"); // LCD DR 출력
  }
  else if(D >= 11 && D <= 12) // 거리가 11 or 12라면
  {
    TIM4->CCR2 = 25000; // DR 50%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "50"); // LCD DR 출력
  }
  else if(D >= 13 && D <= 14) // 거리가 13 or 14라면
  {
    TIM4->CCR2 = 30000; // DR 60%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "60"); // LCD DR 출력
  }
  else if(D >= 15 && D <= 16) // 거리가 15 or 16이라면
  {
    TIM4->CCR2 = 35000; // DR 70%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "70"); // LCD DR 출력
  }
  else if(D >= 17 && D <= 18) // 거리가 17 or 18이라면
  {
    TIM4->CCR2 = 40000; // DR 80%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "80"); // LCD DR 출력
  }
  else if(D == 19) // 거리가 19라면
  {
    TIM4->CCR2 = 45000; // DR 90%, PWM1 mode -> High state before CC
    LCD_DisplayText(4, 7, "90"); // LCD DR 출력
  }
  else // 예외처리
  {
    TIM4->CCR2 = 0; // 예외처리
    LCD_DisplayText(4, 7, " 00"); // LCD DR 출력
  }
}

void Set_Dir(uint32_t D) // 인도와의 거리에 따른 방향, LCD 출력 변경 함수
{
  if(D == 0) // 거리가 0이라면
  {
    LCD_DisplayChar(4, 18, 'R'); // LCD 방향 출력
    TIM14->CCR1 = 24; // DR 30%, PWM1 mode -> High state before CC
  }
  else if(D == 1) // 거리가 1이라면
  {
    LCD_DisplayChar(4, 18, 'F'); // LCD 방향 출력
    TIM14->CCR1 = 0; // DR 0%, PWM1 mode -> High state before CC
  }
  else if(D == 2 || D == 3) // 거리가 2 or 3이라면
  {
    LCD_DisplayChar(4, 18, 'L'); // LCD 방향 출력
    TIM14->CCR1 = 72; // DR 90%, PWM1 mode -> High state before CC
  }
  else TIM14->CCR1 = 0; // 예외처리
}

void _ADC3_Init(void) // ADC3 설정 함수
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

void ADC_IRQHandler(void) // ADC 인터럽트 핸들러
{
  ADC3->SR &= ~(1 << 1); // EOC flag clear
  distance_to_voltage[0] = (float)get_distance[0] * (float)3.3 / (float)1023; // 10bit 분해능에 따라서 전압으로 변환
  distance[0] = (uint32_t)(distance_to_voltage[0] * 5) + 3; // 주어진 거리값 공식에 따른 계산
  distance_to_voltage[1] = (float)get_distance[1] * (float)3.3 / (float)1023; // 10bit 분해능에 따라서 전압으로 변환
  distance[1] = (uint32_t)distance_to_voltage[1]; // 주어진 거리값 공식에 따른 계산
  
  Set_speed(distance[0]); // 추종차량 속도 설정 함수(PWM Duty Ratio 변경)
  Set_Dir(distance[1]); // 추종차량 방향 설정 함수(PWM Duty Ratio 변경)
  
  LCD_display2(); // 바뀐 데이터에 따른 LCD 출력 함수
}

void DMA2_Init_(void) // DMA2 설정 함수
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

void USART1_Init(void) // USART1 설정 함수
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
  NVIC->ISER[1] |= (1<<(37-32)); // Enable Interrupt USART1 (NVIC 37번)
  
  USART1->CR1 |= (1<<13); // 0x2000, USART1 Enable
}

void SerialSendChar(uint8_t Ch) // 1문자 보내기 함수
{
  // USART_SR_TXE(1<<7)=0?, TX Buffer NOT Empty? 
  // TX buffer Empty되지 않으면 계속 대기(송신 가능한 상태까지 대기)
  while((USART1->SR & USART_SR_TXE) == RESET); 
  USART1->DR = (Ch & 0x01FF);	// 전송 (최대 9bit 이므로 0x01FF과 masking)
}

void SerialSendString(char *str) // 여러문자 보내기 함수
{
  while (*str != '\0') // 종결문자가 나오기 전까지 구동, 종결문자가 나온후에도 구동시 메모리 오류 발생가능성 있음.
  {
    SerialSendChar(*str); // 포인터가 가르키는 곳의 데이터를 송신
    str++; // 포인터 수치 증가
  }
}

// Baud rate 설정
void USART_BRR_Configuration(uint32_t USART_BaudRate) // USART1 Baudrate 설정 함수
{ 
  uint32_t tmpreg = 0x00; // USARTDIV 저장 변수 0으로 초기화
  uint32_t APB2clock = 84000000; //PCLK2_Frequency
  uint32_t integerdivider = 0x00; // Mantissa부분 계산을 위해 임시 저장 변수
  uint32_t fractionaldivider = 0x00; // fraction부분 계산을 위해 임시 저장 변수
  
  // Find the integer part 
  if ((USART1->CR1 & USART_CR1_OVER8) != 0) // USART_CR1_OVER8=(1<<15)
    //  #define  USART_CR1_OVER8 ((uint16_t)0x8000) // USART Oversampling by 8 enable   
  { // USART1->CR1.OVER8 = 1 (8 oversampling)
    // Computing 'Integer part' when the oversampling mode is 8 Samples 
    integerdivider = ((25 * APB2clock) / (2 * USART_BaudRate));  // 공식에 100을 곱한 곳임(소수점 두번째자리까지 유지하기 위함)  
  }
  else // USART1->CR1.OVER8 = 0 (16 oversampling)
  {	// Computing 'Integer part' when the oversampling mode is 16 Samples 
    integerdivider = ((25 * APB2clock) / (4 * USART_BaudRate)); // 공식에 100을 곱한 곳임(소수점 두번째자리까지 유지하기 위함)    
  } // 100*(f_CK) / (8*2*Buadrate) = (25*f_CK)/(4*Buadrate)	
  tmpreg = (integerdivider / 100) << 4; // 4bit부터 Mantissa부분이므로 4비트 시프트
  
  // Find the fractional part 
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4)); // fraction 부분 10의 자리수와 1의 자리수만 남도록 해서 저장
  
  // Implement the fractional part in the register 
  if ((USART1->CR1 & USART_CR1_OVER8) != 0)	// oversampling 8이면 fraction 부분 2bit까지이므로
  {	// 8 oversampling
    tmpreg |= (((fractionaldivider * 8) + 50) / 100) & (0x07); // 비트 세개만 남도록 해서 저장
  }
  else // oversampling 16이면 fraction 부분 3bit까지이므로
  {
    tmpreg |= (((fractionaldivider * 16) + 50) / 100) & (0x0F); // 비트 네개만 남도록 해서 저장
  }
  
  // Write to USART BRR register
  USART1->BRR = (uint16_t)tmpreg; // Baudrate resister에 저장
}

void USART1_IRQHandler(void) // USART1 인터럽트 핸들러 함수
{
  if ( (USART1->SR & USART_SR_RXNE) ) // USART_SR_RXNE= 1? RX Buffer Full?
    // #define  USART_SR_RXNE ((uint16_t)0x0020)    //  Read Data Register Not Empty     
  {
    go_stop = (uint16_t)(USART1->DR & (uint16_t)0x01FF);	// 수신된 문자 저장
    LCD_DisplayChar(1, 18, go_stop); // 명령어 LCD 출력
    if(go_stop == 'M') // 명령어가 Move이면
    {
      ADC3->CR2 |= (1 << 0); // ADC3 Enable
      TIM4->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
      TIM14->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
    }
    else if(go_stop == 'S') // 명령어가 Stop이면
    {
      ADC3->CR2 &= ~(1 << 0); // ADC3 Disable
      
      distance[0] = 0; // 거리값 0으로 전환
      distance[1] = 1; // 거리값 1로 전환
      TIM4->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
      TIM14->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
      LCD_display2(); // 바뀐 데이터에 대한 LCD 출력
    }
    Fram_Write(1201, (uint8_t)go_stop); // 명령어 Fram에 1201주소에 저장
  } 
  // DR 을 읽으면 SR.RXNE bit(flag bit)는 clear 된다. 즉 clear 할 필요없음 
}

void EXTI_Init_(void) // 외부 인터럽트 설정 함수
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

void EXTI15_10_IRQHandler(void) // 외부 인터럽트 핸들러 함수
{
  if(EXTI->PR & (1 << 12)) // EXTI12 인터럽트
  {
    EXTI->PR |= (1 << 12); // EXTI->PR 1 넣어서 다시 초기화
    go_stop = 'M'; // 명령어 변경
    LCD_DisplayChar(1, 18, go_stop); // 명령어 LCD 출력
    TIM4->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
    TIM14->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
    ADC3->CR2 |= (1 << 0); // ADC3 Enable
  }
  if(EXTI->PR & (1 << 14)) // EXTI14 인터럽트
  {
    EXTI->PR |= (1 << 14); // EXTI->PR 1 넣어서 다시 초기화
    go_stop = 'S'; // 명령어 변경
    LCD_DisplayChar(1, 18, go_stop); // 명령어 LCD 출력
    ADC3->CR2 &= ~(1 << 0); // ADC3 Disable
    distance[0] = 0; // 거리값 0으로 전환
    distance[1] = 1; // 거리값 1로 전환
    LCD_display2(); // 바뀐 데이터에 대한 LCD 출력
    TIM4->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
    TIM14->CNT = 0; // 전에 이어지던 동작 초기화하기 위함
  }
  Fram_Write(1201, (uint8_t)go_stop); // Fram 1201 주소에 명령 저장
}

void DelayMS(unsigned short wMS) // MS 딜레이 함수
{
  register unsigned short i;
  
  for (i=0; i<wMS; i++)
    DelayUS(1000);		//1000us => 1ms
}

void DelayUS(unsigned short wUS) // MS 딜레이 함수
{
  volatile int Dly = (int)wUS*17;
  for(; Dly; Dly--);
}
