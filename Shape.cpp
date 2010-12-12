// --------------------------------------------------------
// Shape.cpp:
//    abstract class that represents a shape, holding
//    code that is common to all 'shapes'
//
//  Carick Wienke <cdj26@unh.edu>
//
//  Derived from Demo0 by RDB
// --------------------------------------------------------

#include "Shape.h"
#include <iostream>

// ======== Public Methods/Constructors ===================

   // -----------------------------------------------------
   // Shape::Shape
   // create a shape at its default size/scale/roation
Shape::Shape()
{
   location[X] = location[Y] = location[Z] = 0;

   scale[X] = scale[Y] = scale[Z] = 1;

   rotate[X] = 0;
   rotate[Y] = 0;
   rotate[Z] = 1;

   angle = 0;

   material = Material::BRASS;

   quadric = gluNewQuadric();

   visible = false;
   animate = true;

   frame = 0;
   cur = -1;
   dx = dy = dz = 0;
}

   // -----------------------------------------------------
   // Shape::~Shape
Shape::~Shape()
{
   gluDeleteQuadric( quadric );
}

   // -----------------------------------------------------
   // sets the translation 
void Shape::SetTranslation( GLfloat tx, GLfloat ty,
                            GLfloat tz )
{
   location[X] = tx;
   location[Y] = ty;
   location[Z] = tz;
}

   // -----------------------------------------------------
   // sets the scale
void Shape::SetScale( GLfloat xs, GLfloat ys,
                      GLfloat zs )
{
   scale[X] = xs;
   scale[Y] = ys;
   scale[Z] = zs;
}


void Shape::SetMaterial( Material m )
{
   material = m;
}

void Shape::SetPath( Path p )
{
   path = p;
}
   
   // -----------------------------------------------------
   // set the matrix for the transform
void Shape::beginTransform()
{
   glMatrixMode( GL_MODELVIEW );
   glPushMatrix();
   glTranslated( location[X], location[Y], location[Z] );
   glRotatef( angle, rotate[X], rotate[Y], rotate[Z] );
   glScaled( scale[X], scale[Y], scale[Z] );
}

   // gets the matrix off the stack so it goes back
   // to how it was before drawing the shape
void Shape::endTransform()
{
   glMatrixMode( GL_MODELVIEW );
   glPopMatrix();
}

void Shape::SetRotation( GLfloat a, Vector r )
{
   angle = a;
   rotate = r;
}

void Shape::SetRotation( GLfloat a, GLfloat i, GLfloat j,
                         GLfloat k )
{
   Vector v (i,j,k);
   SetRotation( a, v );
}

   // Accessors ===========================================
Point Shape::GetTranslation() const
{
   return location;
}

Scale Shape::GetScale() const
{
   return scale;
}

GLfloat Shape::GetRotationAngle() const
{
   return angle;
}

Vector Shape::GetRotationVector() const
{
   return rotate;
}

Material Shape::GetMaterial() const
{
   return material;
}

void Shape::NextFrame()
{

   if( path.size() < 1 )
      return;

   if( animate )
   {
      double frame_time = ++frame * 0.04;
      if( frame_time < path[ cur+1 ].time )
      {
         if( cur >= 0 )
            TranslateBy( dx, dy, dz );
      }
      else
      {
         visible = true;
         ++cur;
         if( cur == (int)path.size() - 1 )
         {
            animate = false;
            cur = -1;
         }
         else
         {
            SetTranslation( path[ cur ].location[X],
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
   }
}

void Shape::TranslateBy( float dx, float dy, float dz )
{
   location[X] += dx;
   location[Y] += dy;
   location[Z] += dz;
}

void Shape::SetVisible( bool v )
{
   visible = v;
}

void Shape::SetAnimate( bool a )
{
   animate = a;
}
