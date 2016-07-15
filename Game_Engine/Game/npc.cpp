//
//  npc.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "npc.h"

#include "handItem.h"
#include "swordItem.h"

NPC::NPC() {
	m_leftHand = new HandItem( Vector3<float>( 0.0f, 0.0f, NPC_HEIGHT ), eHand::HAND_LEFT );
	m_rightHand = new SwordItem( Vector3<float>( 0.0f, 0.0f, NPC_HEIGHT ), eHand::HAND_RIGHT );
	
	AddChild( m_leftHand );
	AddChild( m_rightHand );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}

NPC::NPC( const Vector2<float> &pPosition ) {
	SetPosition( Vector3<float>( pPosition.GetY(), pPosition.GetY(), NPC_HEIGHT ) );
	
	m_leftHand = new HandItem( GetPosition(), eHand::HAND_LEFT );
	m_rightHand = new SwordItem( GetPosition(), eHand::HAND_RIGHT );
	
	AddChild( m_leftHand );
	AddChild( m_rightHand );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}

NPC::~NPC() {
	if ( m_leftHand != 0 ) {
		delete m_leftHand;
	}
	
	if ( m_rightHand != 0 ) {
		delete m_rightHand;
	}
}

void NPC::Update( float pDelta ) {
	// Vector2<float> myLeftPos = Math3D::RotatePoint( GetPosition() + s_leftHandOffset, GetPosition(), pAngle )
	
	m_leftHand->SetPosition( GetPosition() );
	m_rightHand->SetPosition( GetPosition() );
	
	m_leftHand->SetRotation( GetRotation() );
	m_rightHand->SetRotation( GetRotation() );
}






