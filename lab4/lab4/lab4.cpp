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
void setVertPos(std::vector <Vertex>& V, int size);
void countFrame(Frame frame, int& width, int& height);
int setSize(int vertNum);

int main()
{
	const char* file = "sample.txt";   // name of input file
	std::vector <std::pair <int, int>> edges;
	int vertNum = 0;   // number of vertices
	int edgeNum = 0;   // number of edges

	// reading from file
	if (!readFile(file, vertNum, edgeNum, edges)) {
		return 0;
	}

	std::vector <Vertex> vertPos(vertNum);

	// count size of graph
	int size = setSize(vertNum);

	// setting arbitrary positions of vertices
	setVertPos(vertPos, size);

	Frame frame;
	// counting coordinates of vertices
	FRmethod(vertPos, edges, size, frame);

	// counting width and height of graph
	int width = 0;
	int height = 0;
	countFrame(frame, width, height);

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

void setVertPos(std::vector<Vertex>& V, int size)
{
	for (int i = 0; i < V.size(); i++) {
		V[i].x = static_cast<double>(rand() % size);
		V[i].y = static_cast<double>(rand() % size);
	}
}

void countFrame(Frame frame, int& width, int& height)
{
	int maxX = static_cast<int>(frame.maxX + 1);
	int maxY = static_cast<int>(frame.maxY + 1);
	int minX = static_cast<int>(frame.minX);
	int minY = static_cast<int>(frame.minY);
	width = maxX - minX;
	height = maxY - minY;
}

int setSize(int vertNum)
{
	if (vertNum * 5 < 700) {
		return 700;
	}
	return vertNum * 5;
}
