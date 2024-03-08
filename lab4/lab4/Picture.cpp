#include "Picture.h"

#include <fstream>
#include <string>

void makePicture(const char* filename, unsigned char* buffer, int width, int height, const int ADDPIXELS)
{
	//opening file
	std::ofstream graphPicture(filename, std::ofstream::binary);
	BITMAPFILEHEADER Header{};
	BITMAPINFOHEADER Info{};
	Info.biWidth = width + ADDPIXELS * 2;   // count width of picture
	Info.biHeight = height + ADDPIXELS * 2;  // count height of picture
	int stride = ((Info.biWidth * 3 + 3) / 4) * 4;
	Header.bfSize = 14 + Info.biSize + Info.biHeight * stride;
	graphPicture.write(reinterpret_cast<char*>(&Header), sizeof(BITMAPFILEHEADER));
	graphPicture.write(reinterpret_cast<char*>(&Info), sizeof(BITMAPINFOHEADER));
	graphPicture.write(reinterpret_cast<char*>(buffer), static_cast<std::streamsize>(stride) * Info.biHeight);
	//closing file
	graphPicture.close();
	delete[] buffer;
}
