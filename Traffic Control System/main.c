#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>
#include "CLOCK.h"
#include "USART.h"
#include "SYS_INIT.h"
#include "GPIO.h"
#include "TEST.h"

//Taking up and down cars in GPIOA pins

//car from Upper side of the board
int Upper_car[4];

//car from Lower side of the board
int Lower_car[4];


//Taking left and right cars in GPIOB pins

//car from Right side of the board
int Right_car[4];

//car from Left side of the board
int Left_car[4];

//Left to Right traffic lights will be in GPIOC pins
int Left_Right_Lights[4];


//Above to bellow traffic lights will be in GPIOC pins
int Up_Down_Lights[4];

int upper_car[4],lower_car[4],right_car[4],left_car[4],up_down_lights[4],left_right_lights[4];
int UPPER_CAR_FROM_PIN[4],LOWER_CAR_FROM_PIN[4],RIGHT_CAR_FROM_PIN[4],LEFT_CAR_FROM_PIN[4];

const static int Green_to_Yellow=5; 
const static int Yellow_to_Red=2;

int get_random() //random number generator function
{
	//srand(time(0));
	return abs(rand()%2);
}






static void update_upper_cars(void)
{
	GPIO_InitTypeDef LEFT_RIGHGT_RED_LIGHT;
	LEFT_RIGHGT_RED_LIGHT.Pin = GPIO_PIN_12;
	LEFT_RIGHGT_RED_LIGHT.Mode=GPIO_MODE_INPUT;
	LEFT_RIGHGT_RED_LIGHT.Speed=GPIO_SPEED_FREQ_HIGH;
	LEFT_RIGHGT_RED_LIGHT.Pull=GPIO_NOPULL;
	GPIO_Init(GPIOC,&LEFT_RIGHGT_RED_LIGHT);
	
	if(GPIOC->IDR&(1<<12))
	{
		upper_car[3]=0;
		upper_car[3]=upper_car[2];
		upper_car[2]=upper_car[1];
		upper_car[1]=get_random();
	}
	
}
static void update_lower_cars(void)
{
	GPIO_InitTypeDef LEFT_RIGHGT_RED_LIGHT;
	LEFT_RIGHGT_RED_LIGHT.Pin = GPIO_PIN_12;
	LEFT_RIGHGT_RED_LIGHT.Mode=GPIO_MODE_INPUT;
	LEFT_RIGHGT_RED_LIGHT.Speed=GPIO_SPEED_FREQ_HIGH;
	LEFT_RIGHGT_RED_LIGHT.Pull=GPIO_NOPULL;
	GPIO_Init(GPIOC,&LEFT_RIGHGT_RED_LIGHT);
	
	if(GPIOC->IDR&(1<<12))
	{
		lower_car[3]=0;
		lower_car[3]=lower_car[2];
		lower_car[2]=lower_car[1];
		lower_car[1]=get_random();
	}
	
}

static void update_right_cars(void)
{
	GPIO_InitTypeDef UP_DOWN_RED_LIGHT;
	UP_DOWN_RED_LIGHT.Pin = GPIO_PIN_10;
	UP_DOWN_RED_LIGHT.Mode=GPIO_MODE_INPUT;
	UP_DOWN_RED_LIGHT.Speed=GPIO_SPEED_FREQ_HIGH;
	UP_DOWN_RED_LIGHT.Pull=GPIO_NOPULL;
	GPIO_Init(GPIOC,&UP_DOWN_RED_LIGHT);
	
	if(GPIOC->IDR&(1<<10))
	{
		right_car[3]=0;
		right_car[3]=right_car[2];
		right_car[2]=right_car[1];
		right_car[1] = get_random();
	}
	
}
static void update_left_cars(void)
{
	GPIO_InitTypeDef UP_DOWN_RED_LIGHT;
	UP_DOWN_RED_LIGHT.Pin = GPIO_PIN_10;
	UP_DOWN_RED_LIGHT.Mode=GPIO_MODE_INPUT;
	UP_DOWN_RED_LIGHT.Speed=GPIO_SPEED_FREQ_HIGH;
	UP_DOWN_RED_LIGHT.Pull=GPIO_NOPULL;
	GPIO_Init(GPIOC,&UP_DOWN_RED_LIGHT);
	
	if(GPIOC->IDR&(1<<10))
	{
		left_car[3]=0;
		left_car[3]=left_car[2];
		left_car[2]=left_car[1];
		left_car[1]=get_random();
	}
	
}

