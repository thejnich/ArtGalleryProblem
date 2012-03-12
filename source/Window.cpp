/*
 *  Window.cpp
 *  a2
 *
 *  Created by Jeff Nicholson on 11-10-17.
 *  Copyright 2011 University of Calgary. All rights reserved.
 *
 */

#include "Window.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle(tr("Basic QT skeleton"));
	
	glWidget = new GLWidget;

	centralWidget = new QWidget;
	setCentralWidget(centralWidget);
	
	mainLayout = new QHBoxLayout;
	
	mainLayout->addWidget(glWidget);
	centralWidget->setLayout(mainLayout);
}

