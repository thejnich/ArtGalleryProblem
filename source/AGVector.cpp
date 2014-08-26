/*
 *  Vector.cpp
 *  a2
 *
 *  The Vector class represents a 3d vector/point (depending on value of w). 
 *  Included are many operations that can be perfomed, such as scaling, crossproduce, norm etc.
 *
 *  Created by Jeff Nicholson on 10-10-23.
 *  Copyright 2010 University of Calgary. All rights reserved.
 *
 */

#include "AGVector.h"

// default constructor
AGVector::AGVector()
{
   x=y=z=w=angle=0.0f;
}

/*
 * Constructor, takes x,y,z value of vector, and w and creates a AGVector with these values.
 * w=1 for a point, 0 for a vector representation
 */
AGVector::AGVector(float newX, float newY, float newZ, float newW)
{
   x=newX;
   y=newY;
   z=newZ;
   w=newW;
   _color = 0;
   angle = getAngle(this);
}

void AGVector::update(float newX, float newY)
{
   x = newX;
   y = newY;
   angle = getAngle(this);
}

AGVector AGVector::operator+ (AGVector v)
{
   return AGVector(x+v.x, y+v.y, z+v.z, w+v.w);
}

AGVector AGVector::operator- (AGVector v)
{
   return AGVector(x-v.x, y-v.y, z-v.z, w-v.w);
}

AGVector AGVector::operator* (float s)
{
   return AGVector(x*s, y*s, z*s, w*s);
}

AGVector AGVector::operator/ (float s)
{
   return AGVector(x/s, y/s, z/s, w/s);
}

bool AGVector::operator== (AGVector v)
{
   return (x == v.x && y==v.y && z==v.z);
}

// returns a vector perpendicular to both v1 and v2
AGVector AGVector::crossProduct (AGVector v1, AGVector v2)
{
   AGVector result;
   result.x = v1.y * v2.z - v1.z * v2.y;
   result.y = v1.z * v2.x - v1.x * v2.z;
   result.z = v1.x * v2.y - v1.y * v2.x;
   return result;
}

// length of a vector
float AGVector::norm()
{
   return sqrtf(x*x + y*y + z*z);
}

// returns the angle in radians between two vectors, v1 and v2 
float AGVector::getAngle (AGVector v1, AGVector v2)
{
   return acosf((v1.x*v2.x + v1.y*v2.y + v1.z*v2.z)/(v1.norm()*v2.norm()));
}

float AGVector::getAngle(AGVector * const v)
{
   float ang = acosf(v->getx()/v->norm());

   if (v->gety() < 0)
      ang = PI * 2.f - ang;

   return ang;
}

// returns distance between two points, represented by AGVector objects
float AGVector::getDistance (AGVector v1, AGVector v2)
{
   return sqrtf(((v2.x-v1.x)*(v2.x-v1.x))+((v2.y-v1.y)*(v2.y-v1.y))+((v2.z-v1.z)*(v2.z-v1.z)));
}

void AGVector::setColor(int color)
{
   if (color != 0 && color != 1 && color != 2 && color != 3) {
      printf("Trying to set with invalid color value %d.\nValid values are 0,1,2,3\n", (int) color);
      assert(false);
   }

   _color = color;
}
