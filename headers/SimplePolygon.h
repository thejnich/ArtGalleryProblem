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
	int findPoint(Vector v);
};

#endif /* _SIMPLE_POLYGON_H */
