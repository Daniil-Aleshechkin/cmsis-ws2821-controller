#include "stm32f10x.h"
#include "ws2821_display.h"
void drawSmiley(void);
void drawPrettyLight(void);

static struct pixel red = {0, 255, 0};
static struct pixel blue = {0, 0, 255};
static struct pixel green = {255, 0, 0};
static struct pixel nothing = {0, 0, 0};
static struct pixel jank = {0, 0, 0};

int main() {
	displayInit();
	
	//drawSmiley();
	drawPrettyLight();
}

void drawPrettyLight() {
	int offset = 1;
	struct pixel p;
	while (1) {
		for (int x = 0; x < DISPLAY_WIDTH; x++) {
			for (int y = 0; y < DISPLAY_HEIGHT; y++) {
				int val = (x+y+offset) % 3;

				switch (val) {
					case 0:
						p = red;
						break;
					case 1:
						p = blue;
						break;
					case 2:
						p = green;
						break;
				}
				
				bufferPixel(p, x, y);
			}
		}
		
		__disable_irq();
		refreshDisplay();
		__enable_irq();
		
		offset++;
		offset = offset % 3;

		for (int i = 0; i < 1000000; i++){
			__ASM volatile (
				"NOP\n\t"
			);
		}
	}
}

void drawSmiley(void) {
		bufferPixel(red, 2, 6);
	bufferPixel(green, 2, 5);
	bufferPixel(green, 2, 4);
	bufferPixel(red, 5, 6);
	bufferPixel(green, 5, 5);
	bufferPixel(green, 5, 4);
	
	bufferPixel(blue, 1, 2);
	bufferPixel(blue, 2, 1);
	bufferPixel(blue, 3, 1);
	bufferPixel(blue, 4, 1);
	bufferPixel(blue, 5, 1);
	bufferPixel(blue, 6, 2);

		int offset = 1;
	

		
	while (1) {
		__disable_irq();
		refreshDisplay();
		__enable_irq();
		
		bufferPixel(blue, 1, 2 + offset);
		bufferPixel(blue, 2, 1+ offset);
		bufferPixel(blue, 3, 1+ offset);
		bufferPixel(blue, 4, 1+ offset);
		bufferPixel(blue, 5, 1+ offset);
		bufferPixel(blue, 6, 2+ offset);
		
		bufferPixel(nothing, 1, 2 + (1- offset));
		bufferPixel(nothing, 2, 1 + (1- offset));
		bufferPixel(nothing, 3, 1 + (1- offset));
		bufferPixel(nothing, 4, 1 + (1- offset));
		bufferPixel(nothing, 5, 1 + (1- offset));
		bufferPixel(nothing, 6, 2 + (1- offset));
		
		if (offset == 0) {
			offset = 1;
		} else {
			offset = 0;
		}

		for (int i = 0; i < 1000000; i++){
			__ASM volatile (
				"NOP\n\t"
			);
		}
	}
}