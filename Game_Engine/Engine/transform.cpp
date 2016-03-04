//
//  transform.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "transform.h"

#include "config.h"

Matrix4<float> Transform::s_projection = Matrix4<float>().Perspective( Config::GetFieldOfView(), Config::GetAspectRatio(), Config::GetZNear(), Config::GetZFar() );

Transform::Transform( const Vector3<float> &position, const Vector3<float> &scale, const Quaternion &rotation ) {
	m_position = position;
	m_scale = scale;
	m_rotation = rotation;
}

Matrix4<float> Transform::GetModelMatrix() const {
	return Matrix4<float>().Transform( m_position ) * m_rotation.ToRotationMatrix() * Matrix4<float>().InitScale( m_scale );
}

void Transform::Move( const Vector3<float> &direction, float amount ) {
	SetPosition( GetPosition() + ( direction * amount ) );
}

void Transform::Rotate( const Quaternion &quat ) {
	m_rotation = Quaternion( ( m_rotation * quat ).Normalized() );
}

void Transform::Rotate( const Vector3<float> &axis, float angle ) {
	Rotate( Quaternion( axis, angle ) );
}