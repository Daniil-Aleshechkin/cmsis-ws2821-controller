#include "tim2.h"
#include "dma.h"
#include "gpio.h"
#include "stm32f10x.h"

int main() {
	volatile uint32_t time;
	
	config_gpio();
	config_DMA();
	config_tim2();
	config_DMA1();
	config_DMA3();
	
	start_dma1();
	start_dma3();
	start_tim2();
	DMA1->IFCR = (DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2);
	
	while (1) {
		//GPIOB->BSRR = GPIO_BSRR_BR0;
		__ASM volatile (
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"
			"NOP\n\t"			
			"NOP\n\t"
		);
		
		time = TIM2->CNT;
		//GPIOB->BSRR = GPIO_BSRR_BS0;
		//DMA1->IFCR = (DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2);
		//GPIOB->BSRR = 0xFFFF;
	}
}

void DMA1_Channel2_IRQHandler() {
	GPIOB->BSRR = GPIO_BSRR_BS0;
}
