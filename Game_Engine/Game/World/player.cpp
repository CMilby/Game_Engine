//
//  player.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "player.h"

#include "cameraSystem.h"
#include "config.h"
#include "inputSystem.h"
#include "logger.h"

// #include "stabbingSwordItem.h"
// #include "swingingSword.h"

Player::Player() {
	
}

Player::Player( const Vector2<float> &pPosition ) : NPC( pPosition ) {
	SetMoveSpeed( 2.5f );
	SetSprintSpeed( 5.0f );
	
	SetMaxHealth( 200 );
	SetMaxMana( 100 );
	SetMaxStamina( 100 );
	
	SetCurrentHealth( GetMaxHealth() );
	SetCurrentMana( GetMaxMana() );
	SetCurrentStamina( GetCurrentStamina() );
	
	// SetMaterial( new Material( new Texture( "character.png" ) ) );
	
	// SetRightHandItem( new StabbingSwordItem( eHand::HAND_RIGHT ) );
}

Player::~Player() {
	
}

void Player::Collided( Entity *pOther ) {
	// Logger::LogDebug( "Player - Collided", "Collided" );
}

void Player::Input( float pDelta ) {
	Vector2<int> mousePos = InputSystem::GetCursorPosition();
	Vector2<int> screenCenter( Config::GetScreenWidth() / 2, Config::GetScreenHeight() / 2 );
	SetRotation( Quaternion( Vector3<float>( 0.0f, 0.0f, -1.0f ), ToDegree( atan2f( screenCenter.GetY() - mousePos.GetY(), screenCenter.GetX() - mousePos.GetX() ) ) - 90.0f ) );
	
	float moveAmt = GetMoveSpeed();
	
	if ( InputSystem::IsKeyDown( Config::GetKeySprint()) ) {
		moveAmt = GetSprintSpeed();
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyUp() ) ) {
		// SetVelocityY( moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyLeft() ) ) {
		// Move( Vector3<float>( -1.0f, 0.0f, 0.0f ), moveAmt );
		// SetVelocityX( -moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyDown() ) ) {
		// Move( Vector3<float>( 0.0f, -1.0f, 0.0f ), moveAmt );
		// SetVelocityY( -moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyRight() ) ) {
		// Move( Vector3<float>( 1.0f, 0.0f, 0.0f ), moveAmt );
		// SetVelocityX( moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyNext() ) ) {
		// No inventory yet
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyLast() ) ) {
		// No inventory yet
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyInventory() ) ) {
		// No inventory yet
	}
	
	if ( InputSystem::IsMouseDown( Config::GetButtonUseRight() ) ) {
		// if ( GetRightHandItem()->Use() ) {
			Logger::LogInfo( "Player - Input", "Use Right Hand" );
		// }
	}
	
	if ( InputSystem::IsMouseDown( Config::GetButtonUseLeft() ) ) {
		// if ( GetLeftHandItem()->Use() ) {
			Logger::LogInfo( "Player - Input", "Use Left Hand" );
		// }
	}

	CameraSystem::GetMainCamera()->SetPosition( Vector3<float>( GetPosition().GetXY(), CameraSystem::GetMainCamera()->GetPosition().GetZ() ) );
}





