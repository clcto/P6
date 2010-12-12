#include "Articulated.h"

Articulated::Articulated(int depth)
{
   root = true;
   makeArticulated( depth );
}

Articulated::Articulated( int depth, bool r )
{
   root = r;
   makeArticulated( depth );
}

void Articulated::makeArticulated( int d )
{
   depth = d;
   if( depth > 0 )
   {
      art = new Articulated( depth - 1, false );
      art->SetVisible(true);
      art->SetTranslation( 0, 0, 1.8 );
      art->SetScale( 0.8, 0.8, 0.8 );
   }

   cyl.SetVisible(true);
   cyl.SetScale( 1, 1, 2 );
   cyl.SetMaterial( Material::MATTE_RED );
}

void Articulated::Redraw()
{
   if( visible )
   {
      Shape::beginTransform();

      cyl.Redraw();
      if( art )
         art->Redraw();

      Shape::endTransform();
   }
}

void Articulated::NextFrame()
{
   static float angle = 0;

   angle += depth*0.2;
   if( angle == 360 )
      angle = 0;

   SetRotation( angle, 0.3, 0.3, 1 );     

   if( art )
      art->NextFrame();

   if( root )
      Shape::NextFrame();
}
