// --------------------------------------------------------
// GLPoint.h
//    struct representing a point in GL numbers
// --------------------------------------------------------
#ifndef POINT_H_
#define POINT_H_

#define X 0
#define Y 1
#define Z 2

#define I 0
#define J 1
#define K 2

class Point
{
   public:
      Point( float = 0, float = 0, float = 0 );
      float& operator[]( int );
      float  operator[]( int ) const;

   private:
      float values[3];
};

typedef Point Scale;
typedef Point Vector;

#endif
