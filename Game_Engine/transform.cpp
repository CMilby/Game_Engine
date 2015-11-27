//
//  transform.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "transform.h"

Matrix4<float> Transform::s_projection = Matrix4<float>().Perspective( 45.0f, 4.0f / 3.0f, 0.1f, 1024.0f );

void Transform::Rotate( const Vector3<float> &axis, float angle ) {
    Rotate( Quaternion( axis, angle ) );
}

void Transform::Rotate( const Quaternion &quat ) {
    m_rotation = Quaternion( ( m_rotation * quat ).Normalized() );
}