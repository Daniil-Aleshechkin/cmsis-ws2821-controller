#include "ws2821_display.h"
#include "tim2.h"
#include "dma.h"
#include "gpio.h"
#include "util.h"

void fill_dma_buffer(uint16_t *dest, int pos, uint8_t* source);

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
	// TODO: make the thing add to the framebuffer
}

void refreshDisplay() {
	// These are each bits that the DMA channel 5 uses to transfer to the BRR
	// Code currently handles just PB0, so only the first bit is important
	// Each bit is also inverted as the second DMA channel is basically the source of truth of bits
	// Will use 16 size on the final version. 24 is just the testing amount for the real display
	static uint16_t dma_buffer[DMA_BUFFER_SIZE];
	
	int pos = 0;
	
	int max_pos = DISPLAY_FRAME_BUFFER_LENGTH + DMA_BUFFER_SIZE; // A litter extra is added to give the dma some time to refresh last few bytes
	
	fill_dma_buffer((uint16_t *)dma_buffer, pos, (uint8_t *)display_frame_buffer);
	fill_dma_buffer((uint16_t *)dma_buffer, pos + 8, (uint8_t *)display_frame_buffer);
	
	stop_all_dma_channels();
	stop_tim2();
	
	// Begin reset timer
	resetLED();
	start_tim2();
	for (int i = 0; i < 225; i++) {
		while(!isTim2Updated());
		resetTime2Update();
	}
	// End reset timer
	stop_tim2();
	start_dma1();
	start_dma2((uint16_t*)&dma_buffer);
	start_dma3();
	
	clearDMAEventFlags();
	
	// Begin the data transfer
	start_tim2();
	while (pos < max_pos) {
		if (!isTransferComplete()) {
			continue;
		}
		clearDMAEventFlags();
		pos++;
	}
	
}

void fill_dma_buffer(uint16_t *dest, int pos, uint8_t* source) {
	// TODO: constant buffer for now, but we're going to make the full one later
	
	dest[0] = 1;
	dest[1] = 1;
	dest[2] = 1;
	dest[3] = 1;
	dest[4] = 1;
	dest[5] = 1;
	dest[6] = 1;
	dest[7] = 1;
	dest[8] = 0;
	dest[9] = 0;
	dest[10] = 0;
	dest[11] = 0;
	dest[12] = 0;
	dest[13] = 0;
	dest[14] = 0;
	dest[15] = 0;
	dest[16] = 1;
	dest[17] = 1;
	dest[18] = 1;
	dest[19] = 1;
	dest[20] = 1;
	dest[21] = 1;
	dest[22] = 1;
	dest[23] = 1;
}