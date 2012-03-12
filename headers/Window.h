/*
 *  Window.h
 *  a1
 *
 *  Created by Jeff Nicholson on 11-09-22.
 *  Copyright 2011 University of Calgary. All rights reserved.
 *
 */

#ifndef _WINDOW_H
#define _WINDOW_H

#include <QtGui>
#include "GLWidget.h"

class Window : public QMainWindow
{

public:
	Window(QWidget *parent = NULL);
	~Window() {}
	
private:
	QWidget *centralWidget;
	GLWidget *glWidget;
	QHBoxLayout *mainLayout;
	QVBoxLayout *controlLayout;

	QPushButton *clearPolyButton
};

#endif /* _WINDOW_H */
