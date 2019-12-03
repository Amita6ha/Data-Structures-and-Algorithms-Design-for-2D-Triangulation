#include "triangulation.h"

	/*definition of constructor, destructor, copy constructor and assignment operator*/
triangulation::triangulation(int np, int d, int app, map<int, point> ps,
	int nc, int vpc, int na, map<int, triangle> ts,
	vector<string> o) :
	no_point(np), dimension(d), attribute_per_point(app),
	point_set(ps),
	no_cell(nc), vertex_per_cell(vpc), no_attribute(na),
	triangle_set(ts), other(o) {}

triangulation::~triangulation() {}

triangulation::triangulation(const triangulation& t) :
	no_point(t.no_point), dimension(t.dimension), attribute_per_point(t.attribute_per_point),
	point_set(t.point_set),
	no_cell(t.no_cell), vertex_per_cell(t.vertex_per_cell), no_attribute(t.no_attribute),
	triangle_set(t.triangle_set), other(t.other) {}

triangulation& triangulation::operator=(const triangulation& t) {
	if (this == &t) return (*this);
	no_point = t.no_point; dimension = t.dimension; attribute_per_point = t.attribute_per_point;
	point_set = t.point_set;
	no_cell = t.no_cell; vertex_per_cell = t.vertex_per_cell; no_attribute = t.no_attribute;
	triangle_set = t.triangle_set; other = t.other;
	return (*this);
}

	/*construct a "triangulation" instance from a file*/
triangulation::triangulation(ifstream& ifs) {
	ifs >> no_point >> dimension >> attribute_per_point;

	int point_index;
	double x, y, z;
	for (int i = 0;i < no_point;++i) {
		ifs >> point_index >> x >> y >> z;
		point_set.insert(pair<int, point>(point_index, point(x, y, z)));//associate index to point
	}

	if (ifs.eof())
		return;
	
	ifs >> no_cell >> vertex_per_cell >> no_attribute;

	int cell_index, v0_index, v1_index, v2_index;
	for (int i = 0;i < no_cell;++i) {
		ifs >> cell_index >> v0_index >> v1_index >> v2_index;

		vector<double> attribute;
		double a;
		for (int j = 0;j < no_attribute;++j) {
			ifs >> a;
			attribute.push_back(a);
		}

		triangle_set.insert
		(pair<int, triangle>(cell_index, triangle(point_set[v0_index], point_set[v1_index], point_set[v2_index], attribute)));
		//associate index to triangle
	}

	while (!ifs.eof()) {
		string o;
		getline(ifs, o);
		other.push_back(o);
	}
}

	/*output the information of triangulation to a file*/
void triangulation::TriangulationOutput(ofstream& ofs) {
	
	no_point = point_set.size();//update the number of points in the mesh

	ofs << no_point << ' ' << dimension << ' ' << attribute_per_point << '\n';

	for (map<int, point>::iterator psit = point_set.begin();psit != point_set.end();++psit) {
		ofs << (*psit).first << ' ' << (*psit).second.get_x() << ' ' << (*psit).second.get_y() << ' ' << (*psit).second.get_z() << '\n';
	}

	no_cell = triangle_set.size();//update the number of cells in the mesh

	ofs << no_cell << ' ' << vertex_per_cell << ' ' << no_attribute << '\n';

	for (map<int, triangle>::iterator tsit = triangle_set.begin();tsit != triangle_set.end();++tsit) {
		int v0_index, v1_index, v2_index;
		
		/*given the vertex, get the index of the point
		*overloaded equality operator in class "point" is used here*/
		map<int, point>::iterator psit;
		for (psit = point_set.begin();psit != point_set.end(); ++psit) {
			if ((*psit).second == (*tsit).second.get_v0()) {
				v0_index = (*psit).first;
			}
		}
		for (psit = point_set.begin();psit != point_set.end(); ++psit) {
			if ((*psit).second == (*tsit).second.get_v1()) {
				v1_index = (*psit).first;
			}
		}
		for (psit = point_set.begin();psit != point_set.end(); ++psit) {
			if ((*psit).second == (*tsit).second.get_v2()) {
				v2_index = (*psit).first;
			}
		}
		ofs << (*tsit).first << ' ' << v0_index << ' ' << v1_index << ' ' << v2_index;

		vector<double> attribute((*tsit).second.get_attribute());
		for (vector<double>::iterator it = attribute.begin();it != attribute.end();++it) {
			ofs << ' ' << *it;
		}
		
		ofs << '\n';
	}

	for (vector<string>::iterator it = other.begin() + 1;it != other.end() - 1;++it) {
		ofs << *it << '\n';
	}
}

	/*call the member function with a "triangle" instance

	*return the index of triangle which contains the point
	*if no triangle contains the point, return -1*/
