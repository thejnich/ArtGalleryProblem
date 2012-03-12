#include "GLWidget.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer->start(REFRESH_RATE);
}

GLWidget::~GLWidget()
{
	timer = NULL;
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
	
	glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) 
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
}


