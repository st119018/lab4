#include "VerticesLayout.h"

#include <iostream>
void FRmethod(std::vector <Vertex>& vertices, std::vector <std::pair <int, int>>& edges, int width, int height)
{
	int vertNum = vertices.size();
	// optimal distance between vertices(determine experimentally)
	double k = 0.7 * sqrt((width * height) / (vertNum * 1.0));
	// determine max displacement in iteration
	double t = 10.0;//  determine experimentally
	int iterations = 50;
	for (int ii = 0; ii < iterations; ii++) {
		std::vector <std::pair<double, double>> displacement(vertNum); 

		//calculate repulsive forces
		for (int n = 0; n < vertNum; n++) {
			displacement[n] = { 0.0, 0.0 };

			for (int m = 0; m < vertNum; m++) {
				if (n != m) {

					double dx = vertices[n].x - vertices[m].x;
					double dy = vertices[n].y - vertices[m].y;
					double delta = sqrt(dx * dx + dy * dy);

					//considering only neighbouring vertices for decreasing time complexity
					if (delta > 0.0 && delta <= 2 * k) {

						displacement[n].first += repForce(k, delta, dx / delta);
						displacement[n].second += repForce(k, delta, dy / delta);
					}
					else {
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
				else {
					std::cout << "division by 0!\n";
					std::cout << "attractive\n";
				}
			}

		}

		for (int i = 0; i < vertNum; i++) {
			double sign = 1.0;
			if (displacement[i].first < 0) {
				sign = -1.0;
			}
			vertices[i].x += sign * minModule(t, displacement[i].first);
			vertices[i].y += sign * minModule(t, displacement[i].second);

			vertices[i].x = max(0.0, min((width - 1) * 1.0, vertices[i].x));
			vertices[i].y = max(0.0, min((height - 1) * 1.0, vertices[i].y));

		}
		//decreasing the temperature
		if (t - 0.05 > 0) {
			t -= 0.05; 
		}
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
