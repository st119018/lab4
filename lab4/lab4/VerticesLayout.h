#pragma once
#include "Vertex.h"

#include <vector>
#include<math.h>


void FRmethod(std::vector <Vertex>& vertices, std::vector <std::pair <int, int>>& edges, int width, int height);

double attrForce(double k, double delta, double angle);

double repForce(double k, double delta, double angle);

double min(double a, double b);

double minModule(double a, double b);

double max(double a, double b);

