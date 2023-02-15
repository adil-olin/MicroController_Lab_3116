/*
 *This header file was made by Afser Adil Olin
 *for testing any Pin if needed;
 *check_Light() function takes two parameter, first one is which type of pinset you want to test like, GPIOA,GPIOB...etc
 *second parameter takes which number pin you want to test
 *so if you want to test GPIOA-5 pin just call the function as check_Light(GPIOA,5)
 *it will make that pin turn on or off after .5 second of interval
 */


#ifndef __TEST_H
#define __TEST_H
#include "stm32f446xx.h"
#ifdef __cplusplus
extern "C" {
#endif

void check_Light(GPIO_TypeDef *GPIOx,uint16_t GPIO_pin);

#ifdef __cplusplus
}
#endif
#endif
