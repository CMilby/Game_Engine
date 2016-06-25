//
//  camera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "camera.h"

Camera::Camera() {
	m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
}

Camera::Camera( const Vector3<float> &position ) {
	SetPosition( position );
	m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
}

Camera::Camera( const Vector3<float> &pPosition, const Quaternion &pRotation ) {
	SetPosition( pPosition );
	SetRotation( pRotation );
	m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
}

Camera::~Camera() {
	
}

void Camera::Input() {
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
		Move( GetRotation().GetRight( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_A ) ) {
		Move( GetRotation().GetLeft( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_W ) ) {
		Move( GetRotation().GetForward( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_S ) ) {
		Move( GetRotation().GetBack( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_SPACE ) ) {
		Move( GetRotation().GetUp( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_LEFT_ALT ) ) {
		Move( GetRotation().GetDown( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_UP_ARROW ) ) {
		Rotate( GetRotation().GetLeft( rotation ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_DOWN_ARROW ) ) {
		Rotate( GetRotation().GetRight( rotation ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_LEFT_ARROW ) ) {
		Rotate( Vector3<float>( 0, -1, 0 ), rotAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_RIGHT_ARROW ) ) {
		Rotate( Vector3<float>( 0, 1, 0 ), rotAmt );
	}
	
	SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
}













