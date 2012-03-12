/*
 *  Vector.h
 *  a2
 *
 *  The Vector class represents a 3d vector/point (depending on value of w). 
 *  Included are many operations that can be perfomed, such as scaling, crossproduce, norm etc.
 *
 *  Created by Jeff Nicholson on 10-10-23.
 *  Copyright 2010 University of Calgary. All rights reserved.
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#define PI 3.141592

class Vector
{
public:
	
	float x, y, z, w;

	Vector();
	Vector (float newX, float newY, float newZ, float newW);

	Vector operator+ (Vector v);
	Vector operator- (Vector v);
	Vector operator* (float s);
	Vector operator/ (float s);
	bool operator== (Vector v);

	static Vector crossProduct (Vector v1, Vector v2);
	static float getAngle (Vector v1, Vector v2);
	static float getDistance (Vector v1, Vector v2);

	float norm();
};

#endif /* VECTOR_H */
