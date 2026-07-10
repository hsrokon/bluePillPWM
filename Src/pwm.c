#include "pwm.h"

void main () {

	RCC->APB1ENR |= (1<<0); //Timer 2 enabled
	RCC->APB2ENR |= (1<<2); //GPIOA enabled

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
	TIM2->ARR = 2500; /*this defines after how many cycles/count we want the timer to reset,
						since we want the clock to reset after 400count(400Hz),
						so we want timer to reset after 2500 counts [My comment could be wrong in understanding]*/

}
