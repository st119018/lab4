#include "Number.h"

void drawNumber(int number, int x, int y, unsigned char* buffer, int bufferSize, int width, int height, int ADDPIXELS)
{
	int n = number;
	int x0 = x;
	int y0 = y;
	int countDigits = 0; // number of digits
	while (n > 0)
	{
		countDigits++;
		n /= 10;
	}

	int digits[4]{};
	n = number;
	int i = countDigits - 1;

	while (i != -1) {   // split the number into digits
		digits[i] = n % 10;
		n /= 10;
		i--;
	}
	i = countDigits;

	while (i > 0) {   // moving and drawing digit 
		if (width - x < (countDigits * 12) - ADDPIXELS) {
			x0 = x - 6 - i * 9;
		}
		else if (i == countDigits) {
			x0 = x0 + 3;
		}
		else { 
			x0 += 9; 
		}

		if (y < 24 - ADDPIXELS) {
			y0 = y + 13;
		}
		else {
			y0 = y - 3;
		}

		drawDigit(digits[countDigits - i], x0, y0, buffer, bufferSize, width, ADDPIXELS);
		i--;
	}
}

void drawDigit(int num, int x, int y, unsigned char* buffer, int bufferSize, int width, int ADDPIXELS)
{
	int digit[][144] = { 
		{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},

		{1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},

		{1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 },

		{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 }, 

		{1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, 

		{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1 },

		{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },

		{1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1,}, 

		{ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },

		{ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 } };



	int W = (((width + ADDPIXELS * 2) * 3 + 3) / 4) * 4;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			int byte = (x + ADDPIXELS + j) * 3 + (y + i) * W;
			if (byte < bufferSize) {
				buffer[byte] *= digit[num][j + i * 12];
				buffer[byte + 1] *= digit[num][j + i * 12];
				buffer[byte + 2] *= digit[num][j + i * 12];
			}
		}
	}
}
