#include<stdio.h>
#include "CLOCK.h"
#include "USART.h"
#include "SYS_INIT.h"
#include "GPIO.h"

int main()
{
	initClock();
	sysInit();
	UART2_Config();
	
	GPIO_InitTypeDef blinkPin;
	blinkPin.Pin = GPIO_PIN_9;
	blinkPin.Mode = GPIO_MODE_OUTPUT_PP;
	blinkPin.Speed = GPIO_SPEED_FREQ_LOW;
	blinkPin.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOC,&blinkPin);
	
	int curState = 0;
	
	while(1)
	{
		if(curState)
		{
			GPIO_WritePin(GPIOC,9,GPIO_PIN_SET);
		}
		else
		{
			GPIO_WritePin(GPIOC,9,GPIO_PIN_RESET);
		}
		ms_delay(1000);
		curState^=1;
	}

	
	return 0;
}