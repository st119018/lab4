#pragma once
#pragma pack(push, 1)


struct  BITMAPFILEHEADER {
    short           bfType = 0x4D42;
    int             bfSize;                // size of file
    short           bfReserved1 = 0;       // always 0
    short           bfReserved2 = 0;       // always 0
    int             bfOffBits = 54;        // offset in bytes
};

struct BITMAPINFOHEADER {
    unsigned int    biSize = 40;           // size of this header
    int             biWidth;               // width in pixels
    int             biHeight;              // height in pixels
    unsigned short  biPlanes = 1;          // number of color planes (must be 1)
    unsigned short  biBitCount = 24;       // number of bits per pixel
    unsigned int    biCompression = 0;     // compression method being used
    unsigned int    biSizeImage = 0;       // size of the raw bitmap data; 0 can be given for BI_RGB bitmaps
    int             biXPelsPerMeter = 0;   // horizontal resolution of the image
    int             biYPelsPerMeter = 0;   // vertical resolution of the image
    unsigned int    biClrUsed = 0;         // number of colors used (0 - use all colors)
    unsigned int    biClrImportant = 0;    //  number of important colors used; 0 - all colors are important
};
#pragma pack(pop)

