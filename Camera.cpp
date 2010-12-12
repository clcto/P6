// --------------------------------------------------------
// Camera.cpp
//    A class that holds the data about the camera
//
// Carick Wienke
// --------------------------------------------------------


#include "Camera.h"
#include "radians.h"

#include <GL/glut.h>
#include <iostream>

using namespace std;

   // -----------------------------------------------------
   // Constructor:
   //    sets up default values
Camera::Camera()
{
   SetEyeSpherical( 0, 0, 60 );

   center[X] = 0; center[Y] = 0; center[Z] = 0;
   up[X] = 0; up[Y] = 0; up[Z] = 1;

   pFar = 10000;
   pNear = 1;
   fov = 30;
   aspect = 1;
}

   // -----------------------------------------------------
   // sets up the matrices so everything appears
   // as i tell it it should
void Camera::SetUpGLMatrices() const
{
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( fov, aspect, pNear, pFar );

   glMatrixMode( GL_MODELVIEW );

   gluLookAt( eye[X], eye[Y], eye[Z],
              center[X], center[Y], center[Z],
              up[X], up[Y], up[Z] );
}

void Camera::SetEyeSpherical( float t, float p, 
                              float r )
{
   eye[X] = r * cos( t*TO_RAD ) * cos( p*TO_RAD );
   eye[Y] = r * cos( t*TO_RAD ) * sin( p*TO_RAD );
   eye[Z] = r * sin( t*TO_RAD );
}

float Camera::GetElevation()
{
   return asin( eye[Z] / 
      sqrt( eye[X]*eye[X] + 
            eye[Y]*eye[Y] + 
            eye[Z]*eye[Z] ) );
}

float Camera::GetHeading()
{
   return atan2( eye[Y], eye[X] );
}

float Camera::GetRadius()
{
   return 
      sqrt( eye[X]*eye[X] + 
            eye[Y]*eye[Y] + 
            eye[Z]*eye[Z] );
}

void Camera::NextFrame()
{
   static uint frame = 0;
   static int cur = -1;
   static double dx=0, dy=0, dz=0;

   if( cur >= (int)path.size() - 1 )
      return;

   double frame_time = ++frame * 0.04;
   if( frame_time < path[ cur+1 ].time )
   {
      if( cur >= 0 )
         SetDeltaEyeRectangular( dx, dy, dz );
   }
   else
   {
      ++cur;
      cerr << path[cur].location[X] << "\n";
      cerr << path[cur].location[Y] << "\n";
      cerr << path[cur].location[Z] << "\n";
      SetEyeRectangular( path[ cur ].location[X],
                         path[ cur ].location[Y],
                         path[ cur ].location[Z] );
      dx = path[ cur+1 ].location[X] -
                  path[cur].location[X];
      dy = path[ cur+1 ].location[Y] -
                  path[cur].location[Y];
      dz = path[ cur+1 ].location[Z] -
                  path[cur].location[Z];

      dx /= 25*(path[cur+1].time - path[cur].time);
      dy /= 25*(path[cur+1].time - path[cur].time);
      dz /= 25*(path[cur+1].time - path[cur].time);
   }
}

void Camera::SetEyeRectangular( double x, double y,
                                double z )
{
   eye[X] = x;
   eye[Y] = y;
   eye[Z] = z;
}

void Camera::SetDeltaEyeRectangular(
               double dx, double dy, double dz )
{
   eye[X] += dx;
   eye[Y] += dy;
   eye[Z] += dz;

   cerr << eye[X] << ", " << eye[Y] << ", " << eye[Z] << "\n";
}

void Camera::SetPath( Path p )
{
   path = p;
}
