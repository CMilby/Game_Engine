//
//  freeCamera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/20/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "freeCamera.h"

#include "renderingEngine.h"
#include "utility.h"

FreeCamera::FreeCamera( const Vector3<float> &position, const Quaternion &rotation ) {
    SetPosition( position );
    SetRotation( rotation );
    
    m_speed = 0.5f;
    m_sensitivity = 2.5f;
    
    m_mouseLocked = false;
    
    SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
}

FreeCamera::~FreeCamera() {
	
}

void FreeCamera::Init() {
    m_input->SetCursorPosition( Vector2<int>( Utility::ScreenHalfWidth(), Utility::ScreenHalfHeight() ) );
}

void FreeCamera::Input( float delta ) {
    Camera::Input( delta );
    
    float moveSpeed = 0.5 * m_speed;
	if ( m_input->IsKeyDown( Key::KEY_TAB ) ) {
        moveSpeed *= 2.0f;
    }
    
    Matrix4<float> rotation = GetRotation().ToRotationMatrix();

    if ( m_input->IsKeyDown( Key::KEY_A ) ) {
        GetTransform()->Move( GetRotation().GetLeft( rotation ), moveSpeed );
    }
    
    if ( m_input->IsKeyDown( Key::KEY_D ) ) {
        GetTransform()->Move( GetRotation().GetRight( rotation ), moveSpeed );
    }
    
    if ( m_input->IsKeyDown( Key::KEY_S ) ) {
        GetTransform()->Move( GetRotation().GetBack( rotation ), moveSpeed );
    }
    
    if ( m_input->IsKeyDown( Key::KEY_W ) ) {
        GetTransform()->Move( GetRotation().GetForward( rotation ), moveSpeed );
    }
    
    if ( m_input->IsKeyDown( Key::KEY_SPACE ) ) {
        GetTransform()->Move( GetRotation().GetUp( rotation ), moveSpeed );
    }
    
    if ( m_input->IsKeyDown( Key::KEY_LEFT_SHIFT ) ) {
        GetTransform()->Move( GetRotation().GetDown( rotation ), moveSpeed );
    }
    
	if ( m_input->IsKeyDown( Key::KEY_LEFT_ARROW ) ) {
        GetTransform()->Rotate( Vector3<float>( 0, -1, 0 ), m_sensitivity );
    }
    
	if ( m_input->IsKeyDown( Key::KEY_RIGHT_ARROW ) ) {
        GetTransform()->Rotate( Vector3<float>( 0, 1, 0 ), m_sensitivity );
    }
    
	if ( m_input->IsKeyDown( Key::KEY_UP_ARROW ) ) {
        GetTransform()->Rotate( GetRotation().GetLeft( rotation ), m_sensitivity );
    }
    
	if ( m_input->IsKeyDown( Key::KEY_DOWN_ARROW ) ) {
        GetTransform()->Rotate( GetRotation().GetRight( rotation ), m_sensitivity );
    }
    
    SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
    RenderingEngine::SetMainCamera( *this );
}







