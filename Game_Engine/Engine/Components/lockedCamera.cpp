//
//  lockedCamera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/5/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "lockedCamera.h"

LockedCamera::LockedCamera( const Vector3<float> &pPosition, const Quaternion &pRotation ) {
	SetPosition( pPosition );
	SetRotation( pRotation );
	SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
	
	m_keyUp = Key::KEY_W;
	m_keyDown = Key::KEY_S;
	m_keyForward = Key::KEY_Q;
	m_keyBack = Key::KEY_E;
	m_keyLeft = Key::KEY_A;
	m_keyRight = Key::KEY_D;
}

LockedCamera::~LockedCamera() {
	
}

void LockedCamera::Input() {
	float moveAmt = 0.1f;

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
	
	if ( InputSystem::IsKeyDown( m_keyRight ) ) {
		Move( GetRotation().GetRight( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( m_keyLeft ) ) {
		Move( GetRotation().GetLeft( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( m_keyForward ) ) {
		Move( GetRotation().GetForward( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( m_keyBack ) ) {
		Move( GetRotation().GetBack( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( m_keyUp ) ) {
		Move( GetRotation().GetUp( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( m_keyDown ) ) {
		Move( GetRotation().GetDown( rotation ), moveAmt );
	}
	
	SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
}