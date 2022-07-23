#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{	
	int BLOCK_SIZE = 512;
	if (argc != 2) {
		printf("Usage: ./recover IMAGE\n");
		return 1;
	}
	
	FILE* image = fopen(argv[1], "r");
	FILE* new;
	uint8_t* buffer = malloc(BLOCK_SIZE);

	int ones = 0;
	int tens = 0;
	int hundreds = 0;
	
	char* name = malloc(sizeof(char) * 8);
	sprintf(name, "%i%i%i.jpg", hundreds, tens, ones);
	
	while (fread(buffer, 1, BLOCK_SIZE, image) == BLOCK_SIZE) {
		if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[4] > 223 || buffer[4] < 240)) {
			if (ones < 9) {
				ones++;
			}
			else if (tens < 9) {
				tens++;
				ones = 0;
			}
			else {
				hundreds++;
				tens = 0;
				ones = 0;
			}
			sprintf(name, "%i%i%i.jpg", hundreds, tens, ones);
			new = fopen(name, "w");	
		}
		else {
			fwrite(buffer, BLOCK_SIZE, 1, new);	
		}	
	}
	
	free(name);
	free(buffer);

	return 0;	
}
