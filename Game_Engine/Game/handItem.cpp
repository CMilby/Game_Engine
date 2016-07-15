//
//  handItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "handItem.h"

HandItem::HandItem( const Vector3<float> &pPosition, eHand pHand ) : Item( "Hand", pHand ) {
	m_handLeftOffset = Vector3<float>( -0.25f, 0.25f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.25f, 0.25f, 0.0f );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "hand.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
	
	SetPosition( pPosition );
	SetScale( Vector3<float>( 0.25f, 0.25f, 0.25f ) );
	
	SetUseTime( 10 );
	
	m_base = new Entity( GetPosition() );
	m_forward = new Entity( ( ( pHand == HAND_LEFT ) ? m_handLeftOffset : m_handRightOffset ) + Vector3<float>( 0.0f, 0.75f, 0.0f ) );
	
	AddChild( m_base );
	AddChild( m_forward );
}

HandItem::HandItem( const std::string &pItem, eHand pHand ) : Item( pItem, pHand ) {
	
}

HandItem::~HandItem() {
	if ( m_forward != 0 ) {
		delete m_forward;
		m_forward = 0;
	}
}

void HandItem::Update( float pDelta ) {
	if ( IsCoolingDown() ) {
		SetCurrentCooldown( GetCurrentCooldown() - 1 );
		if ( GetCurrentCooldown() == 0 ) {
			SetIsCoolingDown( false );
		}
		
		if ( GetTimeSinceUse() <= GetUseTime() ) {
			SetPosition( GetPosition().Lerp( m_forward->GetPosition(), ( ( float ) GetTimeSinceUse() / ( float ) GetUseTime() ) ), false );
			
			SetTimeSinceUse( GetTimeSinceUse() + 1 );
		} else {
			SetPosition( m_base->GetPosition(), false );
		}
	}
}

bool HandItem::Use() {
	if ( IsCoolingDown() ) {
		return false;
	}
	
	Logger::LogInfo( "Item - Use", GetItemName() );
	
	SetTimeSinceUse( 0 );
	SetIsCoolingDown( true );
	SetCurrentCooldown( GetCooldown() );
	return true;
}