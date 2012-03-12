#ifndef _GLWIDGET_H
#define _GLWIDGET_H

// cross-platform support
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <QtOpenGL>
#include <vector>

#include "Vector.h"

#define WIDGET_HEIGHT 800
#define WIDGET_WIDTH 1200
#define REFRESH_RATE 1
#define MAX_DIST 0.1

using namespace std;
using std::vector;

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(QWidget *parent = NULL);
	~GLWidget();
	QSize sizeHint() const;
	QSize minimumSizeHint() const;
	
public slots:
	void clearPolygon();

signals:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	
private:
	QTimer *timer;
	vector<Vector> *polygon;

	int findPoint(Vector v);

};

#endif  /* _GLWIDGET_H */
