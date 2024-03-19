#include "stm32f10x.h"
#include "ws2821_display.h"

int main() {
	struct pixel red = {0, 255, 0};
	struct pixel blue = {0, 0, 255};
	displayInit();
	
	bufferPixel(red, 2, 5);
	bufferPixel(red, 2, 4);
	bufferPixel(red, 5, 5);
	bufferPixel(red, 5, 4);
	
	bufferPixel(red, 1, 2);
	bufferPixel(red, 2, 1);
	bufferPixel(red, 3, 1);
	bufferPixel(red, 4, 1);
	bufferPixel(red, 5, 1);
	bufferPixel(red, 6, 2);

	while (1) {
		__disable_irq();
		refreshDisplay();
		__enable_irq();
	
		__ASM volatile (
			"NOP\n\t"
		);
	
	}
}