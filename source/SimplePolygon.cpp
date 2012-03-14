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
 /* TODO This fucking peice of garbage is not currently working!!! 
  * BUGFOUND: this alg assums each successive triangle shares an
  * edge with the previous triangle. This IS NOT guaranteed by the
  * current triangulation implementation, so the alg fails in certain
  * situations. My need a half edge data structure or something so 
  * adjacent tris can be walked for the coloring
  */ 
bool SimplePolygon::threeColor(const vector<Vector*> &tris)
{

	printf("\n\nEntering threeColor this peice of shit\n");
	if(tris.size() < 3)
		return true;
	// reset previous coloring
	for(int i = 0; i < (int)tris.size(); ++i) {
		tris[i]->setColor(0);
	}

	for(int i = 0; i < (int)tris.size()-2; i+=3) {
	
		int sum = 0;
		int toColor;
		Vector *v;
		for(int j = 0; j < 3; ++j) {
			v = tris[i+j];
			if(v->getColor() == 0)
				toColor = j;
			else
				sum += v->getColor();
		}
		// if the sum is 0, this is the first tri, so we just color them 1,2,3
		if(sum == 0) {
			for(int j = 0; j < 3; ++j) {
				tris[i+j]->setColor(j+1);
			}
		}
		// all other cases, only one vertex should be uncolored
		// the other two are either sum = 1+2; 1+3; 2+3
		// in each case this vertex should be 6-sum
		else {
			if( (6-sum) <= 0 || (6-sum) > 3 ) {
				printf("something fucked up, trying to set invalid value %d\n", 6-sum);
				return false;
			}
			tris[i+toColor]->setColor(6-sum);
		}
	}

	return true;
}
