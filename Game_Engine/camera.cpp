//
//  camera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "camera.h"

#include <glm/glm.hpp>

#include "entity.h"
#include "input.h"
#include "renderingEngine.h"

void Camera::Init() {
    Input::SetCursorPosition( Vector2<float>( 1024 / 2, 768 / 2 ) );
}

void Camera::Input( float delta ) {
    float moveSpeed = 0.5 * m_speed;
    
    Matrix4<float> rotation = GetRotation().ToRotationMatrix();
    
    if ( Input::IsKeyDown( Input::KEY_A ) ) {
        Move( GetRotation().GetLeft( rotation ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_D ) ) {
        Move( GetRotation().GetRight( rotation ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_S ) ) {
        Move( GetRotation().GetBack( rotation ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_W ) ) {
        Move( GetRotation().GetForward( rotation ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_SPACE ) ) {
        Move( GetRotation().GetUp( rotation ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_LEFT_SHIFT ) ) {
        Move( GetRotation().GetDown( rotation ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_LEFT_ARROW ) ) {
        GetTransform()->Rotate( Vector3<float>( 0, -1, 0 ), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Input::KEY_RIGHT_ARROW ) ) {
        GetTransform()->Rotate( Vector3<float>( 0, 1, 0 ), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Input::KEY_UP_ARROW ) ) {
        GetTransform()->Rotate( GetRotation().GetLeft( rotation ), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Input::KEY_DOWN_ARROW ) ) {
        GetTransform()->Rotate( GetRotation().GetRight( rotation ), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Input::KEY_0 ) ) {
        Input::SetDrawMode( 0 );
    }
    
    if ( Input::IsKeyDown( Input::KEY_1 ) ) {
        Input::SetDrawMode( 1 );
    }
    
    m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
    
    RenderingEngine::SetMainCamera( *this );
}

void Camera::Move( const Vector3<float> &direction, float amount ) {
    SetPosition( GetPosition() + ( direction * amount ) );
}















