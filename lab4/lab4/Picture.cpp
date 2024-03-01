#include "Picture.h"

#include <fstream>
#include <string>

void makePicture(const char* filename, unsigned char* buffer, int Largewidth, int Largeheight)
{
	//opening file
	std::ofstream graphPicture(filename, std::ofstream::binary);
	BITMAPFILEHEADER Header{};
	BITMAPINFOHEADER Info{};
	Info.biWidth = Largewidth;
	Info.biHeight = Largeheight;
	int stride = ((Info.biWidth * 3 + 3) / 4) * 4;
	Header.bfSize = 14 + Info.biSize + Info.biHeight * stride;
	graphPicture.write(reinterpret_cast<char*>(&Header), sizeof(BITMAPFILEHEADER));
	graphPicture.write(reinterpret_cast<char*>(&Info), sizeof(BITMAPINFOHEADER));
	graphPicture.write(reinterpret_cast<char*>(buffer), static_cast<std::streamsize>(stride) * Info.biHeight);
	//closing file
	graphPicture.close();
	delete[] buffer;
}
