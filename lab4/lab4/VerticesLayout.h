#pragma once
#include "Vertex.h"
#include "Frame.h"

#include <vector>
#include<math.h>


void FRmethod(std::vector <Vertex>& vertices, const std::vector <std::pair <int, int>>& edges, int desiredWidth, int desiredHeight, int maxWidth, int maxHeight, Frame& frame);

double attrForce(double k, double delta, double angle);

double repForce(double k, double delta, double angle);

double min(double a, double b);

double minModule(double a, double b);

double max(double a, double b);

double cool(double& t, int ii, int iterations);

