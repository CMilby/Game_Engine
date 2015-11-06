//
//  camera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "camera.h"

#include <glm/glm.hpp>

#include "input.h"
#include "renderingEngine.h"

void Camera::Init() {
    Input::SetCursorPosition( Vector2<float>( 1024 / 2, 768 / 2 ) );
}

void Camera::Input( float delta ) {
    float moveSpeed = delta * m_speed;
    
    if ( Input::IsKeyDown( Input::KEY_A ) ) {
        Move( m_rotation.GetLeft(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_D ) ) {
        Move( m_rotation.GetRight(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_S ) ) {
        Move( m_rotation.GetBack(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_W ) ) {
        Move( m_rotation.GetForward(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_SPACE ) ) {
        Move( m_rotation.GetUp(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_LEFT_SHIFT ) ) {
        Move( m_rotation.GetDown(), moveSpeed );
    }
    
    /*if ( Input::IsKeyDown( Input::KEY_LEFT_ARROW ) ) {
        Rotate( Vector3<float>( 0, 1, 0 ), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Input::KEY_RIGHT_ARROW ) ) {
        Rotate( Vector3<float>( 0, 1, 0 ), -m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Input::KEY_UP_ARROW ) ) {
        Rotate( m_rotation.GetLeft(), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Input::KEY_DOWN_ARROW ) ) {
        Rotate( m_rotation.GetRight(), m_sensitivity );
    }*/
    
    m_view = m_rotation.ToRotationMatrix() * Matrix4<float>().Transform( m_position * -1 );
    
    RenderingEngine::SetMainCamera( *this );
}

Matrix4<float> Camera::GetView() const {
    return m_view;
}

Vector3<float> Camera::GetPosition() const {
    return m_position;
}

void Camera::Move( const Vector3<float> &direction, float amount ) {
    m_position += ( direction * amount );
}

void Camera::Rotate( const Vector3<float> &axis, float angle ) {
    Rotate( Quaternion( axis, angle ) );
}

void Camera::Rotate( const Quaternion &quaternion ) {
    m_rotation = Quaternion( ( quaternion * m_rotation ).Normalized() );
}















