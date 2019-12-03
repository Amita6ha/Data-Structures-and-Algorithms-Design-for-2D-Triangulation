#pragma once

#include <fstream>
#include <string>
#include <map>

#include "point.h"
#include "triangle.h"

using namespace std;

/*The header file contains definition of class "triangulation", which represents a triangulated mesh*/
class triangulation {

/*private members:
	no_point - number of points in the mesh
	dimension - 2 or 3
	attribute_per_point - number of attributes per point
	point_set - container to store points, key is the index of point
	no_cell - number of cells in the mesh
	vertex_per_cell - number of verteses per cell
	no_attribute - number of attributes per cell
	triangle_set - container to store cells, key is the index of cell
	other - other properties of the mesh
*/

private:
	int no_point, dimension, attribute_per_point;
	map<int, point> point_set;
	int no_cell, vertex_per_cell, no_attribute;
	map<int, triangle> triangle_set;
	vector<string> other;

	/*function f(x, y) to be integrated over the domain of the triangulation*/
	double fxy(double x, double y);
public:
	
	/*declaration of constructor, destructor, copy constructor and assignment operator*/
	triangulation(int np, int d, int app, map<int, point> ps,
		int nc, int vpc, int na, map<int, triangle> ts,
		vector<string> o);

	~triangulation();

	triangulation(const triangulation& t);

	triangulation& operator=(const triangulation& t);

	/*construct a "triangulation" instance from a file*/
	triangulation(ifstream& ifs);

	/*output the information of triangulation to a file*/
	void TriangulationOutput(ofstream& ofs);

	/*call the member function with a "triangle" instance
	
	*parameter:
		p - a "point" instance to be tested
	
	*return the index of triangle which contains the point
	*if no triangle contains the point, return -1*/
	int PointInWhichTriangle(point p);

	/*call the member function with a "triangle" instance
	
	*return 1 if the triangulation is Delaunay
	*return 0 if the triangulation is not Delaunay*/
	bool Delaunay();

	/*call the member function with a "triangle" instance

	*return constant value approximation to the integral of f(x,y) over the domain of the triangulation*/
	double ConstantValueApproximation();

	/*call the member function with a "triangle" instance

	*return linear interpolation approximation to the integral of f(x,y) over the domain of the triangulation*/
	double LinearInterpolationApproximation();
};