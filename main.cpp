// --------------------------------------------------------
// main.cpp for Program 3
// 
// This program shows a 3D Scene and allows the camera
//    to be modified.
//
//    Additional Features:
//       Lighting
//       Read a scene from a file
//       ability to select and change shapes
//       selected shape "emits" light to show it is
//          selected
//
// Assignment 3: 3D Graphics
// UNH CS 770 - Computer Graphics
// Due: 2010.10.14
// --------------------------------------------------------

#include <vector>
#include <iostream>
#include <GL/glut.h>

#include "Shape.h"
#include "Control.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Snowman.h"
#include "Path.h"

using std::vector;
using std::cout;

const int windowWidth  = 500;
const int windowHeight = 500;
int window;

// Function Declarations
void appInit();
void timer( int );
void redraw();


   // initializes the GL portion of the application
void appInit()
{
	glutInitDisplayMode( GLUT_DEPTH | 
           GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize( windowWidth, windowHeight ); 

      // set the window properties
	glutInitWindowPosition( 100, 150 );
   window = glutCreateWindow( "Assignment 6 - "
                                  "Animation" );

      // define the function to call when a 
      // redraw is requested
	glutDisplayFunc( redraw );
   glEnable( GL_DEPTH_TEST );

   glEnable( GL_LIGHTING );
   glEnable( GL_LIGHT0 );

   glShadeModel( GL_SMOOTH );

   glClearColor( 1.0, 1.0, 1.0, 0.0 );
   
   Control::Instance()->Initialize( "Control", window );
}

void timer( int value )
{
   if( Scene::Instance()->IsRunning() )
      glutPostWindowRedisplay( window );

   glutTimerFunc( 41, timer, 0 );
}

   // redraws the scene.
   //    clears, draws all the shapes, and flused
void redraw( void )
{
      // clear the screen 
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   Scene::Instance()->Redraw();
   
   glutSwapBuffers();
}

   // runs the program. Sets up the handlers and menu
   // so the program actually does something. 
int main( int argc, char **argv )
{
      // initialize toolkit
	glutInit( &argc, argv );

   if( argc > 1 )
      Scene::Instance()->ReadFile( argv[1] );

	appInit();

   timer( 0 );

      // let glut do its thing
	glutMainLoop();
}
