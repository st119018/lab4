#include "BMPheader.h"
#include "VerticesLayout.h"
#include "Picture.h"
#include "DrawGraph.h"
#include "Frame.h"
#include "Number.h"

#include <iostream>
#include <fstream>
#include <string> 
#include <vector>

#define ADDPIXELS     10



bool readFile (const char* filename, int& vertNum, int& edgeNum, std::vector <std::pair <int, int>> &edges);
void setVertPos(std::vector <Vertex>& V, int maxWidth, int maxHeight, int vertNum);

int main()
{
	const char* file = "sample.txt";
	std::vector <std::pair <int, int>> edges;
	int vertNum = 0;
	int edgeNum = 0;

	// reading from file
	if (!readFile(file, vertNum, edgeNum, edges)) {
		return 0;
	}

	std::vector <Vertex> vertPos(vertNum);

	// setting arbitrary positions of vertices (must be a bit far from each other for good layout)
	setVertPos(vertPos, 300, 300, vertNum);

	Frame frame;
	// countong coordinates of vertices
	FRmethod(vertPos, edges, 200, 200, 300, 300, frame);

	// counting width and height of graph
	int maxX = static_cast<int>(frame.maxX + 1);
	int maxY = static_cast<int>(frame.maxY + 1);
	int minX = static_cast<int>(frame.minX);
	int minY = static_cast<int>(frame.minY);
	int width = maxX - minX;
	int height = maxY - minY;

	unsigned char* picture = drawGraph(edges, vertPos, width, height, ADDPIXELS);

	makePicture("graph.bmp", picture, width, height, ADDPIXELS);

	return 0;
}

bool readFile(const char* filename, int& vertNum, int& edgeNum, std::vector<std::pair<int, int>> &edges)
{
	std::string line;

	// opening file
	std::ifstream input(filename, std::ios::in);
	if (!input.is_open()) {
		std::cerr << "File opening error." << std::endl;
		input.close();
		return 0;
	}

	// getting number of vertices and edges
	std::getline(input, line);
	size_t pos = line.find(' ');
	vertNum = stoi(line.substr(0, pos));
	edgeNum = stoi(line.substr(pos + 1, line.length() - (pos + 1)));
	edges.reserve(edgeNum);

	// adding edges
	for (int i = 0; i < edgeNum; i++) {
		std::getline(input, line);
		size_t pos = line.find(' ');
		int vert1 = stoi(line.substr(0, pos));
		int vert2 = stoi(line.substr(pos + 1, line.length() - (pos + 1)));
		edges.push_back({ vert1, vert2 });
	}

	// closing file
	input.close();

	return 1;
}

void setVertPos(std::vector<Vertex>& V, int maxWidth, int maxHeight, int vertNum)
{
	for (int i = 0; i < vertNum; i++) {
		V[i].x = static_cast<double>(rand() % maxWidth);
		V[i].y = static_cast<double>(rand() % maxHeight);
	}
}
