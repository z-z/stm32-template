#include "stm32f10x.h"
#include "stm32f10x_rcc.c"
#include "stm32f10x_gpio.c"

static __IO uint32_t TimingDelay;

void Delay_ms(__IO uint32_t nTime);

int main(void)
{
	int count;


	SysTick_Config(24000);

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	

	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOC, &gpio);

	while(1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		Delay_ms(1000);
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		for( count=0; count<8000000; count++) __NOP();
	}

	
}

//Функция временной задержки
void Delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

//Обработчик прерывания системного таймера
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}