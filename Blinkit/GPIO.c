/*
 * Copyright (c) 2022 
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "GPIO.h"
#include "CLOCK.h"
#include<stdio.h>


void GPIO_WritePin(GPIO_TypeDef *GPIOx,uint16_t GPIO_pin,GPIO_PinState PinState)
{
	if(PinState==GPIO_PIN_RESET)
	{
		GPIOx->BSRR |= (1<<(GPIO_pin+16));
	}
	else
	{
		GPIOx->BSRR |= (1<<GPIO_pin);
	}
}

void GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_InitTypeDef *GPIO_Init)
{
	int pos;
	if(GPIOx==GPIOA)
	{
		pos = 0;
	}
	else if(GPIOx==GPIOB)
	{
		pos = 1;
	}
	else if(GPIOx==GPIOC)
	{
		pos = 2;
	}
	else if(GPIOx==GPIOD)
	{
		pos = 3;
	}
	else if(GPIOx==GPIOE)
	{
		pos = 4;
	}
	else if(GPIOx==GPIOF)
	{
		pos = 5;
	}
	else if(GPIOx==GPIOG)
	{
		pos = 6;
	}
	else if(GPIOx==GPIOH)
	{
		pos = 7;
	}
	if(GPIO_Init)
	{
		RCC->AHB1ENR |= (1<<pos);
	}
	else
	{
		RCC->AHB1ENR |= (1<<pos);
	}
	int i;
	for(i = 0; i<GPIO_NUMBER;i++)
	{
		if(!(GPIO_Init->Pin&(1<<i)))
		{
			continue;
		}
		GPIOx->MODER   &= ~(GPIO_MODER_MODER0 << (i * 2U));
		GPIOx->MODER   |= ((GPIO_Init->Mode & GPIO_MODE) << (i * 2U));
		
		GPIOx->OTYPER  &= ~(GPIO_OTYPER_OT_0 << i);
		GPIOx->OTYPER  |= (((GPIO_Init->Mode & GPIO_OUTPUT_TYPE) >> 4U) << i);
		
		GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (i * 2U));
		GPIOx->OSPEEDR |= ((GPIO_Init->Speed) << (i * 2U));
		
		/* Activate the Pull-up or Pull down resistor for the current IO */
		GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (i * 2U)); 
		GPIOx->PUPDR |= ((GPIO_Init->Pull) << (i * 2U));  
	}
}