int up_down_traffic_load(void) //check the traffic load of up down road
{
	
	int tot = 0;
	GPIO_InitTypeDef UP_THIRD_PIN,DOWN_THIRD_PIN;
	UP_THIRD_PIN.Pin = GPIO_PIN_0;
	UP_THIRD_PIN.Mode=GPIO_MODE_INPUT;
	UP_THIRD_PIN.Speed=GPIO_SPEED_FREQ_HIGH;
	UP_THIRD_PIN.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOC,&UP_THIRD_PIN);
	
	DOWN_THIRD_PIN.Pin = GPIO_PIN_1;
	DOWN_THIRD_PIN.Mode=GPIO_MODE_INPUT;
	DOWN_THIRD_PIN.Speed=GPIO_SPEED_FREQ_HIGH;
	DOWN_THIRD_PIN.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOC,&DOWN_THIRD_PIN);
	
	if(GPIOC->IDR&(1<<0))
	{
		tot++;
	}
	if(GPIOC->IDR&(1<<1))
	{
		tot++;
	}
	return tot;
}

int left_right_traffic_load(void) //check the traffic load of left right road
{
	int tot=0;
	GPIO_InitTypeDef LEFT_THIRD_PIN,RIGHT_THIRD_PIN;
	LEFT_THIRD_PIN.Pin = GPIO_PIN_12;
	LEFT_THIRD_PIN.Mode=GPIO_MODE_INPUT;
	LEFT_THIRD_PIN.Speed=GPIO_SPEED_FREQ_HIGH;
	LEFT_THIRD_PIN.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOA,&LEFT_THIRD_PIN);
	
	RIGHT_THIRD_PIN.Pin = GPIO_PIN_11;
	RIGHT_THIRD_PIN.Mode=GPIO_MODE_INPUT;
	RIGHT_THIRD_PIN.Speed=GPIO_SPEED_FREQ_HIGH;
	RIGHT_THIRD_PIN.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOA,&RIGHT_THIRD_PIN);
	
	if(GPIOA->IDR&(1<<12))
	{
		tot++;
	}
	if(GPIOA->IDR&(1<<11))
	{
		tot++;
	}
	return tot;
}

void update_cars(int now) //move all the car according to the traffic light
{
	if(now)
	{
		//move the left and right vehicles
		update_left_cars();
		update_right_cars();
		
		//if there is space in up and down direction , cars can move in to fill up those gap
		
		if(upper_car[3]==0)
		{
			upper_car[3]=upper_car[2];
			upper_car[2]=0;
		}
		if(upper_car[2]==0)
		{
			upper_car[2]=upper_car[1];
			upper_car[1]=0;
		}
		if(upper_car[1]==0)
		{
			upper_car[1]=get_random();
		}
		if(lower_car[3]==0)
		{
			lower_car[3]=lower_car[2];
			lower_car[2]=0;
		}
		if(lower_car[2]==0)
		{
			lower_car[2]=lower_car[1];
			lower_car[1]=0;
		}
		if(lower_car[1]==0)
		{
			lower_car[1]=get_random();
		}
	}
	else
	{
		//move in up and down direction
		update_upper_cars();
		update_lower_cars();
		
		//if there is space in left and right direction , cars can move in to fill up those gap
		if(left_car[3]==0)
		{
			left_car[3]=left_car[2];
			left_car[2]=0;
		}
		if(left_car[2]==0)
		{
			left_car[2]=left_car[1];
			left_car[1]=0;
		}
		if(left_car[1]==0)
		{
			left_car[1]=get_random();
		}
		if(right_car[3]==0)
		{
			right_car[3]=right_car[2];
			right_car[2]=0;
		}
		if(right_car[2]==0)
		{
			right_car[2]=right_car[1];
			right_car[1]=0;
		}
		if(right_car[1]==0)
		{
			right_car[1]=get_random();
		}
	}
}



void init_lights(void) // initially put a green light on left to right road and red light to up to down road
{
	up_down_lights[3]=1;
	left_right_lights[1]=1;
}

void init_cars(void) // randomly initialize some car to the road
{
	int i;
	for(i=1;i<4;i++)
	{
		left_car[i]=get_random();
		right_car[i]=get_random();
		upper_car[i]=get_random();
		lower_car[i]=get_random();
	}
}


void init_pins(void) //initialize all the pin numbers and turn on the necessary pins
{
	Upper_car[1] = 5;
	Upper_car[2] = 6;
	Upper_car[3] = 7;
	
	Lower_car[1] = 0;
	Lower_car[2] = 1;
	Lower_car[3] = 4;
	
	Right_car[1] = 13;
	Right_car[2] = 14;
	Right_car[3] = 15;
	
	Left_car[1] = 3;
	Left_car[2] = 4;
	Left_car[3] = 5;
	
	Up_Down_Lights[1] = 5;
	Up_Down_Lights[2] = 6;
	Up_Down_Lights[3] = 8;
	
	Left_Right_Lights[1] = 3;
	Left_Right_Lights[2] = 2;
	Left_Right_Lights[3] = 9;
	
	GPIO_InitTypeDef LRlight_cars,UDlight_cars,Traffic_lights;
	
	//       GPIOA    lower_car_1  lower_car_2  lower_car_3  upper_car_1 upper_car_2  upper_car_3
	LRlight_cars.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |GPIO_PIN_6 | GPIO_PIN_7;
	
	LRlight_cars.Mode=GPIO_MODE_OUTPUT_PP;
	LRlight_cars.Speed=GPIO_SPEED_FREQ_HIGH;
	LRlight_cars.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOA,&LRlight_cars);
	
	//        GPIOB    Right_car_1   Right_car_2   Right_car_3   Left_car_1  Left_car_2   Left_car_3
	UDlight_cars.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	
	UDlight_cars.Mode=GPIO_MODE_OUTPUT_PP;
	UDlight_cars.Speed=GPIO_SPEED_FREQ_HIGH;
	UDlight_cars.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOB,&UDlight_cars);
	
	//          GPIOC      L-R-Green   L-R-Yellow    L-R-Red       U-D-Green   U-D-Yellow   U-D-Red
	Traffic_lights.Pin = GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_9 | GPIO_PIN_5 |GPIO_PIN_6 | GPIO_PIN_8;
	
	Traffic_lights.Mode=GPIO_MODE_OUTPUT_PP;
	Traffic_lights.Speed=GPIO_SPEED_FREQ_HIGH;
	Traffic_lights.Pull=GPIO_NOPULL;
	
	GPIO_Init(GPIOC,&Traffic_lights);
}


