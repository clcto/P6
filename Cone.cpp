// --------------------------------------------------------
// Cone.cpp
//    A wrapper for a GLU Cone 
//    (well really a specific cylinder...)
//
// Carick Wienke
// --------------------------------------------------------
#include "Cone.h"

Cone::Cone()
{
   material = Material::CHROME;  
}

   // -----------------------------------------------------
   // Redraw
   //    redraws the cone to the screen
void Cone::Redraw()
{
   if( visible )
   {
      Shape::beginTransform();

      material.GLInit();

      GLfloat emit[4] = {0, 0, 0, 1};
      glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emit );

      gluCylinder( quadric, 1, 0, 1, 50, 50 );

      Shape::endTransform();
   }
}
