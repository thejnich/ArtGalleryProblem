#include "Triangulate.h"

/* Puts vertices of triangulation of polygon into result */
bool Triangulate::Process(vector<Vector> &polygon, vector<Vector*> &result)
{
	result.clear();
	int n = polygon.size();

	if (n < 3)
		return false;

	vector<Vector*> workingPoly;

	// need to ensure that we traverse polygon in ccw order, workingPoly
	// will contain vertices in ccw order
	if (Area(polygon) > 0.f)
   {
		for (int i = 0; i < n; ++i)
      {
			workingPoly.push_back(&polygon[i]);
		}
	}
	else
   {
		for (int i = 0; i < n; ++i)
      {
			workingPoly.push_back(&polygon[(n-1)-i]);
		}
	}

	assert(n = workingPoly.size());
	int j = 0;
	int work_sz, u,v,w;
	while ((work_sz = workingPoly.size()) > 3)
   {
		u = j % work_sz;
		v = (j+1) % work_sz;
		w = (j+2) % work_sz;

		if (Snip(workingPoly, u,v,w) )
      {
			// add triangle uvw to result, remove v from working set
			result.push_back(workingPoly[u]);
			result.push_back(workingPoly[v]);
			result.push_back(workingPoly[w]);
			workingPoly.erase(workingPoly.begin() + v);
		}
		else
      {
			j++;
      }
	}

	// should be three vertices left in working set,
	// this is the last triangle of triangulation, add it
	assert(workingPoly.size() == 3);
	for (int i = 0; i < 3; ++i)
   {
		result.push_back(workingPoly[i]);
	}

	return true;
}
	
/* returns area of polygon */
float Triangulate::Area(const vector<Vector> &polygon)
{
	int n = polygon.size();

	if (n < 3)
		return 0.f;

	float area = 0.f;

	for (int p = n-1, q = 0; q < n; p = q++)
   {
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
	return (Vector::crossProduct(v, (p1 - a)).getz() * Vector::crossProduct(v, (p2 - a)).getz()) >= 0;
}

/* determines if the section of the polygon defined by the three vertices
 * abc (where abc are at indices u,v,w in polygon) can be 
 * 'snipped' (considered a triangle in the triangulation of the polygon).
 * True if abc is convex and empty, false if another vertex of the polygon lies within
 * abc, or if abc forms a right turn (non-convex, assuming counter clockwise (ccw) traversal).
 * V is an array of integers, containing the indices of polygon in ccw order, n is its length
 */
bool Triangulate::Snip(const vector<Vector*> &polygon, int u, int v, int w)
{
	Vector a = *polygon[u];
	Vector b = *polygon[v];
	Vector c = *polygon[w];
	// if abc forms a right turn, cannot snip
	if (Vector::crossProduct( (b-a), (c-b) ).getz() <= 0)
		return false;

	Vector p;
	// check if any other points of polygon are inside abc
	for (int i = 0; i < (int)polygon.size(); ++i)
   {
		if (i == u || i == v || i == w)
			continue;

		p = *polygon[i];
		if (InsideTriangle(a,b,c,p))
			return false;
	}

	return true;	
}
