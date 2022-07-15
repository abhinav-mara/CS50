#include "helpers.h"
#include <math.h>
#include <stdio.h>

// header
void swap(RGBTRIPLE* a, RGBTRIPLE* b);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
    	for (int w = 0; w < width; w++) {
    		int sum = 0;
    		sum += (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed);
    		uint8_t value = round(sum / 3);
    		image[h][w].rgbtGreen = value;
    		image[h][w].rgbtBlue = value;
    		image[h][w].rgbtRed = value;
    	}
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
    	for (int w = 0; w < width; w++) {
    		int red = 0.393 * image[h][w].rgbtRed + 0.769 * image[h][w].rgbtGreen + 0.189 * image[h][w].rgbtBlue;
    		int green = 0.349 * image[h][w].rgbtRed + 0.686 * image[h][w].rgbtGreen + 0.168 * image[h][w].rgbtBlue;
    		int blue = 0.272 * image[h][w].rgbtRed + 0.534 * image[h][w].rgbtGreen + 0.131 * image[h][w].rgbtBlue;
    		if (red > 255) {
    			red = 255;
    		}
    		if (green > 255) {
    			green = 255;
    		}
    		if (blue > 255) {
    			blue = 255;
    		}
    		uint8_t sepiaRed = red;
    		uint8_t sepiaGreen = green;
    		uint8_t sepiaBlue = blue;
    		image[h][w].rgbtRed, image[h][w].rgbtGreen, image[h][w].rgbtBlue = sepiaRed, sepiaGreen, sepiaBlue;
    		
    	}
    };
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
    	for (int w = 0; w < width/2; w++) {
    		swap(&image[h][w], &image[h][width-w]);
    	}
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *copy[height][width];
    // TODO: copy image into copy using for loops
    for (int h = 0; h < height; h++) {
    	for (int w = 0; w < width; w++) {
    		copy[h][w] = image[h][w];
    	}
    }
}

// Swap pixels (helper)
void swap(RGBTRIPLE* a, RGBTRIPLE* b) {
	RGBTRIPLE tmp = *a;
	*a = *b;
	*b = tmp;
}
