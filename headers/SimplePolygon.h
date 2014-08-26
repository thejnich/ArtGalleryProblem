#ifndef _SIMPLE_POLYGON_H
#define _SIMPLE_POLYGON_H

#include <vector>
#include <QtOpenGL>

#include "AGVector.h"
#include "Triangulate.h"

#define MAX_DIST 0.1

using std::vector;

class SimplePolygon {

public:
   SimplePolygon();
   ~SimplePolygon();
   void DrawPolygon();
   void Clear();
   void Update(AGVector v, bool remove);
   void Update();
   bool getTriangulate() {return _triangulate;};
   void setTriangulate(bool b) {_triangulate = b;};
   bool isColored() {return _color;};
   void setColored(bool b) {_color = b;};

private:
   vector<AGVector> *vertices;
   vector<AGVector *> *triVerts;
   int findPoint(AGVector v);
   bool threeColor(vector<AGVector *> &tris);
   bool adjacent(AGVector **tri1, AGVector **tri2);
   bool _triangulate;
   bool _color;
};

#endif /* _SIMPLE_POLYGON_H */