void turn_on_the_lights(void) //handy function that will turn on all the lights at it's need
{
	int i;
	for(i =1 ;i<4;i++)
	{
		GPIO_WritePin(GPIOB,(uint16_t)Left_car[i],left_car[i]);
		GPIO_WritePin(GPIOB,(uint16_t)Right_car[i],right_car[i]);
		GPIO_WritePin(GPIOA,(uint16_t)Upper_car[i],upper_car[i]);
		GPIO_WritePin(GPIOA,(uint16_t)Lower_car[i],lower_car[i]);
		GPIO_WritePin(GPIOC,(uint16_t)Up_Down_Lights[i],up_down_lights[i]);
		GPIO_WritePin(GPIOC,(uint16_t)Left_Right_Lights[i],left_right_lights[i]);
	}
	
}


int main()
{
	initClock();
	sysInit();
	UART2_Config();
	
	//check_Light(GPIOA,11);
	
	init_lights();
	init_cars();
	init_pins();
	
	int now = 1;
	int tme = 0;
	int extra =0;
	
	while(1)
	{
		update_cars(now);
		
		if(now) //if left to right side is not in red
		{
			//if green is on
			if(left_right_lights[1])
			{
				if(extra <= 0 && left_right_traffic_load()>up_down_traffic_load())
				{
					extra = 15;
				}
				up_down_lights[1]=up_down_lights[2]=0; //just making unnecessary lights turn off just to be safe :3
				//keep the other red light on
				up_down_lights[3]=1;
				//if the timer is over ,turn off the green light and turn on the yellow light
				if(tme>=Green_to_Yellow+extra)
				{
					left_right_lights[2]=1;
					left_right_lights[1]=0;
					tme=0;
					extra=0;
				}
			}
			//else if the yellow light is on
			else if(left_right_lights[2])
			{
				up_down_lights[1]=up_down_lights[2]=0; //just making unnecessary lights turn off just to be safe :3
				//keep the other red light on
				up_down_lights[3]=1;
				//if the timer is over , then make it red light and make the other red light to green light
				if(tme>=Yellow_to_Red)
				{
					left_right_lights[1]=left_right_lights[2]=0; //just making unnecessary lights turn off just to be safe :3
					left_right_lights[3]=1;
					up_down_lights[2] = up_down_lights[3] = 0; //just making unnecessary lights turn off just to be safe :3
					up_down_lights[1] = 1;
					tme=0;
					now^=1;
					extra=0;
				}
			}
		}
		
		else
		{
			//if green is on
			if(up_down_lights[1])
			{
				if(extra <= 0 && left_right_traffic_load()<up_down_traffic_load())
				{
					extra = 15;
				}
				left_right_lights[1]=left_right_lights[2]=0; //just making unnecessary lights turn off just to be safe :3
				//keep the other red light on
				left_right_lights[3]=1;
				//if the timer is over ,turn off the green light and turn on the yellow light
				if(tme>=Green_to_Yellow+extra)
				{
					up_down_lights[2]=1;
					up_down_lights[1]=0;
					tme=0;
					extra=0;
				}
			}
			else if(up_down_lights[2])
			{
				left_right_lights[1]=left_right_lights[2]=0;  //just making unnecessary lights turn off just to be safe :3
				//keep the other red light on
				left_right_lights[3]=1;
				//if the timer is over , then make it red light and make the other red light to green light
				if(tme>=Yellow_to_Red)
				{
					up_down_lights[1]=up_down_lights[2]=0;
					up_down_lights[3]=1;
					left_right_lights[2] = left_right_lights[3] = 0;
					left_right_lights[1] = 1;
					tme=0;
					now^=1;
					extra=0;
				}
			}
		}
		
		turn_on_the_lights();
		tme++;
		ms_delay(1000);
	}

	
	return 0;
}