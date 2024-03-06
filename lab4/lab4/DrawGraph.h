#pragma once
#include "Vertex.h"

#include <vector>
 
unsigned char* drawGraph(const std::vector <std::pair <int, int>>& edges, std::vector <Vertex>& vertices, int width, int height, const int ADDPIXELS);

void drawVertices(std::vector <Vertex>& vertices, unsigned char* buffer, int stride, const int ADDPIXELS, int bufferSize);

void drawCircle(unsigned char* buffer, int x0, int y0, const int ADDPIXELS, int stride, int bufferSize);

void drawEdges(unsigned char* buffer, std::vector <Vertex>& vertices, const  std::vector <std::pair <int, int>>& edges, int width, int height, int stride, const int ADDPIXELS, int bufferSize);

void drawLine(unsigned char* buffer, int x1, int y1, int x2, int y2, int stride, const int ADDPIXELS, int bufferSize);

void drawPixel(unsigned char* buffer, int x, int y, int stride, const int ADDPIXELS, int bufferSize);

void drawLoop(unsigned char* buffer, int x0, int y0, int width, int height, const int ADDPIXELS, int stride, int bufferSize);
