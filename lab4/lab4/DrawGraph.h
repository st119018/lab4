#pragma once
#include "Vertex.h"

#include <vector>
 
unsigned char* drawGraph(std::vector <std::pair <int, int>>& edges, std::vector <Vertex>& vertices, int width, int height, const int ADDPIXELS);

void drawVertices(std::vector <Vertex>& vertices, unsigned char* buffer, int stride, const int ADDPIXELS, int bufferSize);

void drawCircle(unsigned char* buffer, int x0, int y0, const int ADDPIXELS, int stride, int bufferSize);

void drawEdges(unsigned char* buffer, std::vector <Vertex>& vertices, std::vector <std::pair <int, int>>& edges, int stride, const int ADDPIXELS, int bufferSize);

void drawLine(unsigned char* buffer, int x1, int y1, int x2, int y2, int stride, const int ADDPIXELS, int bufferSize);

void drawPixel(unsigned char* buffer, int x, int y, int stride, const int ADDPIXELS, int bufferSize);
