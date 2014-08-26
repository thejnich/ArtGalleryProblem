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
#include <assert.h>
#include <stdio.h>

static const float PI = 3.141592;

class AGVector
{
public:
   AGVector();
   AGVector(float newX, float newY, float newZ, float newW);

   void update(float x, float y);
   float getx() const {return x;};
   float gety() const {return y;};
   float getz() const {return z;};
   float getw() const {return w;};
   float getangle() const {return angle;};
   AGVector operator+ (AGVector v);
   AGVector operator- (AGVector v);
   AGVector operator* (float s);
   AGVector operator/ (float s);
   bool operator== (AGVector v);

   static AGVector crossProduct (AGVector v1, AGVector v2);
   static float getAngle (AGVector v1, AGVector v2);
   static float getAngle (AGVector * const v);
   static float getDistance (AGVector v1, AGVector v2);

   float norm();
   int getColor() const {return _color;};
   void setColor(int color);

private:
   float x, y, z, w, angle;
   int _color;
};

#endif /* VECTOR_H */
