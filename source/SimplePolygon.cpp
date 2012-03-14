#include "SimplePolygon.h"

bool comparePolarAngle(Vector a, Vector b)
{
	return a.getangle() < b.getangle();
}

SimplePolygon::SimplePolygon()
{
	vertices = new vector<Vector>();
	triVerts = new vector<Vector*>();
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
	for(vector<Vector>::iterator it = vertices->begin(); it != vertices->end(); ++it) {
		switch(it->getColor()) {
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
		}
		glVertex3f(it->getx(), it->gety(), it->getz());
	}
	glEnd();
	
	// render triangulation of polygon
	glColor3f(0.f,0.f,1.f);
	glLineWidth(2);
	if(triVerts->size() > 2) {
		for(int i = 0; i < (int)triVerts->size()-2; i+=3) {
			Vector a = *(*triVerts)[i];
			Vector b = *(*triVerts)[i+1];
			Vector c = *(*triVerts)[i+2];
			glBegin(GL_LINE_LOOP);
			glVertex3f(a.getx(), a.gety(), a.getz());
			glVertex3f(b.getx(), b.gety(), b.getz());
			glVertex3f(c.getx(), c.gety(), c.getz());
			glEnd();
		}
	}

	// draw lines connecting vertices, showing boundary of polygon
	glColor3f(1.0,1.0,0);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	for(vector<Vector>::iterator it = vertices->begin(); it != vertices->end(); ++it) {
		glVertex3f(it->getx(), it->gety(), it->getz());
	}
	glEnd();
}

void SimplePolygon::Clear()
{
	if(NULL == vertices)
		return;
	vertices->clear();
	triVerts->clear();
}

int SimplePolygon::findPoint(Vector v)
{
	if (vertices->size() == 0) {
		return -1;
	}

	// Find the point closest
	int index = 0;
	float smallestDistance = Vector::getDistance(v, (*vertices)[index]);
	float dist;
	// loop through all vertices, tracking which is closest
	for (uint i = 1; i < vertices->size(); i++)
	{
		dist = Vector::getDistance(v, (*vertices)[i]);
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

void SimplePolygon::Update(Vector v, bool remove)
{
	int closestPointIndex = findPoint(v);

	if(remove) {
		if(closestPointIndex != -1)
			vertices->erase(vertices->begin() + closestPointIndex);
	}
	else {
		if(closestPointIndex == -1) {
			vertices->push_back(v);
		}
		else {
			(*vertices)[closestPointIndex].update(v.getx(), v.gety());
		}
	}
	
	Triangulate::Process(*vertices, *triVerts);	
	threeColor(*triVerts);
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
bool SimplePolygon::threeColor(vector<Vector*> &tris)
{

	printf("\n\nEntering threeColor\n");
	if(tris.size() < 3)
		return true;
	// reset previous coloring
	for(int i = 0; i < (int)tris.size(); ++i) {
		tris[i]->setColor(0);
	}

	int numTris = tris.size() / 3;

	// color the first triangle
	for(int i = 0; i < 3; ++i) {
		tris[i]->setColor(i+1);
	}

	int colored = 1;

	Vector **lastColored = &tris[0];
	Vector **current = &tris[3];
	// loop until we have colored all the triangles
	while( colored != numTris ) {
		
		// check if current is adjacent (shares edge) with lastColored
		if(adjacent(lastColored, current)) {
			// if adjacent, then we color the remaining vertex of current
			int sum = 0;
			int toColor;
			Vector *v;
			for(int j = 0; j < 3; ++j) {
				v = *(current+j); 
				if(v->getColor() == 0)
					toColor = j;
				else
					sum += v->getColor();
			}
			if( sum != 6 ) {
				(*(current+toColor))->setColor(6-sum);
				colored++;
				lastColored = current;
			}
			else {
				// already colored, keep looking
				printf("already colored,keep going\n");
			}
		}
		current += 3;
		if(current == lastColored)
			current += 3;
		if(current > (&tris[0] + tris.size()-1)) {
			current = &tris[0];
			if(current == lastColored)
				current += 3;
		}
		printf("colored %d of %d\n", colored, numTris);
	}
	return true;
}

bool SimplePolygon::adjacent(Vector **tri1, Vector **tri2)
{
	Vector t1a = **tri1;
	Vector t1b = **(tri1+1);
	Vector t1c = **(tri1+2);
	Vector t2a = **(tri2);
	Vector t2b = **(tri2+1);
	Vector t2c = **(tri2+2);

	if( (t1a == t2a || t1a == t2b || t1a == t2c) && (t1b == t2a || t1b == t2b || t1b == t2c) )
		return true;
	if( (t1a == t2a || t1a == t2b || t1a == t2c) && (t1c == t2a || t1c == t2b || t1c == t2c) )
		return true;
	if( (t1b == t2a || t1b == t2b || t1b == t2c) && (t1c == t2a || t1c == t2b || t1c == t2c) )
		return true;

	return false;
}
