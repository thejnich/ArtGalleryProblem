[![Build Status](https://travis-ci.org/thejnich/ArtGalleryProblem.svg?branch=master)](https://travis-ci.org/thejnich/ArtGalleryProblem)

Application for visualizing the Art Gallery Problem

### Dependencies
* QT, opengl

## Usage
### Build
* qmake (generates the Makefile)
* make (build)

### Run
* ./run

### Or, XCode
* Should just be able to open and run. xcodeproj was generated with qmake:
  * qmake -spec macx-xcode

### Summary
Given n vertices, which form a polygon (ie the floor plan of an art gallery),
how do you place the minimum number of guards in such a way that together, the
guards can see the entire polygon?

There are variations of this problem specifying whether or not the polygon can
contain holes, and the limitations of the guards.

Initially the goal of this application is to place vertex guards (guards are only 
placed at vertices of the polygon, they can see 360 degrees, cannot move), in a
polygon with no holes. This is accomplished by triangulating the polygon, then
three coloring the triangulation, picking a color, and placing guards at these
vertices. This gives you floor(n/3) guards for an n vertex polygon.
See docs/ArtGallery_NoHoles.pdf for detailed description/proof.
