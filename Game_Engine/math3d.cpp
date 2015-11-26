//
//  math3d.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "math3d.h"

/*Vector3<float> Rotate( const Vector3<float> &vect, const Quaternion &quat ) {
    Quaternion w = quat * vect * quat.Conjugate();
    return Vector3<float>( w.GetX(), w.GetY(), w.GetZ() );
}

Vector3<float> Rotate( const Vector3<float> &vect, const Vector3<float> &axis, float angle ) {
    return Rotate( vect, Quaternion( axis, angle ) );
}*/