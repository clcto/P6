// --------------------------------------------------------
// Control.cpp
//    class code for the control window
//
//    allows for the user to select and modify the 
//    graphics that are drawn in the "scene"
// 
// Author: Carick Wienke
// --------------------------------------------------------
//
#include "Control.h"
#include "Scene.h"
#include <iostream>

using namespace std;

Control* Control::instance = NULL;

   // -----------------------------------------------------
   // Control* Instance()
   //    returns the sole instance of the class
Control* Control::Instance()
{
   if( !instance )
      instance = new Control();

   return instance;
}

   // -----------------------------------------------------
   // void Initialize( string, int )
   //    initializes the glui windows, creating all the
   //    controls and the setting their values
void Control::Initialize( string name, int windowID )
{
      // create the main window
   glui = GLUI_Master.create_glui( name.c_str() );

      // link it to the graphics window
   if( windowID >= 0 )
      glui->set_main_gfx_window( windowID );
   
   createCamera();
   createShapeControls();

   glui->add_button( "Pause", Modified_Pause, 
      modified_cb );
   glui->add_button( "Run", Modified_Run, 
      modified_cb );

   Control::LoadValues();
}

void Control::LoadValues()
{
   Scene* s = Scene::Instance();

   cam_radius->set_float_val(
      s->GetCamera().GetRadius() ); 
   cam_heading->set_float_val(
      s->GetCamera().GetHeading() ); 
   cam_elevation->set_float_val(
      s->GetCamera().GetElevation() ); 

}

   // -----------------------------------------------------
   // void modified_cb( int control )
   //    callback for the controls changing
   //
   // control: which control caused it?
void Control::modified_cb( int control )
{
   Instance()->modified( control );
}

   // -----------------------------------------------------
   // void modified( int control )
   //    callback for the controls changing
   //
   // control: which control caused it?
void Control::modified( int control )
{
   Camera &cam = Scene::Instance()->GetCamera();
      
      // used to convert the 3 spinners into
      // one struct for passing to the cam

   Scene* s;
   vector<string> names;
   switch( control )
   {
      case Modified_Camera:
         cam.SetEyeSpherical(
            cam_elevation->get_float_val(),
            cam_heading->get_float_val(),
            cam_radius->get_float_val() );
         break;
      case Modified_ShapePause:
         s = Scene::Instance();
         names = s->GetNames();
         s->GetShape( 
            names[ selectionControl->get_int_val() ] 
            )->SetAnimate( false );
         break;
      case Modified_ShapeRun:
         s = Scene::Instance();
         names = s->GetNames();
         s->GetShape( 
            names[ selectionControl->get_int_val() ] 
            )->SetAnimate( true );
         break;
      case Modified_Pause:
         Scene::Instance()->SetRunning( false );
         break;
      case Modified_Run:
         Scene::Instance()->SetRunning( true );
         break;
   }

      //
      // refresh please
   glutPostRedisplay();
}

void Control::createCamera()
{
   GLUI_Panel* panel = glui->add_panel( "Camera Location" );

   cam_radius = glui->add_spinner_to_panel( panel, "Radius",
      GLUI_SPINNER_FLOAT, NULL, 
      Modified_Camera, modified_cb );
   cam_radius->set_float_limits( 10, 200 );
   cam_radius->set_speed( .1 );

   cam_heading = glui->add_spinner_to_panel( panel, "Heading", 
      GLUI_SPINNER_FLOAT, NULL, 
      Modified_Camera, modified_cb );
   cam_heading->set_float_limits( 0, 360 );
   cam_heading->set_speed( .2 );

   cam_elevation = glui->add_spinner_to_panel( panel, "Elevation",
      GLUI_SPINNER_FLOAT, NULL,
      Modified_Camera, modified_cb );
   cam_elevation->set_float_limits( -80, 80 );
   cam_elevation->set_speed( .2 );
}

void Control::createShapeControls()
{
   GLUI_Panel *panel;
   panel = glui->add_panel( "Animation Controls" );
   
   selectionControl = glui->add_listbox_to_panel(
      panel, "Shape", NULL, Modified_Selection,
      modified_cb );   
   
   vector<string> names = Scene::Instance()->GetNames();

   for( uint i = 0; i < names.size(); ++i )
      selectionControl->add_item( i, names[i].c_str() );

   glui->add_button_to_panel( panel, "Pause",
      Modified_ShapePause, modified_cb );
   glui->add_button_to_panel( panel, "Run",
      Modified_ShapeRun, modified_cb );
}
