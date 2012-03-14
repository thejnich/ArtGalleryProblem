#include "GLWidget.h"
#include "Triangulate.h"
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	polygon = new SimplePolygon();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer->start(REFRESH_RATE);
}

GLWidget::~GLWidget()
{
	delete timer;
	delete polygon;
}

void GLWidget::initializeGL()
{
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}
// from Steven Longay, keeps the aspect ratio when resizing window
void GLWidget::resizeGL(int w, int h)
{
	// Switch to the propper matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set drawing to take up the entire window
	glViewport(0, 0, w, h);
	
	float ratio;
	if ( w > h ) // In this case the w/h ratio is > 1
	{
		ratio = (float)w/(float)h;
		glOrtho(-ratio, ratio, -1, 1, -2, 2);
	}
	else        // In this case the h/w ratio is > 1
	{
		ratio = (float)h/(float)w;
		glOrtho(-1, 1, -ratio, ratio, -2, 2);
	}
	
	//Switch back to modelview matrix
	glMatrixMode(GL_MODELVIEW);
}


QSize GLWidget::sizeHint() const
{
	return QSize(WIDGET_WIDTH, WIDGET_HEIGHT);
}


QSize GLWidget::minimumSizeHint() const
{
	return QSize(WIDGET_WIDTH, WIDGET_HEIGHT);
}


void GLWidget::paintGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -2, 2);	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// place camera
	gluLookAt(0, 0, 1,		// camera position
			  0, 0, 0,		// look-at
			  0, 1, 0);		// up-vector
	
	polygon->DrawPolygon();

	// draw axis
	glColor3f(1.f,1.f,1.f);
	glBegin(GL_LINES);
	glVertex3f(0.f,1.f,0.f);
	glVertex3f(0.f,-1.f,0.f);
	glVertex3f(-1.f,0.f,0.f);
	glVertex3f(1.f,0.f,0.f);
	glEnd();


	glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) 
{
	if(event->type() == QEvent::MouseButtonPress) {
		// create vector based on click position, need to adjust to correct coordinates
		float xnew = ((float)event->x() / (float)WIDGET_WIDTH) *2 -1;
		float ynew = ((float)event->y() / (float)WIDGET_HEIGHT) *(-2) +1;
		float znew = 0.0f;
		float wnew = 1.0f;

		Vector v = Vector(xnew,ynew,znew,wnew);
	
		polygon->Update(v, !(event->button() == Qt::LeftButton));
	}
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(event->type() == QEvent::MouseMove) {
		// create vector based on click position, need to adjust to correct coordinates
		float xnew = ((float)event->x() / (float)WIDGET_WIDTH) *2 -1;
		float ynew = ((float)event->y() / (float)WIDGET_HEIGHT) *(-2) +1;
		float znew = 0.0f;
		float wnew = 1.0f;

		if(xnew < (-1.0)) 
			xnew = -1.0f;
		else if(xnew > 1.0)
			xnew = 1.0f;
		if(ynew < (-1.0))
			ynew = -1.0f;
		else if(ynew > 1.0)
			ynew = 1.0f;

		Vector v = Vector(xnew,ynew,znew,wnew);
		polygon->Update(v, false);
	}
}

void GLWidget::clearPolygon()
{
	if(NULL == polygon)
		return;
	polygon->Clear();
}
