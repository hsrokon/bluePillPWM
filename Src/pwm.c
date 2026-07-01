#include "pwm.h"

void main () {

	RCC->APB1ENR |= (1<<0); //Timer 2 enabled
	RCC->APB2ENR |= (1<<2); //GPIOA enabled

	//Resetting pin 0,1,2,3
	GPIOA->CRL &= ~(0xF<<0);
	GPIOA->CRL &= ~(0xF<<4);
	GPIOA->CRL &= ~(0xF<<8);
	GPIOA->CRL &= ~(0xF<<12);
	//Configuring pin 0,1,2,3
	GPIOA->CRL |= (0xB<<0);
	GPIOA->CRL |= (0xB<<4);
	GPIOA->CRL |= (0xB<<8);
	GPIOA->CRL |= (0xB<<12);

}
