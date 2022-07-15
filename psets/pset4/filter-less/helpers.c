#include "helpers.h"
#include <math.h>
#include <stdio.h>





// header for functions
void swap(RGBTRIPLE* a, RGBTRIPLE* b);
void blurPixel(RGBTRIPLE* center, RGBTRIPLE surround[], int len);

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
    RGBTRIPLE copy[height][width];
    // TODO: copy image into copy using for loops
    for (int h = 0; h < height; h++) {
    	for (int w = 0; w < width; w++) {
    		copy[h][w] = image[h][w];
    	}
    }
    
    // TODO: blur image
    for (int h = 0; h < height; h++) {
    	for (int w = 0; w < width; w++) {
    		// TODO: corner cases
    		if ((h == 0 && w == 0) || (h == 0 && w == width-1) || (h == height-1 && w == 0) || (h == height-1 && w == width-1)) {
	    		if (h == 0 && w == 0) {
	    			RGBTRIPLE s[] = {copy[1][0], copy[1][1], copy[0][1]};
	    			blurPixel(&image[0][0], s, 3);
	    		}
	    		else if (h == 0 && w == width-1) {
	    			RGBTRIPLE s[] = {copy[h][width-2], copy[h+1][width-2], copy[h+1][width-1]};
	    			blurPixel(&image[h][w], s, 3);
	    		}
	    		else if (h == height-1 && w == 0) {
	    			RGBTRIPLE s[] = {copy[height-2][w], copy[height-2][w+1], copy[h][w+1]};
	    			blurPixel(&image[h][w], s, 3);
	    		}
	    		else if (h == height-1 && w == width-1) {
	    			RGBTRIPLE s[] = {copy[height-2][width-2], copy[height-2][w], copy[h][width-2]};
	    			blurPixel(&image[h][w], s, 3);
	    		}
    		}
    		else if (h == 0 || w == 0 || h == height-1 || w == width-1) {
    			if (h == 0) {
    				RGBTRIPLE s[] = {copy[h][w-1], copy[h][w+1], copy[h+1][w], copy[h+1][w-1], copy[h+1][w+1]};
    				blurPixel(&image[h][w], s, 5);
    			}
    			else if (w == 0) {
    				RGBTRIPLE s[] = {copy[h+1][w], copy[h-1][w], copy[h][w+1], copy[h-1][w+1], copy[h+1][w+1]};
    				blurPixel(&image[h][w], s, 5);
    			}
    			else if (h == height-1) {
    				RGBTRIPLE s[] = {copy[h][w-1], copy[h][w+1], copy[h-1][w], copy[h-1][w-1], copy[h-1][w+1]};
    				blurPixel(&image[h][w], s, 5);
    			}
    			else {
    				RGBTRIPLE s[] = {copy[h-1][w], copy[h+1][w], copy[h][w-1], copy[h-1][w-1], copy[h+1][w-1]};
    				
    			}
    		}
    		else {
    			RGBTRIPLE s[] = {copy[h-1][w-1], copy[h-1][w], copy[h-1][w+1], copy[h][w-1], copy[h][w+1], copy[h+1][w-1], copy[h+1][w], copy[h+1][w+1]};
    			blurPixel(&image[h][w], s, 8);
    		}
    	}
    }
}

// Swap pixels (helper)
void swap(RGBTRIPLE* a, RGBTRIPLE* b) {
	RGBTRIPLE tmp = *a;
	*a = *b;
	*b = tmp;
}

void blurPixel(RGBTRIPLE* center, RGBTRIPLE surround[], int len) {
	int r = 0;
	int g = 0;
	int b = 0;
	for (int i = 0; i < len; i++) {
		r += surround[i].rgbtRed;
		g += surround[i].rgbtGreen;
		b += surround[i].rgbtBlue;
	}
	uint8_t fr = round(r/len);
	uint8_t fg = round(g/len);
	uint8_t fb = round(b/len);
	center->rgbtRed = fr;
	center->rgbtGreen = fg;
	center->rgbtBlue = fb;
}

