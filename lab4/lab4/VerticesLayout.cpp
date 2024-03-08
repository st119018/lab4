#include "VerticesLayout.h"

void FRmethod(std::vector <Vertex>& vertices, const std::vector <std::pair <int, int>>& edges, int size, Frame& frame)
{
	size_t vertNum = vertices.size();

	double C = 0.7;
	double gridRadius = 4;
	double maxTemp = 3;
	double minTemp = 20;
	setParameters(vertNum, C, gridRadius, maxTemp, minTemp);

	// optimal distance between vertices(determine experimentally)
	double k = C * sqrt((size * size) / (vertNum * 1.0));
	
	// max displacement in iteration(determine experimentally)
	double t = k * maxTemp;
	int iterations = 100;

	frame.minX = size * 1.0;
	frame.minY = size * 1.0;

	for (int ii = 0; ii < iterations; ii++) {
		std::vector <std::pair<double, double>> displacement(vertNum);  // displacement of vertices

		//calculate repulsive forces between all vertices
		for (int n = 0; n < vertNum; n++) {
			displacement[n] = { 0.0, 0.0 };

			for (int m = 0; m < vertNum; m++) {
				if (n != m) {

					double dx = vertices[n].x - vertices[m].x;
					double dy = vertices[n].y - vertices[m].y;

					// consider overlapping vertices
					if (dx == 0 && dy == 0) {  
						if (vertices[m].x + 1 < size) {
							vertices[m].x += 1;
							dx = -1.0;
						}
						else {
							vertices[m].x -= 1;
							dx = 1.0;
						}
					}
					double delta = sqrt(dx * dx + dy * dy);

					//considering only neighbouring vertices for decreasing time complexity
					if (delta > 0.0 && delta <= gridRadius * k) {

						displacement[n].first += repForce(k, delta, dx / delta);
						displacement[n].second += repForce(k, delta, dy / delta);
					}
				}
			}
		}
		

		// calculate attractive forces between adjacent vertices
		for (int i = 0; i < edges.size(); i++) {

			int vertexNum1 = edges[i].first - 1;
			int vertexNum2 = edges[i].second - 1;

			// taking into account loops
			if (vertexNum1 != vertexNum2) {
				double dx = vertices[vertexNum1].x - vertices[vertexNum2].x;
				double dy = vertices[vertexNum1].y - vertices[vertexNum2].y;
				double delta = sqrt(dx * dx + dy * dy);

				if (delta > 0.0) {

					displacement[vertexNum1].first -= attrForce(k, delta, dx / delta);
					displacement[vertexNum1].second -= attrForce(k, delta, dy / delta);

					displacement[vertexNum2].first += attrForce(k, delta, dx / delta);
					displacement[vertexNum2].second += attrForce(k, delta, dy / delta);
				}

			}

		}


		// move vertices
		for (int i = 0; i < vertNum; i++) {

			double sign = 1.0;
			if (displacement[i].first < 0.0) {
				sign = -1.0;
			}

			// temperature t limits displacement
			vertices[i].x += sign * minModule(t, displacement[i].first);

			if (displacement[i].second > 0.0) {
				sign = 1.0;
			}
			else {
				sign = -1.0;
			}
			// temperature t limits displacement
			vertices[i].y += sign * minModule(t, displacement[i].second);

			// consider the frame
			vertices[i].x = max(0.0, min((size - 1) * 1.0, vertices[i].x));
			vertices[i].y = max(0.0, min((size - 1) * 1.0, vertices[i].y));

			if (ii == iterations - 1) {  // set size of graph
				frame.maxX = max(vertices[i].x, frame.maxX);
				frame.maxY = max(vertices[i].y, frame.maxY);
				frame.minX = min(vertices[i].x, frame.minX);
				frame.minY = min(vertices[i].y, frame.minY);

			}
		}

		//decreasing the temperature
		cool(t, minTemp);
	}

	// moving vertices closer to origin of coordinates
	for (int i = 0; i < vertNum; i++) {
		vertices[i].x -= frame.minX;
		vertices[i].y -= frame.minY;

	}
}

double attrForce(double k, double delta, double angle) {
	return ((delta * delta) / k) * angle;
}

double repForce(double k, double delta, double angle) {
	return ((k * k) / delta) * angle;
}

// returns minimum number
double min(double a, double b)
{
	if (a < b) {
		return a;
	}
	return b;
}

// returns minimum module number
double minModule(double a, double b)
{
	if (abs(a) < abs(b)) {
		return abs(a);
	}
	return abs(b);
}

// returns maximum number
double max(double a, double b)
{
	if (a > b) {
		return a;
	}
	return b;
}

double cool(double& t, double minTemp)
{
	if (t * 0.9 > minTemp) {
		t *= 0.9;
	}

	return t;
}

void setParameters(size_t vertNum, double& C, double& gridRadius, double& maxTemp, double& minTemp)
{
	if (vertNum > 500) {
		C = 1;
		gridRadius = 6;
		maxTemp = 6;
		minTemp = 50;
	}
	else if (vertNum <= 500 && vertNum > 300) {
		C = 0.9;
		gridRadius = 5;
		maxTemp = 4;
		minTemp = 40;
	}
}
