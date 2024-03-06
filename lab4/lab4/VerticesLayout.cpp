#include "VerticesLayout.h"

#include <iostream>
void FRmethod(std::vector <Vertex>& vertices, const std::vector <std::pair <int, int>>& edges, int desiredWidth, int desiredHeight, int maxWidth, int maxHeight, Frame& frame)
{
	size_t vertNum = vertices.size();

	// optimal distance between vertices(determine experimentally)
	double k = 1.1 * sqrt((desiredWidth * desiredHeight) / (vertNum * 1.0));

	// determine max displacement in iteration
	double t = k * 3;//  determine experimentally
	int iterations = 100;

	frame.minX = maxWidth * 1.0;
	frame.minY = maxHeight * 1.0;

	for (int ii = 0; ii < iterations; ii++) {
		std::vector <std::pair<double, double>> displacement(vertNum); 

		//calculate repulsive forces
		for (int n = 0; n < vertNum; n++) {
			displacement[n] = { 0.0, 0.0 };

			for (int m = 0; m < vertNum; m++) {
				if (n != m) {

					double dx = vertices[n].x - vertices[m].x;
					double dy = vertices[n].y - vertices[m].y;

					// consider overlapping vertices
					if (dx == 0 && dy == 0) {  
						if (vertices[m].x + 1 < maxWidth) {
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
					if (delta > 0.0 && delta <= 4 * k) {

						displacement[n].first += repForce(k, delta, dx / delta);
						displacement[n].second += repForce(k, delta, dy / delta);
					}
					else if (delta <= 0.0) {
						std::cout << "division by 0!\n";
						std::cout << "repulsive\n";
					}
				}
			}
		}
		
		// calculate attractive forces
		for (int i = 0; i < edges.size(); i++) {

			int vertexNum1 = edges[i].first - 1;
			int vertexNum2 = edges[i].second - 1;

			// taking into account loops
				double dx = vertices[vertexNum1].x - vertices[vertexNum2].x;
				double dy = vertices[vertexNum1].y - vertices[vertexNum2].y;
				double delta = sqrt(dx * dx + dy * dy);

				if (delta > 0.0) {

					displacement[vertexNum1].first -= attrForce(k, delta, dx / delta);
					displacement[vertexNum1].second -= attrForce(k, delta, dy / delta);

					displacement[vertexNum2].first += attrForce(k, delta, dx / delta);
					displacement[vertexNum2].second += attrForce(k, delta, dy / delta);
				}
				else {
					std::cout << "division by 0!\n";
					std::cout << "attractive\n";
				}
			

		}

		// move vertices
		for (int i = 0; i < vertNum; i++) {

			double sign = 1.0;
			if (displacement[i].first < 0) {
				sign = -1.0;
			}

			// temperature limits displacement
			vertices[i].x += sign * minModule(t, displacement[i].first);
			vertices[i].y += sign * minModule(t, displacement[i].second);

			// consider the frame
			vertices[i].x = max(0.0, min((maxWidth - 1) * 1.0, vertices[i].x));
			vertices[i].y = max(0.0, min((maxHeight - 1) * 1.0, vertices[i].y));

			if (ii == iterations - 1) {
				frame.maxX = max(vertices[i].x, frame.maxX);
				frame.maxY = max(vertices[i].y, frame.maxY);
				frame.minX = min(vertices[i].x, frame.minX);
				frame.minY = min(vertices[i].y, frame.minY);

			}
		}
		//decreasing the temperature
		cool(t, ii, iterations);
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

double cool(double& t, int ii, int iterations)
{
	//// 1st phase; temperature changes rapidly
	//if (ii < iterations / 3) {
	//	t = t / (1.0 + ii / (iterations * 1.0));
	//}

	//// 2nd phase; temperature is constant and low
	//if (t <= 10.0){
	//	t = 10.0;
	//}
	if (t * 0.9 > 10.0) {
		t *= 0.9;
	}

	return t;
}