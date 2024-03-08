#include "DrawGraph.h"
#include "Number.h"

unsigned char* drawGraph(const std::vector<std::pair<int, int>>& edges, std::vector<Vertex>& vertices, int width, int height, const int ADDPIXELS)
{
	int stride = (((width + ADDPIXELS * 2) * 3 + 3) / 4) * 4;    // enlarged width in bytes, multiple of 4

	// create buffer
	int bufferSize = stride * (height + ADDPIXELS * 2);
	unsigned char* buffer = new unsigned char[bufferSize];

	// make the picture white
	for (int i = 0; i < bufferSize; i++) {
		buffer[i] = (unsigned char)255;
	}

	// draw all vertices
	drawVertices(vertices, buffer, stride, ADDPIXELS, bufferSize);

	// number vertices
	for (int i = 0; i < vertices.size(); i++) {
		int x = static_cast<int>(vertices[i].x);
		int y = static_cast<int>(vertices[i].y);
		drawNumber(i + 1, x, y, buffer, bufferSize, width, height, ADDPIXELS);
	}

	// draw edges
	drawEdges(buffer, vertices, edges, width, height, stride, ADDPIXELS, bufferSize);
	return buffer;
}

void drawVertices(std::vector<Vertex>& vertices, unsigned char* buffer, int stride, const int ADDPIXELS, int bufferSize)
{
	for (Vertex v : vertices) {
		int x = static_cast<int>(v.x);
		int y = static_cast<int>(v.y);

		// draw vertex 
		drawCircle(buffer, x, y, ADDPIXELS, stride, bufferSize);

	}
}

void drawCircle(unsigned char* buffer, int x0, int y0, const int ADDPIXELS, int stride, int bufferSize)
{
	int radius = 4;
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0) {

		drawLine(buffer, x0 - x, y0 + y, x0 + x, y0 + y, stride, ADDPIXELS, bufferSize);
		drawLine(buffer, x0 + x, y0 - y, x0 - x, y0 - y, stride, ADDPIXELS, bufferSize);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}


void drawEdges(unsigned char* buffer, std::vector <Vertex>& vertices, const  std::vector <std::pair <int, int>>& edges, int width, int height, int stride, const int ADDPIXELS, int bufferSize)
{
	for (std::pair <int, int> edge : edges) {
		int vertexNum1 = edge.first - 1;
		int x1 = static_cast<int>(vertices[vertexNum1].x);
		int y1 = static_cast<int>(vertices[vertexNum1].y);
		int vertexNum2 = edge.second - 1;
		int x2 = static_cast<int>(vertices[vertexNum2].x);
		int y2 = static_cast<int>(vertices[vertexNum2].y);

		// consider loops
		if (vertexNum1 == vertexNum2) {
			drawLoop(buffer, x1, y1, width, height, ADDPIXELS, stride, bufferSize);
		}
		else {
			drawLine(buffer, x1, y1, x2, y2, stride, ADDPIXELS, bufferSize);
		}
	}

}

void drawLine(unsigned char* buffer, int x1, int y1, int x2, int y2, int stride, const int ADDPIXELS, int bufferSize)
{
	const int dX = abs(x2 - x1);
	const int dY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = dX - dY;
	drawPixel(buffer, x2, y2, stride, ADDPIXELS, bufferSize);

	while (x1 != x2 || y1 != y2) {
		drawPixel(buffer, x1, y1, stride, ADDPIXELS, bufferSize);
		int error2 = error * 2;
		if (error2 > -dY) {
			error -= dY;
			x1 += signX;
		}
		if (error2 < dX)
		{
			error += dX;
			y1 += signY;
		}
	}

}

void drawPixel(unsigned char* buffer, int x, int y, int stride, const int ADDPIXELS, int bufferSize)
{
	int byte = (ADDPIXELS + x) * 3 + (ADDPIXELS + y) * stride;
	if (byte >= 0 && byte + 2 < bufferSize) {
		//take into account 3 bytes per pixel
		buffer[byte] = (unsigned char)0;
		buffer[byte + 1] = (unsigned char)0;
		buffer[byte + 2] = (unsigned char)0;
	}
}

void drawLoop(unsigned char* buffer, int x0, int y0, int width, int height, const int ADDPIXELS, int stride, int bufferSize)
{
	// moving centre of loop considering frame
	if (x0 < 12) {
		x0 += 7;
	}
	else {
		x0 -= 7;
	}
	if (y0 > height - 12) {
		y0 -= 8;
	}
	else {
		y0 += 8;
	}

	int radius = 6; //radius of loop
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	// drawing loop
	while (y >= 0) {

		drawPixel(buffer, x0 + x, y0 + y, stride, ADDPIXELS, bufferSize);
		drawPixel(buffer, x0 + x, y0 - y, stride, ADDPIXELS, bufferSize);
		drawPixel(buffer, x0 - x, y0 + y, stride, ADDPIXELS, bufferSize);
		drawPixel(buffer, x0 - x, y0 - y, stride, ADDPIXELS, bufferSize);

		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}
