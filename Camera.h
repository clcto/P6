#ifndef CAMERA_H_
#define CAMERA_H_

#include "Point.h"
#include "Path.h"
#include <GL/glut.h>

class Camera
{
   public:
      
      Camera();

      void SetEyeSpherical( float t, float p,
                            float r = 1 );
      void SetEyeRectangular( double, double, double );
      void SetDeltaEyeRectangular(
               double, double, double );

      void SetUpGLMatrices() const;

      float GetElevation();
      float GetHeading();
      float GetRadius();

      void NextFrame();

      void SetPath( Path );

   private:
      Point eye;

      Point center;
      Vector up;

      GLdouble pNear, pFar;

      GLdouble fov, aspect;

      Path path;
};

#endif
