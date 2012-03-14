#ifndef _SIMPLE_POLYGON_H
#define _SIMPLE_POLYGON_H

#include <vector>
#include <QtOpenGL>

#include "Vector.h"
#include "Triangulate.h"

#define MAX_DIST 0.1

using std::vector;

class SimplePolygon {

public:
	SimplePolygon();
	~SimplePolygon();
	void DrawPolygon();
	void Clear();
	void Update(Vector v, bool remove);
	void Update();
	bool getTriangulate() {return _triangulate;};
	void setTriangulate(bool b) {_triangulate = b;};
	bool isColored() {return _color;};
	void setColored(bool b) {_color = b;};

private:
	vector<Vector> *vertices;	
	vector<Vector*> *triVerts;
	int findPoint(Vector v);
	bool threeColor(vector<Vector*> &tris);
	bool adjacent(Vector **tri1, Vector **tri2);
	bool _triangulate;
	bool _color;
};

#endif /* _SIMPLE_POLYGON_H */
