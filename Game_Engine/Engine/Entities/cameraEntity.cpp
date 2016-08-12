//
//  camera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "cameraEntity.h"

#include "drawModeComponent.h"
#include "../../freeLookComponent.h"
#include "freeMoveComponent.h"

CameraEntity::CameraEntity() : Entity( EntityType::ENTITY_CAMERA ) {
	AddComponent( new FreeLookComponent() );
	AddComponent( new FreeMoveComponent() );
	AddComponent( new DrawModeComponent() );
}

CameraEntity::CameraEntity( const Vector3<float> &pPosition ) : Entity( EntityType::ENTITY_CAMERA ) {
	AddComponent( new FreeLookComponent() );
	AddComponent( new FreeMoveComponent( pPosition ) );
	AddComponent( new DrawModeComponent() );
	
	SetPosition( pPosition );
}

CameraEntity::CameraEntity( const Vector3<float> &pPosition, const Quaternion &pRotation ) : Entity( EntityType::ENTITY_CAMERA ) {
	AddComponent( new FreeLookComponent( pRotation ) );
	AddComponent( new FreeMoveComponent( pPosition ) );
	AddComponent( new DrawModeComponent() );
	
	SetPosition( pPosition );
	SetRotation( pRotation );
}

CameraEntity::~CameraEntity() {
	
}

void CameraEntity::Update( float pDelta ) {
	SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
}

/*void CameraEntity::Input( float pDelta ) {
	float moveAmt = 0.3f;
	float rotAmt = 2.0f;
	Matrix4<float> rotation = GetRotation().ToRotationMatrix();
	
	if ( InputSystem::IsKeyDown( Key::KEY_TAB ) ) {
		moveAmt *= 3.0f;
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_O ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_SHADED );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_P ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_WIREFRAME );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_D ) ) {
		// Move( GetRotation().GetRight( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_A ) ) {
		// Move( GetRotation().GetLeft( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_W ) ) {
		// Move( GetRotation().GetForward( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_S ) ) {
		// Move( GetRotation().GetBack( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_SPACE ) ) {
		// Move( GetRotation().GetUp( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_LEFT_ALT ) ) {
		// Move( GetRotation().GetDown( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_UP_ARROW ) ) {
		// Rotate( GetRotation().GetLeft( rotation ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_DOWN_ARROW ) ) {
		// Rotate( GetRotation().GetRight( rotation ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_LEFT_ARROW ) ) {
		// Rotate( Vector3<float>( 0, -1, 0 ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_RIGHT_ARROW ) ) {
		// Rotate( Vector3<float>( 0, 1, 0 ), rotAmt );
	}
	
	SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
}

/*
CameraEntity::CameraEntity() : Entity( EntityType::ENTITY_CAMERA ) {
	m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
}

CameraEntity::CameraEntity( const Vector3<float> &pPosition ) : Entity( EntityType::ENTITY_CAMERA ) {
	SetPosition( pPosition );
	
	m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
}

CameraEntity::CameraEntity( const Vector3<float> &pPosition, const Quaternion &pRotation ) : Entity( EntityType::ENTITY_CAMERA ) {
	SetPosition( pPosition );
	SetRotation( pRotation );
	
	m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
}

CameraEntity::~CameraEntity() {
	
}

void CameraEntity::Input( float pDelta ) {
	float moveAmt = 0.3f;
	float rotAmt = 2.0f;
	Matrix4<float> rotation = GetRotation().ToRotationMatrix();
	
	if ( InputSystem::IsKeyDown( Key::KEY_TAB ) ) {
		moveAmt *= 3.0f;
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_O ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_SHADED );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_P ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_WIREFRAME );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_D ) ) {
		m_transform.Move( GetRotation().GetRight( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_A ) ) {
		m_transform.Move( GetRotation().GetLeft( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_W ) ) {
		m_transform.Move( GetRotation().GetForward( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_S ) ) {
		m_transform.Move( GetRotation().GetBack( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_SPACE ) ) {
		m_transform.Move( GetRotation().GetUp( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_LEFT_ALT ) ) {
		m_transform.Move( GetRotation().GetDown( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_UP_ARROW ) ) {
		m_transform.Rotate( GetRotation().GetLeft( rotation ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_DOWN_ARROW ) ) {
		m_transform.Rotate( GetRotation().GetRight( rotation ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_LEFT_ARROW ) ) {
		m_transform.Rotate( Vector3<float>( 0, -1, 0 ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_RIGHT_ARROW ) ) {
		m_transform.Rotate( Vector3<float>( 0, 1, 0 ), rotAmt );
	}
	
	m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
	SetView( m_view );
}
*/
