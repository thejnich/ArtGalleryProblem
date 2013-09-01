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

   toggleTriangulateButton = new QPushButton("Triangulate");
   toggleTriangulateButton->setCheckable(true);
   connect(toggleTriangulateButton, SIGNAL(toggled(bool)), glWidget, SLOT(toggleTriangulate(bool)));

   toggleColorButton = new QPushButton("Three Color");
   toggleColorButton->setCheckable(true);
   connect(toggleColorButton, SIGNAL(toggled(bool)), glWidget, SLOT(toggleColor(bool)));

   // add controls to controlLayout
   controlLayout->addWidget(clearPolyButton);
   controlLayout->addWidget(toggleTriangulateButton);
   controlLayout->addWidget(toggleColorButton);

   // add main widgets and layouts
   mainLayout->addWidget(glWidget);
   mainLayout->addLayout(controlLayout);
   centralWidget->setLayout(mainLayout);
}

