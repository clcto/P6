// --------------------------------------------------------
// Scene.cpp
//    Represents the scene on the screen using the
//    singleton pattern.
//
//    Allows for adding, but not removal, of shapes,
//    and holds the currently selected shape
//
// Carick Wienke
// --------------------------------------------------------

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <sstream>
#include <typeinfo>

#include "Scene.h"
#include "Control.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "Snowman.h"
#include "Articulated.h"

using std::ifstream;
using std::cerr;
using std::istringstream;
using std::ofstream;

Scene* Scene::instance = NULL;

   // -----------------------------------------------------
   // singleton pattern to get the sole scene
Scene* Scene::Instance()
{
   if( !instance )
      instance = new Scene();
   return instance;
}

   // -----------------------------------------------------
   //  Constructor
Scene::Scene() 
{
   isAnimating = true;

   GLfloat dir_pos[4] = { 1, 0, 0, 0 };
   directionalLight = new Light( GL_LIGHT0, dir_pos );
   directionalLight->Disable();

   GLfloat pnt_pos[4] = { 10, 0, 0, 1 };
   pointLight = new Light( GL_LIGHT1, pnt_pos );
}

Scene::~Scene()
{
   while( !shapes.empty() )
   {
      delete shapes.begin()->second;
      shapes.erase( shapes.begin() );
   }

   while( !paths.empty() )
   {
      delete paths.begin()->second;
      paths.erase( paths.begin() );
   }

   delete directionalLight;
   delete pointLight;
}

   // -----------------------------------------------------
   // Redraw
   //    draw the scene again, boxing selected
void Scene::Redraw()
{
   GLfloat ambient[] = { 0.4, 0.4, 0.4, 1 };
   glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   if( isAnimating )
      camera.NextFrame();
   camera.SetUpGLMatrices();
   directionalLight->GLInit();
   pointLight->GLInit();

   map<string,Shape*>::iterator it;
   
   for( it = shapes.begin(); it != shapes.end(); ++it )
   {
      if( it->second )
      {
         if( IsRunning() )
            it->second->NextFrame();
         it->second->Redraw();
      }
   }
}

   // -----------------------------------------------------
   // adds a shape to the scene
void Scene::AddShape( Shape* newShape, string name )
{
   shapes[name] = newShape;
   names.push_back( name );
}

Camera& Scene::GetCamera()
{
   return camera;
}

vector<string> Scene::GetNames()
{
   return names;
}
   // -----------------------------------------------------
   // Shape* GetShape( name )
   //    returns the shape that has the name passed,
   //    or NULL if it does not exist
Shape* Scene::GetShape( string name )
{
   Shape* s = shapes[name];
   if( s )
      return s;
   else
   {
      shapes.erase( name );
      return NULL;
   }
}

Light* Scene::GetDirectionalLight()
{
   return directionalLight;
}

Light* Scene::GetPointLight()
{
   return pointLight;
}

bool Scene::IsRunning()
{
   return isAnimating;
}

void Scene::ReadFile( string filename )
{
   ifstream file( filename.c_str() );

   if( !file.is_open() )
   {
      cerr << "Error opening file '" << filename << "'\n";
      return;
   }
   
   char line[256];
   file.getline( line, 256 );

   while( !file.eof() )
   {
      vector<string> tokens = tokenize( line, "\t " );

      if( tokens.size() > 0 )
      {
         if( tokens[0] == "path" )
            processPath( tokens, file );
         else if( tokens[0] == "tell" )
            processTell( tokens );
         else if( tokens[0] == "define" )
            processDefine( tokens );
      }

      file.getline( line, 256 );
   }


}

void Scene::processDefine( vector<string> tokens )
{
   if( tokens.size() < 3 )
   {
      cerr << "command syntax\n   define <type> <name>\n";
      return;
   }

   Shape *s;

   if( tokens[1] == "snowman" )
      s = new Snowman();
   else if( tokens[1] == "cone" )
      s = new Cone();
   else if( tokens[1] == "articulated" )
      s = new Articulated();

   AddShape( s, tokens[2] );
}

