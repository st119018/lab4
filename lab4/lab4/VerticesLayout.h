#pragma once
#include "Vertex.h"
#include "Frame.h"

#include <vector>
#include<cmath>


void FRmethod(std::vector <Vertex>& vertices, const std::vector <std::pair <size_t, size_t>>& edges, int size, Frame& frame);

double attrForce(double k, double delta, double angle);

double repForce(double k, double delta, double angle);

double min(double a, double b);

double minModule(double a, double b);

double max(double a, double b);

double cool(double& t, double minTemp);

void setParameters(size_t vertNum, double& C, double& gridRadius, double& maxTemp, double& minTemp);