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

};

#endif /* _TRIANGULATE_H */
