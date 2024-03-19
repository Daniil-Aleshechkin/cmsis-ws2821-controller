#include "ws2821_display.h"
#include "tim2.h"
#include "dma.h"
#include "gpio.h"
#include "util.h"

#define DISPLAY_FRAME_BUFFER_LENGTH DISPLAY_WIDTH*DISPLAY_HEIGHT

// This is what will be sent to the ws2821. Each is a pixel value for G,R,B
static uint8_t display_frame_buffer[DISPLAY_FRAME_BUFFER_LENGTH * 3];

void displayInit() {
	config_gpio();
	config_DMA();
	config_tim2();
	config_DMA1();
	config_DMA2();
	config_DMA3();
	
	for (int i = 0; i < DISPLAY_FRAME_BUFFER_LENGTH; i++) {
		display_frame_buffer[i] = (uint8_t)0;
	}
}

void bufferPixel(struct pixel p, int x, int y) {
	
}

void refreshDisplay() {
	// These are each bits that the DMA channel 5 uses to transfer to the BRR
	// Code currently handles just PB0, so only the first bit is important
	// Each bit is also inverted as the second DMA channel is basically the source of truth of bits
	// Will use 16 size on the final version. 27 is just the testing amount for the real display
	static uint16_t dma_buffer[24];

	
}

void fill_dma_buffer(uint8_t *dest, int pos) {
	// TODO: constant buffer for now, but we're going to make the full one later
	
	
}