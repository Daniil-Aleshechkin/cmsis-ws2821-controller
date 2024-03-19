#include "stm32f10x.h"
#include "ws2821_display.h"

int main() {
	struct pixel red = {0, 255, 0};
	displayInit();
	
	bufferPixel(red, 0, 0);
	

	while (1) {
		__disable_irq();
	refreshDisplay();
	__enable_irq();
	
		__ASM volatile (
			"NOP\n\t"
		);
	
	}
}