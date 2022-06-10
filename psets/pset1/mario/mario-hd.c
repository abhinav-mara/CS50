/*
clang mario-hd.c -o mario-hd -lcs50
*/

#include <cs50.h>
#include <stdio.h>

void left(int h, int c);
void right(int h, int c);

int main(void) 
{
    int height;
    do {
        height = get_int("Height (must be an integer between 1 and 8, inclusive): ");        
    }
    while (height > 8 || height < 1);

    for (int i = height; i > 0; i--) {
        // int counter = 0;
        // while (counter < (i-1)) {
        //     printf(" ");
        //     counter++;
        // }
        // while (counter < height) {
        //     printf("#");
        //     counter++;
        // }
        left(height, i);
        printf("  ");
        // counter = 0;
        // while (counter < (height-i+1)) {
        //     printf("#");
        //     counter++;
        // }
        right(height, i);
        printf("\n");
    }
}