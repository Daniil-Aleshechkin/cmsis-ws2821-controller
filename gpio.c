#include "gpio.h"

#include "stm32f10x.h"

void config_gpio() {
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
		GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
		GPIOB->CRL |= GPIO_CRL_MODE0;
}
