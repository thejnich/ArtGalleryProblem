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

private:
	vector<Vector> *vertices;	
	vector<Vector*> *triVerts;
	int findPoint(Vector v);
	bool threeColor(vector<Vector*> &tris);
	bool adjacent(Vector **tri1, Vector **tri2);
};

#endif /* _SIMPLE_POLYGON_H */
