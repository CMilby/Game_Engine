//
//  transform.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "transform.h"

#include "config.h"

Matrix4<float> Transform::s_projection = Matrix4<float>().Perspective( Config::GetFieldOfView(), Config::GetAspectRatio(), Config::GetZNear(), Config::GetZFar() );

void Transform::Rotate( const Vector3<float> &axis, float angle ) {
    Rotate( Quaternion( axis, angle ) );
}

void Transform::Rotate( const Quaternion &quat ) {
    m_rotation = Quaternion( ( m_rotation * quat ).Normalized() );
}

void Transform::SetProjection( float fov, float aspectRatio, float zNear, float zFar ) {
    s_projection = Matrix4<float>().Perspective( fov, aspectRatio, zNear, zFar );
}