#include "pwm.h"

int main (void) {

	RCC->APB1ENR |= (1<<0); //Timer 2 clock peripheral enabled
	RCC->APB2ENR |= (1<<2); //GPIOA clock peripheral enabled

	//Resetting pin 0,1,2,3
	GPIOA->CRL &= ~(0xFFFF); // 0xFFFF means 0000 0000 0000 0000 1111 1111 1111 1111

	//Configuring pin 0,1,2,3
	GPIOA->CRL |= (0xB<<0)	| // 0xB means 1011
				  (0xB<<4)	|
				  (0xB<<8)	|
				  (0xB<<12); /* (0xB<<0)|(0xB<<4)|(0xB<<8)|(0xB<<12) means 0xBBBB which
				  	  	  	  	  represents 0000 0000 0000 0000 1011 1011 1011 1011*/

	//Setting up timer 2
	TIM2->PSC = 71; /*Hardware always add a 1 to the value we write here, so write 71, we need result 72
					For ease in calc, we want a round number for a clock to count,
					here the clock will count 1M times/second (72MHz/72). */
	TIM2->ARR = 2499; /*this defines after how many cycles/count we want the timer to reset,
						since we want the clock to reset after 400count(400Hz),
						so after each 2500 cycles the timer will reset
						>> 0 - 2499 gives you 2500 total steps(1MHz/2500 = 400Hz)
						>> 1,000,000 ticks/sec divided by 2500 steps = exactly 400Hz PWM cycle rate
						CCR=Capture/Compare Register
						*/

	//CCMR=Capture/Compare Mode Register | Input Capture & Output Compare
	//OCxM=Output Compare Mode
	//TIMx Capture/Compare Mode Register 1 controls Channel 1 & 2
	//TIMx Capture/Compare Mode Register 2 controls Channel 3 & 4

	//Resetting output compare, OC1M & OC2M in one shot
	TIM2->CCMR1 &= ~((0x7<<12)|(0x7<<4));//0x7=111, and | means combining into 1 clean pattern before applying to register
	//Configuring channel 1 & 2 to PWM mode 1 with bin 110
	TIM2->CCMR1 |= ((0x6<<12)|(0x6<<4));

	//same configuration for channel 3 & 4
	TIM2->CCMR2 &= ~((0x7<<12)|(0x7<<4));
	TIM2->CCMR2 |= ((0x6<<12)|(0x6<<4));

	//Enabling Capture Compare Register for channel 1, 2, 3, 4 as output
	TIM2->CCER |= ((1<<12)|(1<<8)|(1<<4)|(1<<0));

	//Setting duty cycle
	//Setting initial safety speed 0
	TIM2->CCR1 = 0;
	TIM2->CCR2 = 0;
	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;

	//Enabling counter through Timer control register
	TIM2->CR1 |= (1<<0);//After this, timer will start counting, before timer was off

	//Making an LED brightness simulation with PWM signals we are getting as output by increasing duty cycles

	int speed = 0;
	int steps = 5;

	while(1){

		speed+=steps;//every loop cycle, adding speed by steps value

		if(speed>=2499 || speed<=0){
			steps= -steps;//increasing from 0-2499 then decreasing to 2499-0 indefinitely
		}

		TIM2->CCR1 = speed;
		TIM2->CCR2 = speed;
		TIM2->CCR3 = speed;
		TIM2->CCR4 = speed;

		//For every 1 while loop cycle, forcing it to delay for another 20000 loop cycles, for the bare eye to see the transition
		for (volatile int i=0; i<20000; i++);

//		TIM2->CCR1 = 0;
//		TIM2->CCR2 = 624;
//		TIM2->CCR3 = 1249;
//		TIM2->CCR4 = 2499;
	};
}
