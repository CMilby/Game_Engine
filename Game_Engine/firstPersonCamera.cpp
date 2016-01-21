//
//  firstPersonCamera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/20/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "firstPersonCamera.h"

#include "renderingEngine.h"
#include "utility.h"

FirstPersonCamera::FirstPersonCamera( const Vector3<float> &position, const Quaternion &rotation ) {
    SetPosition( position );
    SetRotation( rotation );
    
    m_speed = 0.3f;
    m_sensitivity = 2.5f;
    
    m_mouseLocked = false;
    
    SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
}

FirstPersonCamera::~FirstPersonCamera() {
    
}

void FirstPersonCamera::Init() {
    Input::SetCursorPosition( Vector2<int>( Utility::ScreenHalfWidth(), Utility::ScreenHalfHeight() ) );
}

void FirstPersonCamera::Input( float delta ) {
    Camera::Input( delta );
    
    float moveSpeed = 0.3 * m_speed;
    if ( Input::IsKeyDown( Input::KEY_TAB ) ) {
        moveSpeed *= 2.0f;
    }
    
    Matrix4<float> rotation = GetRotation().ToRotationMatrix();
    
    if ( Input::IsKeyDown( Input::KEY_A ) ) {
        Vector3<float> vect = GetRotation().GetLeft( rotation );
        GetTransform()->Move( Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_D ) ) {
        Vector3<float> vect = GetRotation().GetRight( rotation );
        GetTransform()->Move( Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_S ) ) {
        Vector3<float> vect = GetRotation().GetBack( rotation );
        GetTransform()->Move( Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized(), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_W ) ) {
        Vector3<float> vect = GetRotation().GetForward( rotation );
        GetTransform()->Move( Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized(), moveSpeed );
    }
    
    /*if ( Input::IsKeyDown( Input::KEY_SPACE ) ) {
        GetTransform()->Move( GetRotation().GetUp( rotation ), moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_LEFT_SHIFT ) ) {
        GetTransform()->Move( GetRotation().GetDown( rotation ), moveSpeed );
    }*/
    
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
    
    SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
    RenderingEngine::SetMainCamera( *this );
}