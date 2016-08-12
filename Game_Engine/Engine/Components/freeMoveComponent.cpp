//
//  freeMoveComponent.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/12/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "freeMoveComponent.h"

FreeMoveComponent::FreeMoveComponent( const Vector3<float> &pPosition ) : InputComponent( ComponentType::FREE_MOVE_COMPONENT ) {
	// GetParent()->SetPosition( pPosition );
}

FreeMoveComponent::~FreeMoveComponent() {
	
}

void FreeMoveComponent::Input( float pDelta )  {
	float moveAmt = 0.3f;
	Matrix4<float> rotation = GetParent()->GetRotation().ToRotationMatrix();
	
	if ( InputSystem::IsKeyDown( Key::KEY_TAB ) ) {
		moveAmt *= 3.0f;
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_D ) ) {
		Move( GetParent()->GetRotation().GetRight( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_A ) ) {
		Move( GetParent()->GetRotation().GetLeft( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_W ) ) {
		Move( GetParent()->GetRotation().GetForward( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_S ) ) {
		Move( GetParent()->GetRotation().GetBack( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_SPACE ) ) {
		Move( GetParent()->GetRotation().GetUp( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_LEFT_ALT ) ) {
		Move( GetParent()->GetRotation().GetDown( rotation ), moveAmt );
	}
}

void FreeMoveComponent::Move( const Vector3<float> &pDirection, float pAmount ) {
	GetParent()->SetPosition( GetParent()->GetPosition() + ( pDirection * pAmount ) );
}



