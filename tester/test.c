/*
clang test.c -o test -lcs50
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() 
{
    int *m = malloc(3 * sizeof(int));

    m[0] = 1;
    m[1] = 2;
    m[2] = 3;

    free(m);

}