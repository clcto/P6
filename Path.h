#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include "Point.h"

class PathNode
{
public:
   PathNode( double, Point );

   double time;
   Point  location;
};

class Path : public std::vector<PathNode>
{
   public:
      Path operator*( double scale );
      Path operator+( double offset );
};

#endif
