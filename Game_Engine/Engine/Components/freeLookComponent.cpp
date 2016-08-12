//
//  freeLookComponent.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/12/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "freeLookComponent.h"

FreeLookComponent::FreeLookComponent( const Quaternion &pRotation ) : InputComponent( ComponentType::FREE_LOOK_COMPONENT ) {
	// GetParent()->SetRotation( pRotation );
}

FreeLookComponent::~FreeLookComponent() {
	
}

void FreeLookComponent::Input( float pDelta ) {
	float rotAmt = 2.0f;
	Matrix4<float> rotation = GetRotation().ToRotationMatrix();
	
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
}

void FreeLookComponent::Rotate( const Quaternion &pQuat ) {
	GetParent()->SetRotation( Quaternion( ( GetParent()->GetRotation() * pQuat ).Normalized() ) );
}

void FreeLookComponent::Rotate( const Vector3<float> &axis, float angle ) {
	Rotate( Quaternion( axis, angle ) );
}