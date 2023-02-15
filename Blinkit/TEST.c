#include "TEST.h"
#include "GPIO.h"

void check_Light(GPIO_TypeDef *GPIOx,uint16_t GPIO_pin)
{
	GPIO_InitTypeDef blinkPin;
	if(GPIO_pin==0)
	{
		blinkPin.Pin = GPIO_PIN_0;
	}
	else if(GPIO_pin==1)
	{
		blinkPin.Pin = GPIO_PIN_1;
	}
	else if(GPIO_pin==2)
	{
		blinkPin.Pin = GPIO_PIN_2;
	}
	else if(GPIO_pin==3)
	{
		blinkPin.Pin = GPIO_PIN_3;
	}
	else if(GPIO_pin==4)
	{
		blinkPin.Pin = GPIO_PIN_4;
	}
	else if(GPIO_pin==5)
	{
		blinkPin.Pin = GPIO_PIN_5;
	}
	else if(GPIO_pin==6)
	{
		blinkPin.Pin = GPIO_PIN_6;
	}
	else if(GPIO_pin==7)
	{
		blinkPin.Pin = GPIO_PIN_7;
	}
	else if(GPIO_pin==8)
	{
		blinkPin.Pin = GPIO_PIN_8;
	}
	else if(GPIO_pin==9)
	{
		blinkPin.Pin = GPIO_PIN_9;
	}
	else if(GPIO_pin==10)
	{
		blinkPin.Pin = GPIO_PIN_10;
	}
	else if(GPIO_pin==11)
	{
		blinkPin.Pin = GPIO_PIN_11;
	}
	else if(GPIO_pin==12)
	{
		blinkPin.Pin = GPIO_PIN_12;
	}
	else if(GPIO_pin==13)
	{
		blinkPin.Pin = GPIO_PIN_13;
	}
	else if(GPIO_pin==14)
	{
		blinkPin.Pin = GPIO_PIN_14;
	}
	else if(GPIO_pin==15)
	{
		blinkPin.Pin = GPIO_PIN_15;
	}
	
	blinkPin.Mode = GPIO_MODE_OUTPUT_PP;
	blinkPin.Speed = GPIO_SPEED_FREQ_LOW;
	blinkPin.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOx,&blinkPin);
	
	int curState = 0;
	
	while(1)
	{
		if(curState)
		{
			GPIO_WritePin(GPIOA,GPIO_pin,GPIO_PIN_SET);
		}
		else
		{
			GPIO_WritePin(GPIOA,GPIO_pin,GPIO_PIN_RESET);
		}
		ms_delay(500);
		curState^=1;
	}

}