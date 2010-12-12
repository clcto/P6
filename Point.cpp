#include "Point.h"
#include <assert.h>

Point::Point( float x, float y, float z )
{
   values[X] = x;
   values[Y] = y;
   values[Z] = z;
}

float& Point::operator[]( int index )
{
   assert( index >= X && index <= Z );
   return values[ index ];
}

float Point::operator[]( int index ) const
{
   assert( index >= X && index <= Z );
   return values[ index ];
}
