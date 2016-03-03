//
//  thirdPersonCamera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/20/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "thirdPersonCamera.h"

#include "config.h"
#include "shader.h"
#include "renderingEngine.h"
#include "utility.h"

ThirdPersonCamera::ThirdPersonCamera( const Vector3<float> &position, const Quaternion &rotation, RenderableEntity *character ) {
    m_offset = Vector3<float>( 0, 2, 9 );
    
    SetPosition( position + m_offset );
    SetRotation( rotation );
    
    m_character = character;
    m_character->SetPosition( position );
    m_character->GetTransform()->Rotate( Vector3<float>( 0.0f, 1.0f, 0.0f ), 180.0f );
    
    m_moveSpeed = 0.5f;
    m_sensitivity = 2.5f;
}

ThirdPersonCamera::~ThirdPersonCamera() {
    if ( m_character ) delete m_character;
}

void ThirdPersonCamera::Init() {
    Input::SetCursorPosition( Vector2<int>( Utility::ScreenHalfWidth(), Utility::ScreenHalfHeight() ) );
}

void ThirdPersonCamera::Input( float delta ) {
    Camera::Input( delta );
    
    float moveSpeed = 0.3 * m_moveSpeed;
    if ( Input::IsKeyDown( Input::KEY_TAB ) ) {
        moveSpeed *= 2.0f;
    }
    
    Matrix4<float> rotation = GetRotation().ToRotationMatrix();
    
    if ( Input::IsKeyDown( Input::KEY_A ) ) {
        Vector3<float> vect = GetRotation().GetLeft( rotation );
        vect = Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized();
        GetTransform()->Move( vect, moveSpeed );
        m_character->GetTransform()->Move( vect, moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_D ) ) {
        Vector3<float> vect = GetRotation().GetRight( rotation );
        vect = Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized();
        GetTransform()->Move( vect, moveSpeed );
        m_character->GetTransform()->Move( vect, moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_S ) ) {
        Vector3<float> vect = GetRotation().GetBack( rotation );
        vect = Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized();
        GetTransform()->Move( vect, moveSpeed );
        m_character->GetTransform()->Move( vect, moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_W ) ) {
        Vector3<float> vect = GetRotation().GetForward( rotation );
        vect = Vector3<float>( vect.GetX(), 0.0, vect.GetZ() ).Normalized();
        GetTransform()->Move( vect, moveSpeed );
        m_character->GetTransform()->Move( vect, moveSpeed );
    }
    
    if ( Input::IsKeyDown( Input::KEY_LEFT_ARROW ) ) {
        
    }
    
    if ( Input::IsKeyDown( Input::KEY_RIGHT_ARROW ) ) {
        
    }
    
    if ( Input::IsKeyDown( Input::KEY_UP_ARROW ) ) {
        
    }
    
    if ( Input::IsKeyDown( Input::KEY_DOWN_ARROW ) ) {
        
    }
    
    SetView( Matrix4<float>().LookAt( GetPosition(), m_character->GetTransform()->GetPosition(), Vector3<float>( 0.0f, 1.0f, 0.0f ) ) );
    RenderingEngine::SetMainCamera( *this );
}

void ThirdPersonCamera::Render( const std::vector<Shader*> &shaders, const Camera &camera ) {
    m_character->Render( shaders, camera );
}






