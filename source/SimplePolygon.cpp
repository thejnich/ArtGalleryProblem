#include "SimplePolygon.h"

SimplePolygon::SimplePolygon()
{
   vertices = new vector<AGVector>();
   triVerts = new vector<AGVector *>();
   _triangulate = false;
   _color = false;
}

SimplePolygon::~SimplePolygon()
{
   delete vertices;
   delete triVerts;
}

void SimplePolygon::DrawPolygon()
{
   // render vertices of polygon
   glPointSize(10.0);
   glBegin(GL_POINTS);
   for (vector<AGVector>::iterator it = vertices->begin(); it != vertices->end(); ++it)
   {
      if (_color) 
      {
         switch (it->getColor())
         {
            case 1:
               glColor3f(1.f,0.f,0.f);
               break;
            case 2:
               glColor3f(0.f,1.f,0.f);
               break;
            case 3:
               glColor3f(1.f,0.f,1.f);
               break;
            default:
               glColor3f(1.f,1.f,0.f);
               break;
         }
      }
      else
      {
         glColor3f(1.f,1.f,0.f);
      }
      glVertex3f(it->getx(), it->gety(), it->getz());
   }
   glEnd();

   if (_triangulate)
   {
      // render triangulation of polygon
      glColor3f(0.f,0.f,1.f);
      glLineWidth(2);
      if (triVerts->size() > 2)
      {
         for (int i = 0; i < (int)triVerts->size()-2; i+=3)
         {
            AGVector a = *(*triVerts)[i];
            AGVector b = *(*triVerts)[i+1];
            AGVector c = *(*triVerts)[i+2];
            glBegin(GL_LINE_LOOP);
            glVertex3f(a.getx(), a.gety(), a.getz());
            glVertex3f(b.getx(), b.gety(), b.getz());
            glVertex3f(c.getx(), c.gety(), c.getz());
            glEnd();
         }
      }
   }

   // draw lines connecting vertices, showing boundary of polygon
   glColor3f(1.0,1.0,0);
   glLineWidth(5);
   glBegin(GL_LINE_LOOP);
   for (vector<AGVector>::iterator it = vertices->begin(); it != vertices->end(); ++it)
   {
      glVertex3f(it->getx(), it->gety(), it->getz());
   }
   glEnd();
}

void SimplePolygon::Clear()
{
   if (NULL == vertices)
      return;

   vertices->clear();
   triVerts->clear();
}

int SimplePolygon::findPoint(AGVector v)
{
   if (vertices->size() == 0)
   {
      return -1;
   }

   // Find the point closest
   int index = 0;
   float smallestDistance = AGVector::getDistance(v, (*vertices)[index]);

   // loop through all vertices, tracking which is closest
   float dist;
   for (uint i = 1; i < vertices->size(); i++)
   {
      dist = AGVector::getDistance(v, (*vertices)[i]);
      if (dist < smallestDistance)
      {
         index = i;
         smallestDistance = dist;
      }
   }

   // Threshold the distance so we dont get anything too far out
   if (smallestDistance > MAX_DIST)
      index = -1;

   return index;
}

void SimplePolygon::Update(AGVector v, bool remove)
{
   int closestPointIndex = findPoint(v);

   if (remove)
   {
      if (closestPointIndex != -1)
         vertices->erase(vertices->begin() + closestPointIndex);
   }
   else 
   {
      if (closestPointIndex == -1)
      {
         vertices->push_back(v);
      }
      else
      {
         (*vertices)[closestPointIndex].update(v.getx(), v.gety());
      }
   }
   Update();
}

void SimplePolygon::Update()
{
   // have to triangulate in order to color
   if (_triangulate) 
   {
      Triangulate::Process(*vertices, *triVerts);	
      if (_color)
         threeColor(*triVerts);
   }
}

/* every three vectors in tris represents one triangle
 * in a triangulation. This function three colors this
 * triangulation, ie any two vertices that share an edge
 * have different color, so each triangle will have a vertex of 
 * each color
 */
/* TODO Almost working, but not quite
 * Am now just brute forcing, but still not working, gets into
 * infinite loop on more complex polygons
 */
bool SimplePolygon::threeColor(vector<AGVector *> &tris)
{
   if (tris.size() < 3)
      return true;

   // reset previous coloring
   for (int i = 0; i < (int)tris.size(); ++i)
   {
      tris[i]->setColor(0);
   }

   assert(tris.size() % 3 == 0);
   int numTris = tris.size() / 3;

   // color the first triangle
   for (int i = 0; i < 3; ++i)
   {
      tris[i]->setColor(i + 1);
   }

   int colored = 1;

   int lastColoredIndex = 0;
   int currentIndex = 3;

   printf("Attempting to color %d triangles", numTris);

   // loop until we have colored all the triangles
   int attempts = 0;
   while (colored != numTris)
   {
      AGVector **lastColored = &tris[lastColoredIndex];
      AGVector **current = &tris[currentIndex];

      // check if current is adjacent (shares edge) with lastColored
      int adjacentSum = adjacent(lastColored, current);
      if (adjacentSum > -1)
      {
         // if adjacent, then we color the remaining vertex of current
         AGVector *v;
         bool didColor = false;
         for (int j = 0; j < 3; ++j)
         {
            v = *(current + j);
            if (v->getColor() == 0)
            {
               v->setColor(6 - adjacentSum);
               didColor = true;
               break;
            }
         }

         if (didColor)
         {
            colored++;
            lastColoredIndex = currentIndex;
         }
      }

      printf("colored %d of %d\n", colored, numTris);

      currentIndex = (currentIndex + 3) % tris.size();
      if (currentIndex == lastColoredIndex)
         currentIndex = (currentIndex + 3) % tris.size();

      attempts++;
      if (attempts > numTris * 10)
      {
         printf("Failed to three color");
         break;
      }
   }

   return true;
}

// Return positive value is adjacent, value is sum of adjacent sides vertex colors.
// Return -1 if not adjacent.
int SimplePolygon::adjacent(AGVector **tri1, AGVector **tri2)
{
   AGVector t1a = **tri1;
   AGVector t1b = **(tri1+1);
   AGVector t1c = **(tri1+2);
   AGVector t2a = **(tri2);
   AGVector t2b = **(tri2+1);
   AGVector t2c = **(tri2+2);

   if ((t1a == t2a || t1a == t2b || t1a == t2c) && (t1b == t2a || t1b == t2b || t1b == t2c))
      return t1a.getColor() + t1b.getColor();

   if ((t1a == t2a || t1a == t2b || t1a == t2c) && (t1c == t2a || t1c == t2b || t1c == t2c))
      return t1a.getColor() + t1c.getColor();

   if ((t1b == t2a || t1b == t2b || t1b == t2c) && (t1c == t2a || t1c == t2b || t1c == t2c))
      return t1b.getColor() + t1c.getColor();

   return -1;
}
