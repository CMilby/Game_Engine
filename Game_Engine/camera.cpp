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
    
    Vector3<float> difference( 0, 0, 0 );
    if ( Input::IsKeyDown( Input::KEY_A ) || Input::IsKeyDown( Input::KEY_LEFT_ARROW ) ) {
        difference += Move( Vector3<float>( -1, 0, 0 ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_D ) || Input::IsKeyDown( Input::KEY_RIGHT_ARROW ) ) {
        difference += Move( Vector3<float>( 1, 0, 0 ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_S ) || Input::IsKeyDown( Input::KEY_DOWN_ARROW ) ) {
        difference += Move( Vector3<float>( 0, 0, 1 ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_W ) || Input::IsKeyDown( Input::KEY_UP_ARROW ) ) {
        difference += Move( Vector3<float>( 0, 0, -1 ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_Q ) ) {
        difference += Move( Vector3<float>( 0, 1, 0 ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_E ) ) {
        difference += Move( Vector3<float>( 0, -1, 0 ), moveSpeed );
    }
    
    m_lookAt += difference;
    m_view = Matrix4<float>().LookAt( m_position, m_lookAt, Vector3<float>( 0, 1, 0 ) );
    
    RenderingEngine::SetMainCamera( *this );
}

Matrix4<float> Camera::GetView() const {
    return m_view;
}

Vector3<float> Camera::GetPosition() const {
    return m_position;
}

Vector3<float> Camera::Move( const Vector3<float> &direction, float amount ) {
    m_position += ( direction * amount );
    return direction * amount;
}