#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int gx[3][3] = {
	{-1, 0, 1},
	{-2, 0, 2},
	{-1, 0, 1}
};

int gy[3][3] = {
	{-1, -2, -1},
	{0, 0, 0},
	{1, 2, 1}
};

// header for functions
void swap(RGBTRIPLE* a, RGBTRIPLE* b);
void blurPixel(RGBTRIPLE* center, RGBTRIPLE surround[], int len);
uint8_t* calculateKernels(int kx[3][3], int ky[3][3], RGBTRIPLE surround2D[3][3]);
int sumKernelValues(int result[3][3]);
uint8_t sobel(int kx, int ky);
void updatePixelEdge(uint8_t c[3], RGBTRIPLE* pixel);



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

void edge(int height, int width, RGBTRIPLE image[height][width]) {
	RGBTRIPLE copy[height][width];
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			copy[h][w] = image[h][w];
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if (h == 0 || w == 0 || h == height-1 || w == width-1) {
				image[h][w].rgbtRed, image[h][w].rgbtGreen, image[h][w].rgbtBlue = 0;
				copy[h][w].rgbtRed, copy[h][w].rgbtGreen, copy[h][w].rgbtBlue = 0;
			}
			else {
				RGBTRIPLE s[3][3] = {
					{copy[h-1][w-1], copy[h-1][w], copy[h-1][w+1]},
					{copy[h][w-1], copy[h][w], copy[h][w+1]},
					{copy[h+1][w-1], copy[h+1][w], copy[h+1][w+1]}
				};
				uint8_t* rgbSums = calculateKernels(gx, gy, s);
				updatePixelEdge(rgbSums, &image[h][w]);
				free(rgbSums);
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

uint8_t* calculateKernels(int kx[3][3], int ky[3][3], RGBTRIPLE surround2D[3][3]) {
	uint8_t* arr = malloc(sizeof(int) * 3);
	int rx[3][3];
	int gx[3][3];
	int bx[3][3];
	int ry[3][3];
	int gy[3][3];
	int by[3][3];
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			rx[r][c] = kx[r][c] * surround2D[r][c].rgbtRed;
			ry[r][c] = ky[r][c] * surround2D[r][c].rgbtRed;
			gx[r][c] = kx[r][c] * surround2D[r][c].rgbtGreen;
			gy[r][c] = ky[r][c] * surround2D[r][c].rgbtGreen;
			bx[r][c] = kx[r][c] * surround2D[r][c].rgbtBlue;
			by[r][c] = ky[r][c] * surround2D[r][c].rgbtBlue;
		}
	}
	int totalRx = sumKernelValues(rx);
	int totalRy = sumKernelValues(ry);
	int totalGx = sumKernelValues(gx);
	int totalGy = sumKernelValues(gy);
	int totalBx = sumKernelValues(bx);
	int totalBy = sumKernelValues(by);
	
	uint8_t red = sobel(totalRx, totalRy);
	uint8_t green = sobel(totalGx, totalGy);
	uint8_t blue = sobel(totalBx, totalBy);
	
	arr[0] = red;
	arr[1] = green;
	arr[2] = blue;
	return arr;
}

int sumKernelValues(int result[3][3]) {
	int sum = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			sum += result[r][c];
		}
	}
	return sum;
}

uint8_t sobel(int kx, int ky) {
	int v;
	if (v = round(sqrt(kx*kx+ky*ky)) > 255) {
		return 255;
	}
	else {
		return v;
	}
}

void updatePixelEdge(uint8_t c[3], RGBTRIPLE* pixel) {
	uint8_t r = c[0];
	uint8_t g = c[1];
	uint8_t b = c[2];
	pixel->rgbtRed = r;
	pixel->rgbtGreen = g;
	pixel->rgbtBlue = b;
}
