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

#include "Vector.h"

// default constructor
Vector::Vector()
{
   x=y=z=w=angle=0.0f;
}

/*
 * Constructor, takes x,y,z value of vector, and w and creates a Vector with these values.
 * w=1 for a point, 0 for a vector representation
 */
Vector::Vector (float newX, float newY, float newZ, float newW)
{
   x=newX;
   y=newY;
   z=newZ;
   w=newW;
   angle = getAngle(this);
   color = 0;
}

void Vector::update(float newX, float newY)
{
   x = newX;
   y = newY;
   angle = getAngle(this);
}

Vector Vector::operator+ (Vector v)
{
   return Vector (x+v.x, y+v.y, z+v.z, w+v.w);
}

Vector Vector::operator- (Vector v)
{
   return Vector  (x-v.x, y-v.y, z-v.z, w-v.w);
}

Vector Vector::operator* (float s)
{
   return Vector (x*s, y*s, z*s, w*s);
}

Vector Vector::operator/ (float s)
{
   return Vector (x/s, y/s, z/s, w/s);
}

bool Vector::operator== (Vector v)
{
   return (x == v.x && y==v.y && z==v.z);
}

// returns a vector perpendicular to both v1 and v2
Vector Vector::crossProduct (Vector v1, Vector v2)
{
   Vector result;
   result.x = v1.y * v2.z - v1.z * v2.y;
   result.y = v1.z * v2.x - v1.x * v2.z;
   result.z = v1.x * v2.y - v1.y * v2.x;
   return result;
}

// length of a vector
float Vector::norm()
{
   return sqrt(x*x + y*y + z*z);
}

// returns the angle in radians between two vectors, v1 and v2 
float Vector::getAngle (Vector v1, Vector v2)
{
   return acos((v1.x*v2.x + v1.y*v2.y + v1.z*v2.z)/(v1.norm()*v2.norm()));
}

float Vector::getAngle(Vector* const v)
{
   float ang = acos(v->getx()/v->norm());

   if (v->gety() < 0)
      ang = 2*PI - ang;

   return ang;
}

// returns distance between two points, represented by Vector objects
float Vector::getDistance (Vector v1, Vector v2)
{
   return sqrt(((v2.x-v1.x)*(v2.x-v1.x))+((v2.y-v1.y)*(v2.y-v1.y))+((v2.z-v1.z)*(v2.z-v1.z)));
}

void Vector::setColor(int c)
{
   if (c != 0 && c != 1 && c != 2 && c != 3)
   {
      printf("Trying to set with invalid color value %d.\nValid values are 0,1,2,3\n", c);
      assert(false);
   }

   color = c;
}
