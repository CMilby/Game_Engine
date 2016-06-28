//
//  player.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "player.h"

#include "inputSystem.h"

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

Player::Player( const Vector2<float> &pPosition ) {
	SetPosition( Vector3<float>( pPosition.GetX(), pPosition.GetY(), 0.0f ) );
	SetRotation( Quaternion( Vector3<float>( 1.0f, 0.0f, 0.0f ), 90.0f ) );
	SetScale( Vector3<float>( 0.5f, 0.5f, 0.5f ) );
	
	/*SetMaxHealth( 200 );
	SetMaxMana( 100 );
	SetMaxStamina( 100 );
	
	SetCurrentHealth( GetMaxHealth() );
	SetCurrentMana( GetMaxMana() );
	SetCurrentStamina( GetCurrentStamina() );*/
	
	SetMesh( new Mesh( "plane.obj" ) );
	SetMaterial( new Material( new Texture( "plain.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}

/*void Player::Init() {
	
}*/

void Player::Input( float pDelta ) {
	float moveAmt = 0.1f;
	Matrix4<float> rotation = GetRotation().ToRotationMatrix();
	
	if ( InputSystem::IsKeyDown( Key::KEY_TAB ) ) {
		moveAmt *= 3.0f;
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_W ) ) {
		Move( GetRotation().GetUp( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_A ) ) {
		Move( GetRotation().GetLeft( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_S ) ) {
		Move( GetRotation().GetDown( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_D ) ) {
		Move( GetRotation().GetRight( rotation ), moveAmt );
	}
	
	if ( InputSystem::IsMouseDown( MouseButton::MOUSE_BUTTON_LEFT ) ) {
		// GetRightHandItem()->Use();
	}
	
	if ( InputSystem::IsMouseDown( MouseButton::MOUSE_BUTTON_RIGHT ) ) {
		// GetLeftHandItem()->Use();
	}
}

void Player::Update( float pDelta ) {
	
}