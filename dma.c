#include "dma.h"
#include "stm32f10x.h"

#define DMA_BUFFER_SIZE 1

static const uint16_t ws2812_gpio_set_bits = 0xFFFF; // We're only touching PB0 for now

void config_DMA(void) {
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	uint32_t prioritygroup = NVIC_GetPriorityGrouping();
	
	NVIC_SetPriority(DMA1_Channel2_IRQn, NVIC_EncodePriority(prioritygroup, 0, 0));
}

void config_DMA1(void) {
	DMA1_Channel2->CCR &= ~DMA_CCR2_MEM2MEM; // We want mem -> periferal
	DMA1_Channel2->CCR |= DMA_CCR2_DIR;
	DMA1_Channel2->CCR &= ~DMA_CCR2_MINC; // No perf or mem incrment modes
	DMA1_Channel2->CCR &= ~DMA_CCR2_PINC;
	DMA1_Channel2->CCR &= ~DMA_CCR2_PSIZE; // Word size perifiral
	DMA1_Channel2->CCR |= DMA_CCR2_PSIZE_1;
	DMA1_Channel2->CCR &= ~DMA_CCR2_MSIZE; // Half word size memory
	DMA1_Channel2->CCR |= DMA_CCR2_MSIZE_0;
	DMA1_Channel2->CCR |= DMA_CCR2_CIRC; // Circular mode enabled
	DMA1_Channel2->CCR |= DMA_CCR2_PL; // Very high priority
}

void start_dma1(void) {
	DMA1_Channel2->CNDTR = DMA_BUFFER_SIZE; // Set the buffer size
	DMA1_Channel2->CPAR = (uint32_t)&GPIOB->BSRR; // We're going to set the BSRR address
	DMA1_Channel2->CMAR = (uint32_t)&ws2812_gpio_set_bits; // This is the source. Should be just an 0x1
	
	DMA1_Channel2->CCR |= DMA_CCR2_EN;
	TIM2->DIER |= TIM_DIER_UDE; // Enable TIM 2 update
}
