#include "dma.h"
#include "stdbool.h"
#include "stm32f10x.h"

#define DMA_BUFFER_SIZE 16

static const uint16_t ws2812_gpio_set_bits = 0xFFFF; // We're only touching PB0 for now

static uint16_t dmaBuffer[DMA_BUFFER_SIZE];

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

void config_DMA2(void) {
	DMA1_Channel5->CCR &= ~DMA_CCR2_MEM2MEM; // We want mem -> periferal
	DMA1_Channel5->CCR |= DMA_CCR2_DIR;
	DMA1_Channel5->CCR &= ~DMA_CCR2_MINC; // No perf or mem incrment modes
	DMA1_Channel5->CCR &= ~DMA_CCR2_PINC;
	DMA1_Channel5->CCR &= ~DMA_CCR2_PSIZE; // Word size perifiral
	DMA1_Channel5->CCR |= DMA_CCR2_PSIZE_1;
	DMA1_Channel5->CCR &= ~DMA_CCR2_MSIZE; // Half word size memory
	DMA1_Channel5->CCR |= DMA_CCR2_MSIZE_0;
	DMA1_Channel5->CCR |= DMA_CCR2_CIRC; // Circular mode enabled
	DMA1_Channel5->CCR |= DMA_CCR2_PL; // Very high priority
}

void config_DMA3(void) {
	DMA1_Channel7->CCR &= ~DMA_CCR2_MEM2MEM; // We want mem -> periferal
	DMA1_Channel7->CCR |= DMA_CCR2_DIR;
	DMA1_Channel7->CCR &= ~DMA_CCR2_MINC; // No perf or mem incrment modes
	DMA1_Channel7->CCR &= ~DMA_CCR2_PINC;
	DMA1_Channel7->CCR &= ~DMA_CCR2_PSIZE; // Word size perifiral
	DMA1_Channel7->CCR |= DMA_CCR2_PSIZE_1;
	DMA1_Channel7->CCR &= ~DMA_CCR2_MSIZE; // Half word size memory
	DMA1_Channel7->CCR |= DMA_CCR2_MSIZE_0;
	DMA1_Channel7->CCR |= DMA_CCR2_CIRC; // Circular mode enabled
	DMA1_Channel7->CCR |= DMA_CCR2_PL; // Very high priority
}

void start_dma1(void) {
	DMA1_Channel2->CNDTR = DMA_BUFFER_SIZE; // Set the buffer size
	DMA1_Channel2->CPAR = (uint32_t)&GPIOB->BSRR; // We're going to set the BSRR address to start the ws2821 signal for the bit
	DMA1_Channel2->CMAR = (uint32_t)&ws2812_gpio_set_bits; // This is the source. Should be just an 0x1
	
	DMA1_Channel2->CCR |= DMA_CCR2_EN;
	TIM2->DIER |= TIM_DIER_UDE; // Enable TIM 2 update
}

void start_dma2(void) {
	DMA1_Channel5->CNDTR = DMA_BUFFER_SIZE; // Set the buffer size
	DMA1_Channel5->CPAR = (uint32_t)&GPIOB->BRR; // We're going to set the BSRR address to start the ws2821 signal for the bit
	DMA1_Channel5->CMAR = (uint32_t)&ws2812_gpio_set_bits; // This is the source. Should be just an 0x1
	
	DMA1_Channel5->CCR |= DMA_CCR2_EN;
	TIM2->DIER |= TIM_DIER_CC1DE; // Enable TIM Channel 1 update
}


void start_dma3(void) {
	DMA1_Channel7->CNDTR = DMA_BUFFER_SIZE; // Set the buffer size
	DMA1_Channel7->CPAR = (uint32_t)&GPIOB->BRR; // We're going to set the BRR address to finish the signal for a 1 bit
	DMA1_Channel7->CMAR = (uint32_t)&ws2812_gpio_set_bits; // This is the source. Should be just an 0x1
	
	DMA1_Channel7->CCR |= DMA_CCR7_EN;
	TIM2->DIER |= TIM_DIER_CC2DE; // Enable TIM Channel 2 update
}

bool isTransferComplete() {
	return (DMA1->ISR & (DMA_ISR_TCIF5 | DMA_ISR_HTIF5));
}

bool isFullTransferComplete() {
	return (DMA1->ISR & DMA_ISR_TCIF5);
}

// super hyper-optimized way of filling up the dma buffer
void clearDMAEventFlags() {
	
}