int triangulation::PointInWhichTriangle(point p) {
	
	/*modified version of "find_if" function
	*for each triangle in the container, check whether the triangle contains the point
	*if the triangle contains the point, return the index of the triangle*/
	map<int, triangle>::iterator tsit;
	for (tsit = triangle_set.begin();tsit != triangle_set.end();++tsit) {
		
		if ((*tsit).second.PointInTriangle(p))//check whether the triangle contains the point
			return (*tsit).first;
	}
	
	/*if all the triangles are checked and the function doesn't return, no triangle contains the point*/
	return -1;
}

	/*call the member function with a "triangle" instance

	*return 1 if the triangulation is Delaunay
	*return 0 if the triangulation is not Delaunay*/
bool triangulation::Delaunay() {
	
	/*for each triangle in the container, check whether there is a point in the cricumcircle
	*if there is one, the triangulation is not Delaunay
	*else the triangulation is Delaunay*/
	for (map<int, triangle>::iterator tsit = triangle_set.begin();tsit != triangle_set.end();++tsit) {
		triangle t((*tsit).second);
		double r2(t.CircumcircleCenter().SquareOfDistance(t.get_v0()));//calculate square value of the triangle's circumcircle's radius
		
		/*modified version of "find_if" function*/
		for (map<int, point>::iterator psit = point_set.begin();psit != point_set.end();++psit) {
			if (!t.PointInCircumcircle((*psit).second, r2))//check whether the point is in the cricumcircle
				return 0;
		}
	}
	return 1;
}

	/*function f(x, y) to be integrated over the domain of the triangulation*/
double triangulation::fxy(double x, double y) {
	return x * y;
}

	/*call the member function with a "triangle" instance

	*return constant value approximation to the integral of f(x,y) over the domain of the triangulation*/
double triangulation::ConstantValueApproximation() {
	double i;
	vector<double> I;
	
	/*evaluate constant value approximation to the integral of f(x,y) over each triangle*/
	for (map<int, triangle>::iterator tsit = triangle_set.begin();tsit != triangle_set.end();++tsit) {
		triangle t((*tsit).second);
		i = t.AreaOfTriangle() * fxy(t.CircumcircleCenter().get_x(), t.CircumcircleCenter().get_y());
		I.push_back(i);
	}
	
	/*calculate the sum*/
	double sum(0.);
	for (vector<double>::iterator it = I.begin();it != I.end();++it) {
		sum += *it;
	}
	return sum;
}

	/*call the member function with a "triangle" instance

	*return linear interpolation approximation to the integral of f(x,y) over the domain of the triangulation*/
double triangulation::LinearInterpolationApproximation() {
	double i;
	vector<double> I;
	
	/*evaluate linear interpolation approximation to the integral of f(x,y) over each triangle*/
	for (map<int, triangle>::iterator tsit = triangle_set.begin();tsit != triangle_set.end();++tsit) {
		triangle t((*tsit).second);
		i = (fxy(t.get_v0().get_x(), t.get_v0().get_y()) 
			+ fxy(t.get_v1().get_x(), t.get_v1().get_y()) 
			+ fxy(t.get_v2().get_x(), t.get_v2().get_y()));
		I.push_back(i);
	}
	
	/*calculate the sum*/
	double sum(0.);
	for (vector<double>::iterator it = I.begin();it != I.end();++it) {
		sum += *it;
	}
	return sum / 3.;
}