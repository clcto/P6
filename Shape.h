// -----------------------------------------------------
// Shape.h:
//    abstract class that represents a shape, holding
//    code that is common to all 'shapes'
//
//  Carick Wienke <cdj26@unh.edu>
//
//  Derived from Demo0 by RDB
// -----------------------------------------------------

#ifndef SHAPE_H_
#define SHAPE_H_

#include <GL/glut.h>
#include <cmath>
#include <string>

#include "Color.h"
#include "Point.h"
#include "Material.h"
#include "Path.h"

using std::string;

class Shape
{

   public: //------------------------------------------

         // creates the shape in its own coordinate 
         // system
      Shape();

      virtual ~Shape();
      
         // SetTranslation
         // sets the translation of the shape
      void SetTranslation( GLfloat, GLfloat, GLfloat );
      void TranslateBy( float, float, float );

      Point GetTranslation() const;

         // set the scale of the shape
      void SetScale( Scale s );
      void SetScale( GLfloat, GLfloat, GLfloat ); 

      Scale GetScale() const;

      virtual void SetMaterial( Material m );
      Material GetMaterial() const;

         
         // sets the rotation of the object
      void SetRotation( GLfloat, Vector );
      void SetRotation( GLfloat, GLfloat, GLfloat,
                        GLfloat );

      GLfloat GetRotationAngle() const;
      Vector GetRotationVector() const;

      void SetPath( Path );

      void SetVisible( bool );
      void SetAnimate( bool );

      virtual void NextFrame();

      virtual void Redraw() = 0;

   protected: // --------------------------------------
      static const float pi = 3.141593;

         // sets up the transform matrix so the draw
         // will occur with the proper transforms 
      void beginTransform();
      void endTransform();

         // translation locations
      Point location;
         
         // scale coefficients
      Scale scale;

         // rotation
      GLfloat angle;
      Vector rotate;

      Material material;

      GLUquadric* quadric;

      bool visible, animate;

      Path path;

      uint frame;
      int cur;
      double dx, dy, dz;

};

#endif /*SHAPE_H_*/
