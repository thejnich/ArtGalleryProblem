#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include <QtOpenGL>
#include <vector>

#include "Vector.h"
#include "SimplePolygon.h"

#define WIDGET_HEIGHT 800
#define WIDGET_WIDTH 1200
#define REFRESH_RATE 1

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
   void toggleTriangulate(bool state);
   void toggleColor(bool state);

signals:

protected:
   void initializeGL();
   void resizeGL(int w, int h);
   void paintGL();
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
	
private:
   QTimer *timer;
   SimplePolygon *polygon;
};

#endif  /* _GLWIDGET_H */
