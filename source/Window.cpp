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
	// init
	setWindowTitle(tr("Art Gallery Problem"));
	
	glWidget = new GLWidget;

	centralWidget = new QWidget;
	setCentralWidget(centralWidget);
	
	mainLayout = new QHBoxLayout;
	controlLayout = new QVBoxLayout;

	// set up buttons
	clearPolyButton = new QPushButton("Clear");
	connect(clearPolyButton, SIGNAL(clicked()), glWidget, SLOT(clearPolygon()));

	// add controls to controlLayout
	controlLayout->addWidget(clearPolyButton);

	// add main widgets and layouts
	mainLayout->addWidget(glWidget);
	mainLayout->addLayout(controlLayout);
	centralWidget->setLayout(mainLayout);
}

