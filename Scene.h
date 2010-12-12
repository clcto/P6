// --------------------------------------------------------
// Scene.h
//    represents a singleton scene on the screen.
//    allows for selecting object, and their interaction
//    with the control
//
// Carick Wienke
// --------------------------------------------------------
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "Shape.h"
#include "Camera.h"
#include "Light.h"
#include "Path.h"

using std::vector;
using std::string;
using std::map;
using std::ifstream;

class Scene
{
   public:
      static Scene* Instance();
      void Redraw();
      void AddShape( Shape* newShape, string name );
      Camera& GetCamera();
      Shape* GetShape( string name );
      void ReadFile( string );
      bool IsRunning();

      Light* GetDirectionalLight();
      Light* GetPointLight();

      ~Scene();

   private:
      void processPath( vector<string>, ifstream& );
      void processTell( vector<string> );
      void processDefine( vector<string> );

      Scene();

      Camera camera;

      static Scene* instance;

      Light* directionalLight;
      Light* pointLight;

      bool isAnimating;

      map<string, Path*> paths;
      map<string, Shape*> shapes;
};

vector<string> tokenize( const string& input,
                         const string& delims );

bool stringToFloat( const string&, float& );

void trim( string& );

#endif // SCENE_H_
