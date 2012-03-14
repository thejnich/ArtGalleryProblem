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
	Vector();
	Vector (float newX, float newY, float newZ, float newW);

	void update(float x, float y);
	float getx() const {return x;};
	float gety() const {return y;};
	float getz() const {return z;};
	float getw() const {return w;};
	float getangle() const {return angle;};
	Vector operator+ (Vector v);
	Vector operator- (Vector v);
	Vector operator* (float s);
	Vector operator/ (float s);
	bool operator== (Vector v);

	static Vector crossProduct (Vector v1, Vector v2);
	static float getAngle (Vector v1, Vector v2);
	static float getAngle (Vector* const v);
	static float getDistance (Vector v1, Vector v2);

	float norm();

private:
	float x, y, z, w, angle;
};

#endif /* VECTOR_H */
