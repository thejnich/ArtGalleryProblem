#include "Triangulate.h"

/* Puts vertices of triangulation of polygon into result */
bool Triangulate::Process(const vector<Vector> &polygon, vector<Vector> &result)
{
	return false;
}
	
/* returns area of polygon */
float Triangulate::Area(const vector<Vector> &polygon)
{
	int n = polygon.size();

	if(n < 3)
		return 0.f;

	float area = 0.f;

	for(int p = n-1, q = 0; q < n; p = q++) {
		area += (polygon[p].getx() *polygon[q].gety()) - (polygon[q].getx() * polygon[p].gety()); 
	}
	return area * 0.5;	
}
	
/* true if p is inside triangle(abc) */
bool Triangulate::InsideTriangle(Vector a, Vector b, Vector c, Vector p)
{
	// do p and a lie on same side of line bc
	bool pa = SameSide(b, c, p, a);

	// do p and b lie on same side of line ac
	bool pb = SameSide(a, c, p, b);

	// do p and c lie on same side of ab
	bool pc = SameSide(a, b, p, c);

	// p is inside triangle abc if all above are true.
	return (pa && pb && pc);
}

/* true is points p1, p2 lie on the same side of line segment ab */
bool Triangulate::SameSide(Vector a, Vector b, Vector p1, Vector p2)
{
	// v is a vector from a to b
	Vector v = b - a;

	// if the cross product of the vector from a to b, with the vector from a to p1 and a to p2
	// are in the same direction, then p1 and p2 are on the same side. This will be true only
	// when the z components of the crossproducts both positive or both negative, ie when multiplied
	// they are positive.
	return ( Vector::crossProduct(v, (p1 - a)).getz() * Vector::crossProduct(v, (p2 - a)).getz() ) >= 0;
}
