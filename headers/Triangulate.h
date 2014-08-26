/*
 * Based on code submitted to FlipCode.com by
 * John W. Ratcliff (jratcliff@verant.com) on July 22, 2000
 *
 * modified by Jeff Nicholson, March 13, 2012
 * In Process, changed original implementation to use a working
 * set of vertices rather than complicated array of indexes, which
 * provided no real savings, since we are duplicating vertices to 
 * result anyways.
 */

#ifndef _TRIANGULATE_H
#define _TRIANGULATE_H

#include <vector>
#include <assert.h>

#include "AGVector.h"

using std::vector;

class Triangulate {

public:
   /* Puts vertices of triangulation of polygon into result */
   static bool Process( vector<AGVector> &polygon, vector<AGVector *> &result);
	
   /* returns area of polygon */
   static float Area(const vector<AGVector> &polygon);
	
   /* true if p is inside triangle(abc) */
   static bool InsideTriangle(AGVector a, AGVector b, AGVector c, AGVector p);

private:
   /* true if points p1 and p2 are on the same side of line segment ab */
   static bool SameSide(AGVector a, AGVector b, AGVector p1, AGVector p2);

   /* determines if the section of the polygon defined by the three vertices
   * abc (where abc are at indices u,v,w in polygon) can be
   * 'snipped' (considered a triangle in the triangulation of the polygon).
   * True if abc is convex and empty, false if another vertex of the polygon lies within
   * abc, or if abc forms a right turn (non-convex, assuming counter clockwise (ccw) traversal).
   * V is an array of integers, containing the indices of polygon in ccw order, n is its length
   */
    static bool Snip(const vector<AGVector *> &polygon, int u, int v, int w);
};

#endif /* _TRIANGULATE_H */
