//
//  npc.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "npc.h"

#include "handItem.h"

Vector3<float> NPC::s_leftHandOffset = Vector3<float>( -0.25f, 0.25f, 0.0f );
Vector3<float> NPC::s_rightHandOffset = Vector3<float>( 0.25f, 0.25f, 0.0f );

NPC::NPC() {
	m_leftHand = new HandItem( Vector3<float>( 0.0f, 0.0f, NPC_HEIGHT ) );
	m_rightHand = new HandItem( Vector3<float>( 0.0f, 0.0f, NPC_HEIGHT ) );
	
	AddChild( m_leftHand );
	AddChild( m_rightHand );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}

NPC::NPC( const Vector2<float> &pPosition ) {
	SetPosition( Vector3<float>( pPosition.GetY(), pPosition.GetY(), NPC_HEIGHT ) );
	
	m_leftHand = new HandItem( GetPosition() + s_leftHandOffset );
	m_rightHand = new HandItem( GetPosition() + s_rightHandOffset );
	
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
	
	m_leftHand->SetPosition( GetPosition() + s_leftHandOffset );
	m_rightHand->SetPosition( GetPosition() + s_rightHandOffset );
}






