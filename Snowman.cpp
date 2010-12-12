// --------------------------------------------------------
// Snowman
//    A class that represents a 3d snowman. It uses 
//    other classes that wrap the glu solids
//
// Carick Wienke

#include "Snowman.h"
#include "Disk.h"

// Constructor
//    creates the snowman. moves the shapes and
//    resizes them so they actually make the snowman
Snowman::Snowman()
{
   body.SetVisible( true );
    
   bottom.SetTranslation( 0, 0, -1.6 );
   bottom.SetScale( 1.2, 1.2, 1.2 );
   bottom.SetVisible( true );

   head.SetTranslation( 0, 0, 1.2 );
   head.SetScale( 0.65, 0.65, 0.65 );
   head.SetVisible( true );

   hatBottom.SetScale( 0.6, 0.6, 0.1 );
   hatBottom.SetTranslation( 0, 0, 1.65 );
   hatBottom.SetMaterial( Material::BLACK_PLASTIC );
   hatBottom.SetVisible( true );

   hatTop.SetScale( 0.47, 0.47, 0.4 );
   hatTop.SetTranslation( 0, 0, 1.75 );
   hatTop.SetMaterial( Material::BLACK_PLASTIC );
   hatTop.SetVisible( true );

   hatLow.SetScale( 0.6, 0.6, 1 );
   hatLow.SetTranslation( 0, 0, 1.65 );
   hatLow.SetMaterial( Material::BLACK_PLASTIC );
   hatLow.SetVisible( true );

   hatMid.SetScale( 0.6, 0.6, 1 );
   hatMid.SetTranslation( 0, 0, 1.75 );
   hatMid.SetMaterial( Material::BLACK_PLASTIC );
   hatMid.SetVisible( true );

   hatHigh.SetScale( 0.47, 0.47, 1 );
   hatHigh.SetTranslation( 0, 0, 2.15 );
   hatHigh.SetMaterial( Material::BLACK_PLASTIC );
   hatHigh.SetVisible( true );
}

   // draw the snowman to the screen
void Snowman::Redraw()
{
   if( visible )
   {
      Shape::beginTransform();

      bottom.Redraw();
      body.Redraw();
      head.Redraw();
      hatBottom.Redraw();
      hatTop.Redraw();
      hatLow.Redraw();
      hatMid.Redraw();
      hatHigh.Redraw();

      Shape::endTransform();
   }
}

   // sets the color of the "snow". the hat color is
   // always black
void Snowman::SetMaterial( Material m )
{
   Shape::SetMaterial( m );

   bottom.SetMaterial( m );
   body.SetMaterial( m );
   head.SetMaterial( m );
}
