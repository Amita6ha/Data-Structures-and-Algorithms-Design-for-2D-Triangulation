#include "point.h"

	/*definition of constructor, destructor, copy constructor and assignment operator*/
point::point() :x(0.), y(0.), z(0.){}
	//default constructorthe will initialize a point's coordinates with 0

point::point(double _x, double _y, double _z) :
	x(_x),
	y(_y),
	z(_z) {}

point::~point() {}

point::point(const point& p) :
	x(p.x),
	y(p.y),
	z(p.z) {}

point& point::operator=(const point& p) {
	if (this == &p) return (*this);
	x = p.x;
	y = p.y;
	z = p.z;
	return (*this);
}

	/*definition of overloaded equality operator to be used in class "triangulation"*/
bool point::operator==(const point &p) {
	return x == p.x && y == p.y && z == p.z;
	//2 "point"s equal when all the corresponding coordinates equal
}

	/*definition of getting coordinates functions*/
double point::get_x() {
	return x;
}
double point::get_y() {
	return y;
}
double point::get_z() {
	return z;
}

	/*call the member function with a "point" instance

	*return the square value of distance between the 2 points*/
double point::SquareOfDistance(point p) {
	return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z);
}

	/*call the member function with a "point" instance

	*return the area of triangle formed by the 3 points*/
double point::AreaOfTriangle(point v1, point v2) {
	return fabs(0.5 * ((v1.x - x) * (v2.y - y) - (v1.y - y) * (v2.x - x)));
	//geometric significance of the vector outer product operation is used to calculate the area of triangle
}