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

Player::Player() {
	/*SetPosition( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	SetRotation( Quaternion( Vector3<float>( 1.0f, 0.0f, 0.0f ), 90.0f ) );
	SetScale( Vector3<float>( 0.5f, 0.5f, 0.5f ) );
	
	SetMaxHealth( 200 );
	SetMaxMana( 100 );
	SetMaxStamina( 100 );
	
	SetCurrentHealth( GetMaxHealth() );
	SetCurrentMana( GetMaxMana() );
	SetCurrentStamina( GetCurrentStamina() );
	
	SetMesh( new Mesh( "plane.obj" ) );
	SetMaterial( new Material( new Texture( 1, "tiles", 1, 1 ) ) );
	SetShaderType( ShaderType::SHADER_TILE );
	SetIsVisible( true );*/
}

Player::Player( const Vector2<float> &pPosition ) : NPC( pPosition ) {
	SetMoveSpeed( 2.5f );
	SetSprintSpeed( 2.5f );
	
	SetMaxHealth( 200 );
	SetMaxMana( 100 );
	SetMaxStamina( 100 );
	
	SetCurrentHealth( GetMaxHealth() );
	SetCurrentMana( GetMaxMana() );
	SetCurrentStamina( GetCurrentStamina() );
	
	SetMaterial( new Material( new Texture( "character.png" ) ) );
}

void Player::Input( float pDelta ) {
	Vector2<int> mousePos = InputSystem::GetCursorPosition();
	Vector2<int> screenCenter( Config::GetScreenWidth() / 2, Config::GetScreenHeight() / 2 );
	SetRotation( Quaternion( Vector3<float>( 0.0f, 0.0f, -1.0f ), ToDegree( atan2f( screenCenter.GetY() - mousePos.GetY(), screenCenter.GetX() - mousePos.GetX() ) ) - 90.0f ) );
	
	float moveAmt = GetMoveSpeed() * pDelta;
	// Matrix4<float> rotation = GetRotation().ToRotationMatrix();
	
	if ( InputSystem::IsKeyDown( Config::GetKeySprint()) ) {
		moveAmt *= GetSprintSpeed();
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyUp() ) ) {
		// Vector3<float> direction = GetRotation().GetUp( rotation );
		// Move( Vector3<float>( direction.GetX() * -1, direction.GetY(), direction.GetZ() ), moveAmt );
		Move( Vector3<float>( 0.0f, 1.0f, 0.0f ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyLeft() ) ) {
		// Vector3<float> direction = GetRotation().GetLeft( rotation );
		// Move( Vector3<float>( direction.GetX(), direction.GetY() * -1, direction.GetZ() ), moveAmt );
		Move( Vector3<float>( -1.0f, 0.0f, 0.0f ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyDown() ) ) {
		// Vector3<float> direction = GetRotation().GetDown( rotation );
		// Move( Vector3<float>( direction.GetX() * -1, direction.GetY(), direction.GetZ() ), moveAmt );
		Move( Vector3<float>( 0.0f, -1.0f, 0.0f ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Config::GetKeyRight() ) ) {
		// Vector3<float> direction = GetRotation().GetRight( rotation );
		// Move( Vector3<float>( direction.GetX(), direction.GetY() * -1, direction.GetZ() ), moveAmt );
		Move( Vector3<float>( 1.0f, 0.0f, 0.0f ), moveAmt );
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
		if ( GetRightHandItem()->Use() ) {
			// Draw something?
			
			Logger::LogDebug( "Player - Input", "Use Right Hand" );
		}
	}
	
	if ( InputSystem::IsMouseDown( Config::GetButtonUseLeft() ) ) {
		if ( GetLeftHandItem()->Use() ) {
			// Draw something?
			
			Logger::LogDebug( "Player - Input", "Use Left Hand" );
		}
	}

	CameraSystem::GetMainCamera()->SetPosition( Vector3<float>( GetPosition().GetX(), GetPosition().GetY(), CameraSystem::GetMainCamera()->GetPosition().GetZ() ) );
}




