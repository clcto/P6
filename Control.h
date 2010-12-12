//---------------------------------------------------------
// Control.h
//    class definition for the control window
//
// Author: Carick Wienke
// --------------------------------------------------------

#ifndef CONTROL_H_
#define CONTROL_H_

#include <string>
#include <GL/glut.h>
#include <GL/glui.h>

#include "Camera.h"

using std::string;

class Control
{
   public:
         // singleton pattern method to get instance
      static Control* Instance();
      
         // sets up the control box with the name
         // given and the windowID of the main
         // graphics window
      void Initialize( string name, int windowID );

      void LoadValues();

      void SelectionChanged( const uint& );

   protected:
         // singleton instance
      static Control* instance;

         // callback function for content changing
      static void modified_cb( int );
      
         // callback instance method
      void modified( int );
      
      void createCamera();
      void createDirectional();
      void createPoint();
      void createColor();
      void createShapeControls();
      
         // enum determining which value changed
      enum ModifiedControl
      {
         Modified_Camera,
         Modified_ShapePause,
         Modified_ShapeRun,
         Modified_Pause,
         Modified_Run,
         Modified_Selection
      };

         // Controls
      GLUI *glui;

         // Camera properties, spherical
      GLUI_Spinner *cam_radius,
                   *cam_heading,
                   *cam_elevation;

      GLUI_Listbox *selectionControl;
};

#endif // CONTROL_H_
