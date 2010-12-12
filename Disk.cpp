// --------------------------------------------------------
// Disk
//    wrapper for the gluDisk
//
// Carick Wienke

#include "Disk.h"

Disk::Disk()
{
}

void Disk::Redraw()
{
   if( visible )
   {
      Shape::beginTransform();

      material.GLInit();

      GLfloat emit[4] = {0, 0, 0, 1};
      glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emit );

      gluDisk( quadric, 0, 1, 50, 5 );

      Shape::endTransform();
   }
}
