#include "BMPheader.h"
#include "VerticesLayout.h"
#include "Picture.h"
#include "DrawGraph.h"

#include <iostream>
#include <fstream>
#include <string> 
#include <vector>






// кажется проблема в том что изначальное поле довольно маленькое (см сайт)
// короче думаю я не буду учитывать слишком дальние вершины 
// и изначально сделаю оооооочень большое поле и пусть W и L в алгоритме  именно там где ограничиваются x y
// опр-ся на основе самого больших dx dy 
// 
// 
//










bool readFile (const char* filename, int& vertNum, int& edgeNum, std::vector <std::pair <int, int>> &edges);
void setVertPos(std::vector <Vertex>& V, int width, int height, int vertNum);
/*
пусть   <=100 вершин - 200 * 150
		<=300 и >100 - 300 * 200
		>300 и <=500 - 500 * 400
		>500 & <=1000 - ○○ * ○○
*/
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

	// setting arbitrary positions of vertices  
	setVertPos(vertPos, 500, 300, vertNum);

	FRmethod(vertPos, edges, 100, 100);

	unsigned char* picture = drawGraph(edges, vertPos, 100, 100, 10);

	makePicture("graph1.bmp", picture, 100 + 10 * 2, 100 + 10 * 2);


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

void setVertPos(std::vector<Vertex>& V, int width, int height, int vertNum)
{
	for (int i = 0; i < vertNum; i++) {
		V[i].x = static_cast<double>(rand() % 100);
		V[i].y = static_cast<double>(rand() % 100);
	}
}
