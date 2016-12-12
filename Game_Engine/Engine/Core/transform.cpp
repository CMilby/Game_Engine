//
//  transform.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "transform.h"

#include "config.h"

Matrix4f Transform::s_projection = Matrix4<float>().Perspective( Config::GetFOV(), Config::GetAspectRatio(), Config::GetZNear(), Config::GetZFar() );
Matrix4f Transform::s_ortho = Matrix4<float>().Ortho( 0.0f, Config::GetScreenWidth(), Config::GetScreenHeight(), 0.0f, Config::GetZNear(), Config::GetZFar() );

Matrix4f Transform::GetModelMatrix() const {
    return Matrix4f().Transform( m_position ) * m_rotation.ToRotationMatrix() * Matrix4f().InitScale( m_scale );
}

void Transform::Move( const Vector3f &p_direction, float p_amount ) {
    SetPosition( GetPosition() + ( p_direction * p_amount ) );
}

void Transform::Rotate( const Quaternion &p_quat ) {
    m_rotation = Quaternion( ( m_rotation * p_quat ).Normalized() );
}

void Transform::Rotate( const Vector3f &p_axis, float p_angle ) {
    Rotate( Quaternion( p_axis, p_angle ) );
}
