#pragma once

#include <cmath>

/*The header file contains definition of class "point", which represents points in 3-dimentional space*/

class point {

	/*private members:
		x, y, z - coordinates of a 3D point
	*/

private:
	double x;
	double y;
	double z;

public:
	
	/*declaration of constructor, destructor, copy constructor and assignment operator*/
	point();

	point(double _x, double _y, double _z);
	
	~point();
	
	point(const point& p);
	
	point& operator=(const point& p);

	/*declaration of overloaded equality operator to be used in class "triangulation"*/
	bool operator==(const point &p);

	/*declaration of getting coordinates functions*/
	double get_x();
	double get_y();
	double get_z();

	/*call the member function with a "point" instance
	
	*parameter:
		p - another "point" instance

	*return the square value of distance between the 2 points*/
	double SquareOfDistance(point p);

	/*call the member function with a "point" instance
	
	*parameter:
		v1, v2 - another 2 "point" instances

	*return the area of triangle formed by the 3 points*/
	double AreaOfTriangle(point v1, point v2);
};