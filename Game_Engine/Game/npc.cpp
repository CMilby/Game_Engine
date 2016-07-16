//
//  npc.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "npc.h"

#include "handItem.h"
#include "stabbingSwordItem.h"
#include "swingingSword.h"

#include "logger.h"

NPC::NPC() {
	m_leftHand = new HandItem( Vector3<float>( 0.0f, 0.0f, NPC_HEIGHT ), eHand::HAND_LEFT );
	m_rightHand = new SwingingSword( Vector3<float>( 0.0f, 0.0f, NPC_HEIGHT ), eHand::HAND_RIGHT );
	
	AddChild( m_leftHand );
	AddChild( m_rightHand );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}

NPC::NPC( const Vector2<float> &pPosition ) {
	SetPosition( Vector3<float>( pPosition.GetY(), pPosition.GetY(), NPC_HEIGHT ) );
	
	m_leftHand = new HandItem( GetPosition(), eHand::HAND_LEFT );
	m_rightHand = new SwingingSword( GetPosition(), eHand::HAND_RIGHT );
	
	AddChild( m_leftHand );
	AddChild( m_rightHand );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}

NPC::~NPC() {
	if ( m_leftHand != 0 ) {
		delete m_leftHand;
		m_leftHand = 0;
	}
	
	if ( m_rightHand != 0 ) {
		delete m_rightHand;
		m_rightHand = 0;
	}
}

void NPC::Update( float pDelta ) {
	
}






