#include "stm32f10x.h"
#include "ws2821_display.h"

int main() {
	struct pixel red = {0, 255, 0};
	displayInit();
	
	bufferPixel(red, 0, 0);
	
	refreshDisplay();
	
	while (1) {
	
		__ASM volatile (
			"NOP\n\t"
		);
	
	}
}