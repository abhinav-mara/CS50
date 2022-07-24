#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{	
	if (argc != 2) {
		printf("Usage: ./recover IMAGE\n");
		return 1;
	}
	
	FILE* image = fopen(argv[1], "r");
	FILE* new = fopen("000.jpg", "a");
	uint8_t* buffer = malloc(BLOCK_SIZE);

	int ones = 0;
	int tens = 0;
	int hundreds = 0;

	int counter = 0;

	char* name = malloc(sizeof(char) * 8);
	
	while (fread(buffer, 1, BLOCK_SIZE, image) == BLOCK_SIZE) {
		if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[4] > 223 || buffer[4] < 240)) {
			sprintf(name, "%i%i%i.jpg", hundreds, tens, ones);
			if (ones < 9) {
				ones++;
			}
			else if (tens < 9) {
				tens++;
				ones = 0;
			}
			else {
				hundreds++;
				ones = 0;
				tens = 0;
			}	
			if (counter > 0) {
				fclose(new);
				new = fopen(name, "a");
			}
			fwrite(buffer, 1, BLOCK_SIZE, new);
			
			counter++;
		}
		else {
			if (counter > 0) {	
				fwrite(buffer, 1, BLOCK_SIZE, new);	
			}
		}	
	}
	
	free(name);
	free(buffer);
	fclose(image);	
	return 0;	
}
