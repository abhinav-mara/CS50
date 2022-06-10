#include <stdio.h>

void left(int h, int c) {
    int counter = 0;
    while (counter < (c-1)) {
        printf(" ");
        counter++;
    }
    while (counter < h) {
        printf("#");
        counter++;
    }
}

void right(int h, int c) {
    int counter = 0;
    while (counter < (h-c+1)) {
        printf("#");
        counter++;
    }
}