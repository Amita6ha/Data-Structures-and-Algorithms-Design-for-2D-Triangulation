#include "triangle.h"

	/*definition of constructor, destructor, copy constructor and assignment operator*/
triangle::triangle(point &v_0, point &v_1, point &v_2, vector<double> a) :
	v0(&v_0),
	v1(&v_1),
	v2(&v_2),
	attribute(a){}

triangle::~triangle(){}

triangle::triangle(const triangle& t) :
	v0(t.v0),
	v1(t.v1),
	v2(t.v2),
	attribute(t.attribute){}

triangle& triangle::operator=(const triangle& t) {
	if (this == &t) return (*this);
	v0 = t.v0;
	v1 = t.v1;
	v2 = t.v2;
	attribute = t.attribute;
	return (*this);
}

	/*definition of getting vertexes and attributes functions*/
point triangle::get_v0() {
	return *v0;
}
point triangle::get_v1() {
	return *v1;
}
point triangle::get_v2() {
	return *v2;
}
vector<double> triangle::get_attribute() {
	return attribute;
}

	/*call the member function with a "triangle" instance

	*return the area of triangle*/
double triangle::AreaOfTriangle() {
	return (*v0).AreaOfTriangle(*v1, *v2);
	//AreaOfTriangle function in class "point" is used to calculate the area of triangle
}

	/*call the member function with a "triangle" instance

	*return 1 if the point is in the triangle
	*return 0 if the point is not in the triangle*/
bool triangle::PointInTriangle(point p) {
	if (AreaOfTriangle() < (p.AreaOfTriangle(*v0, *v1) + p.AreaOfTriangle(*v1, *v2) + p.AreaOfTriangle(*v2, *v0)))
		//if the point is outside the triangle, S¡÷v0v1v2 is less than S¡÷v0pv1 + S¡÷v1pv2 + S¡÷v2pv1
		return 0;
	else
		return 1;
}

	/*call the member function with a "triangle" instance

	*return the triangle's circumcircle center as a "point" instance*/
point triangle::CircumcircleCenter() {
	double v0_x(v0->get_x()), v0_y(v0->get_y());
	double v1_x(v1->get_x()), v1_y(v1->get_y());
	double v2_x(v2->get_x()), v2_y(v2->get_y());
	return point
	(
		((v1_y - v0_y) * (v2_y * v2_y - v0_y * v0_y + v2_x * v2_x - v0_x * v0_x)
			- (v2_y - v0_y) * (v1_y * v1_y - v0_y * v0_y + v1_x * v1_x - v0_x * v0_x))
		/ (2.0 * ((v2_x - v0_x) * (v1_y - v0_y) - (v1_x - v0_x) * (v2_y - v0_y))),
		((v1_x - v0_x) * (v2_x * v2_x - v0_x * v0_x + v2_y * v2_y - v0_y * v0_y)
			- (v2_x - v0_x) * (v1_x * v1_x - v0_x * v0_x + v1_y * v1_y - v0_y * v0_y))
		/ (2.0 * ((v2_y - v0_y) * (v1_x - v0_x) - (v1_y - v0_y) * (v2_x - v0_x))), v0->get_z()
	);
	//coordinates are calculated by solving the matrix equation defining a triangle's circumcircle
}

	/*call the member function with a "triangle" instance

	*return 1 if the point is in the triangle's circumcircle
	*return 0 if the point is not in the triangle's circumcircle*/
bool triangle::PointInCircumcircle(point p, double r2) {
	return (CircumcircleCenter().SquareOfDistance(p) <= r2 ? 1 : 0);
	//if the point is in the triangle's circumcircle, the distance between the point and circumcircle center is less than radius
}