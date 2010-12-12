// Cylinder
//    wraps the gluCylinder so it is easier to use
//
// Carick Wienke

#include "Cylinder.h"

Cylinder::Cylinder()
{
}

   // draws the cylinder to the sceen
void Cylinder::Redraw()
{
   if( visible )
   {
      Shape::beginTransform();

      material.GLInit();

      GLfloat emit[4] = {0, 0, 0, 1};
      glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emit );

      gluCylinder( quadric, 1, 1, 1, 50, 50 );

      Shape::endTransform();
   }
}
