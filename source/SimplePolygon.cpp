#include "SimplePolygon.h"

bool comparePolarAngle(Vector a, Vector b)
{
	return a.getangle() < b.getangle();
}

SimplePolygon::SimplePolygon()
{
	vertices = new vector<Vector>();
}

SimplePolygon::~SimplePolygon()
{
	delete vertices;
}

void SimplePolygon::DrawPolygon()
{
	glPointSize(10.0);
	glColor3f(1.0,1.0,0);

	glBegin(GL_POINTS);
	for(vector<Vector>::iterator it = vertices->begin(); it != vertices->end(); ++it) {
		glVertex3f(it->getx(), it->gety(), it->getz());
	}
	glEnd();

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
	
}