void Scene::processPath( vector<string> tokens,
                         ifstream& file )
{
   if( tokens.size() < 2 )
   {
      cerr << "command syntax\n   path <name>\n";
      return;
   }

   Path* p = new Path();

   char c_line[256];
   file.getline( c_line, 256 );
   string line = c_line;
   trim( line );

   while( !file.eof() && line.compare( "end" ) )
   {
      vector<string> t = tokenize( line, "\t " );

      if( t.size() < 4 )
      {
         cerr << "ignoring path waypoint\n  "
              << line << "\n";
         delete p;
         return;
      }

      float time, x, y, z;

      if( !stringToFloat( t[0], time ) ||
          !stringToFloat( t[1], x )    ||
          !stringToFloat( t[2], y )    ||
          !stringToFloat( t[3], z ) )
      {
         cerr << "ignoring path waypoint\n   "
              << line << "\n";
         delete p;
         return;
      }

      p->push_back( PathNode( time,
                   Point( x, y, z ) ) );

      file.getline( c_line, 256 );
      line = c_line;
      trim( line );
   }

   paths[ tokens[1] ] = p;
}

void Scene::processTell( vector<string> tokens )
{
   if( tokens.size() < 4 || tokens[2] != "animationPath" )
   {
      cerr << "command synatx:\n"
           << "   tell <object_name> animationPath "
           << "<path_name> [time_offset] [time_scale]\n";
      return;
   }
   
   Path *p = paths[ tokens[3] ];
   if( !p )
   {
      cerr << "invalid path: " << tokens[3] << "\n";
      shapes.erase( tokens[3] );
      return;
   }

   Shape* s = 0;
   if( tokens[1] != "camera" )
   { 
      s = shapes[ tokens[1] ];
      if( !s )
      {
         cerr << "invalid shape: " << tokens[1] << "\n";
         shapes.erase( tokens[1] );
         return;
      }
   }

      // get the scale
   float offset, scale;
   
   if(   tokens.size() > 4 && 
         !stringToFloat( tokens[4], offset ) )
   {
      cerr << "invalid time offset: " << tokens[4] << "\n";
      return;
   }
   else if( tokens.size() <= 4 )
      offset = 0;

   if(   tokens.size() > 5 && 
         !stringToFloat( tokens[5], scale ) )
   {
      cerr << "invalid time scale: " << tokens[5] << "\n";
      return;
   }
   else if( tokens.size() <= 5 )
      scale = 1;

   if( s )
      s->SetPath( (*p) * scale + offset );
   else
      camera.SetPath( *p );

}

   // -----------------------------------------------------
   // vector<string> tokenize
   //    splits the input string into tokens
   //
   // input: the string to split
   // delims: the delims to split on
   //
   // returns a vector containing all the tokens
vector<string> tokenize( const string& input,
                         const string& delims )
{
   vector<string> tokens;

   string::size_type tokenStart, tokenEnd;

      // get the start and end of the first token
   tokenStart = input.find_first_not_of( delims, 0 );
   tokenEnd   = input.find_first_of( delims, tokenStart );

   while( !( tokenStart == string::npos && 
             tokenEnd   == string::npos ) )
   {
         // add the token to the vector.
      tokens.push_back(
         input.substr(tokenStart, tokenEnd - tokenStart));

      tokenStart = 
         input.find_first_not_of( delims, tokenEnd );
      tokenEnd = 
         input.find_first_of( delims, tokenStart );
   }

   return tokens;
}

   // -----------------------------------------------------
   // bool stringToFloat( const string&, float& )
   //    converts the string to a float, saves it in the 
   //    out variable, and returns if it was successful
bool stringToFloat( const string& str, float& out )
{
   istringstream iss( str );
   return !( iss >> std::dec >> out ).fail();
}

   // -----------------------------------------------------
   // trims the inputed string, removing preceding and
   // postceding white space.
   //
   // from: codeproject.com/KB/stl/stdstringtrim.aspx
void trim( string& str )
{
   string::size_type pos = str.find_last_not_of( "\t \n" );
   if( pos != string::npos )
   {
      str.erase( pos + 1 );
      pos = str.find_first_not_of( "\t \n" );
      if( pos != string::npos )
         str.erase( 0, pos );
   }
   else
      str.erase( str.begin(), str.end() );
}

void Scene::SetRunning( bool r )
{
   isAnimating = r;
}
