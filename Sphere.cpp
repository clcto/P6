// --------------------------------------------------------
// Sphere
//    a wrapper for the gluSphere
//
// Carick Wienke

#include "Sphere.h"

Sphere::Sphere()
{
}

void Sphere::Redraw()
{
   if( visible )
   {
      Shape::beginTransform();

      material.GLInit();

      GLfloat emit[4] = {0, 0, 0, 1};
      glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emit );

      gluSphere( quadric, 1, 50, 50 );

      Shape::endTransform();
   }
}
