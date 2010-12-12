#ifndef ARTICULATED_H_
#define ARTICULATED_H_

#include "Shape.h"
#include "Cone.h"

class Articulated : public Shape
{
   public:
      Articulated(int = 5);
      void Redraw();
      void NextFrame();
      
   protected:
      Articulated( int, bool );
      void makeArticulated( int );
      Cone cyl;
      Articulated* art; 

      bool root;
      int depth;
};

#endif
