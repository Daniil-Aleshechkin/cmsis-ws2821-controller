#include "tim2.h"
#include "stm32f10x.h"

#define TIMER2_FREQ_HZ          72000000
#define WS2812_TIMER_PERIOD        (((TIMER2_FREQ_HZ / 1000) * 125) / 100000)
#define WS2812_TIMER_PWM_CH1_TIME  (((TIMER2_FREQ_HZ / 1000) *  40) / 100000)
#define WS2812_TIMER_PWM_CH2_TIME  (((TIMER2_FREQ_HZ / 1000) *  80) / 100000)

void config_tim2(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 0x0;
	TIM2->ARR = WS2812_TIMER_PERIOD;
	
	/* CR1 CONFIGS */
	TIM2->CR1 &= ~TIM_CR1_CKD; // No clock division
	TIM2->CR1 &= ~TIM_CR1_ARPE; // Auto-reload preload disabled
	TIM2->CR1 &= ~TIM_CR1_CMS; // Center aligned mode
	TIM2->CR1 &= ~TIM_CR1_DIR; // Up counter
	TIM2->CR1 &= ~TIM_CR1_OPM; // One pulse mode disabled
	
	/* CR2 CONFIGS */
	TIM2->CR2 &= ~TIM_CR2_MMS; // Reset mms mode 
	
	/* SMCR CONFIGS */
	TIM2->SMCR &= ~TIM_SMCR_MSM; // No Master mode
	TIM2->SMCR &= ~TIM_SMCR_ETP; // No external clocks
	TIM2->SMCR &= ~TIM_SMCR_ECE; 
	TIM2->SMCR &= ~TIM_SMCR_ETPS; 
	TIM2->SMCR &= ~TIM_SMCR_ETF; 
	TIM2->SMCR &= ~TIM_SMCR_SMS; // No Slave mode
	
	
}

void start_tim2(void) {
	TIM2->CR1 |= TIM_CR1_CEN;
	
	while (!(TIM2->SR & TIM_SR_UIF));
}

void stop_tim2(void) {
	TIM2->CR1 &= ~TIM_CR1_CEN;
}
