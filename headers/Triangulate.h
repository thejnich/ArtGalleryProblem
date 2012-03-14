/*
 * Based on code submitted to FlipCode.com by
 * John W. Ratcliff (jratcliff@verant.com) on July 22, 2000 
 *
 * modified by Jeff Nicholson, March 13, 2012
 */

#ifndef _TRIANGULATE_H
#define _TRIANGULATE_H

#include <vector>

#include "Vector.h"

using std::vector;

class Triangulate {

public:
	/* Puts vertices of triangulation of polygon into result */
	static bool Process(const vector<Vector> &polygon, vector<Vector> &result);
	
	/* returns area of polygon */
	static float Area(const vector<Vector> &polygon);
	
	/* true if p is inside triangle(abc) */
	static bool InsideTriangle(Vector a, Vector b, Vector c, Vector p);

private:
	/* true if points p1 and p2 are on the same side of line segment ab */
	static bool SameSide(Vector a, Vector b, Vector p1, Vector p2);

	/* determines if the section of the polygon defined by the three vertices
	 * abc (where abc are at indices V[u,v,w] int polygon) can be 
	 * 'snipped' (considered a triangle in the triangulation of the polygon).
	 * True if abc is convex and empty, false if another vertex of the polygon lies within
	 * abc, or if abc forms a right turn (non-convex, assuming counter clockwise (ccw) traversal).
	 * V is an array of integers, containing the indices of polygon in ccw order, n is its length
	 */
	 static bool Snip(const vector<Vector> &polygon, int u, int v, int w, int n, const int V[]); 
};

#endif /* _TRIANGULATE_H */
