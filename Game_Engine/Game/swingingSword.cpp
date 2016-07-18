//
//  swingingSword.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "swingingSword.h"

SwingingSword::SwingingSword( eHand pHand ) : Item( "SwingingSword", pHand ){
	m_handLeftOffset = Vector3<float>( -0.45f, 0.5f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.45f, 0.5f, 0.0f );

	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "Sword.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
	
	SetPosition();
	SetScale( Vector3<float>( 0.9f, 0.9f, 0.9f ) );
	
	SetCooldown( 30 );
	SetUseTime( 15 );
	
	m_swingAngle = 125.0f;
}

SwingingSword::SwingingSword( const std::string &pItem, eHand pHand ) : Item( "SwingingSword", pHand ) {
	// Used for subclasses
}

SwingingSword::~SwingingSword() {
	
}

void SwingingSword::Update( float pDelta ) {
	if ( IsCoolingDown() ) {
		SetCurrentCooldown( GetCurrentCooldown() - 1 );
		if ( GetCurrentCooldown() == 0 ) {
			SetIsCoolingDown( false );
		}
		
		if ( GetTimeSinceUse() == 0 ) {
			SetPosition( Vector3<float>( 1.5f, 0.5f, GetPosition().GetZ() ) );
		}
		
		if ( GetTimeSinceUse() <= GetUseTime() ) {
			SetPosition( Vector3<float>( 1.5f, 0.5f, GetPosition().GetZ() ).RotateZ( ( ( float ) GetTimeSinceUse() / ( float ) GetUseTime() ) * m_swingAngle ) );
			
			Vector2<float> swordPos = GetPosition().GetXY() + GetParent()->GetPosition().GetXY();
			Vector2<float> playerPos = GetParent()->GetPosition().GetXY();
			SetRotation( Quaternion( Vector3<float>( 0.0f, 0.0f, 1.0f ), ToDegree( atan2f( playerPos.GetY() - swordPos.GetY(), playerPos.GetX() - swordPos.GetX() ) ) - 270 ) );
			
			SetTimeSinceUse( GetTimeSinceUse() + 1 );
		} else {
			SetPosition();
			SetRotation( Quaternion( 0.0f, 0.0f, 0.0f, 1.0f ) );
		}
	}
}

bool SwingingSword::Use() {
	if ( IsCoolingDown() ) {
		return false;
	}
	
	Logger::LogInfo( "Item - Use", GetItemName() );
	
	SetTimeSinceUse( 0 );
	SetIsCoolingDown( true );
	SetCurrentCooldown( GetCooldown() );
	return true;
}