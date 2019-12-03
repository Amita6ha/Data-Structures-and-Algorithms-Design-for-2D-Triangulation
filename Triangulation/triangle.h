#pragma once

#include <vector>

#include "point.h"

using namespace std;

/*The header file contains definition of class "triangle", which represents triangles in 3-dimentional space*/

class triangle {

/*private members:
	v0, v1, v2 - pointers to vertexes of a triangle
	attribute - a series of values, represents a triangle's attributes
*/

private:
	point *v0;
	point *v1;
	point *v2;
	vector<double> attribute;
public:
	
	/*declaration of constructor, destructor, copy constructor and assignment operator*/
	triangle(point &v_0, point &v_1, point &v_2, vector<double> a);

	~triangle();

	triangle(const triangle& t);

	triangle& operator=(const triangle& t);
	
	/*declaration of getting vertexes and attributes functions*/
	point get_v0();
	point get_v1();
	point get_v2();
	vector<double> get_attribute();

	/*call the member function with a "triangle" instance

	*parameter:

	*return the area of triangle*/
	double AreaOfTriangle();

	/*call the member function with a "triangle" instance

	*parameter:
		p - a "point" instance to be tested

	*return 1 if the point is in the triangle
	*return 0 if the point is not in the triangle*/
	bool PointInTriangle(point p);

	/*call the member function with a "triangle" instance

	*parameter:

	*return the triangle's circumcircle center as a "point" instance*/
	point CircumcircleCenter();

	/*call the member function with a "triangle" instance

	*parameter:
		p - a "point" instance to be tested
		r2 - square value of the triangle's circumcircle's radius

	*return 1 if the point is in the triangle's circumcircle 
	*return 0 if the point is not in the triangle's circumcircle*/
	bool PointInCircumcircle(point p, double r2);
};