#include <iostream>
#include <fstream>

#include "triangulation.h"

using namespace std;

int main() {
	ifstream in("triangulation#0.tri");
	triangulation t = triangulation(in);

	point p0(1.1, 1.1, 0);//P0 is not in any triangle
	cout << t.PointInWhichTriangle(p0) << '\n';//should return -1
	point p1(0.1, 0.1, 0);//P1 is in triangle #0
	cout << t.PointInWhichTriangle(p1) << '\n';//should return 0
	point p2(0.6, 0.6, 0);//P2 is in triangle #1
	cout << t.PointInWhichTriangle(p2) << '\n';//should return 1
	cout << t.Delaunay() << '\n';//should return 1
	cout << t.ConstantValueApproximation() << '\n';
	cout << t.LinearInterpolationApproximation() << '\n';

	ofstream out("output#0.tri");
	t.TriangulationOutput(out);
}
