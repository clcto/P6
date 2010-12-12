#include "Path.h"

PathNode::PathNode( double t, Point l )
{
   time = t;
   location[X] = l[X];
   location[Y] = l[Y];
   location[Z] = l[Z];
}

Path Path::operator*( double scale )
{
   Path p( *this );
   Path::iterator it;
   for( it = p.begin(); it < p.end(); ++it )
      (*it).time *= scale;

   return p;
}

Path Path::operator+( double offset )
{
   Path p( *this );
   Path::iterator it;
   for( it = p.begin(); it < p.end(); ++it )
      (*it).time += offset;

   return p;
}
