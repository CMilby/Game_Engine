//
//  math3d.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "math3d.h"

Vector3<float> Rotate( const Vector3<float> &vect, const Quaternion &quat ) {
    Quaternion w = quat * vect * quat.Conjugate();
    return Vector3<float>( w.GetX(), w.GetY(), w.GetZ() );
}

Vector3<float> Rotate( const Vector3<float> &vect, float angle, const Vector3<float> &axis ) {
    return Rotate( vect, Quaternion( axis, angle ) );
}

float Random::InRangeF( float min, float max ) {
    float random = ( ( float ) rand() ) / ( float ) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}