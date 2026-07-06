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

}
