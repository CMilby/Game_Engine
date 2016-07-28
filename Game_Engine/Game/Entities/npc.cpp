//
//  npc.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "npc.h"

#include "circleCollider.h"
#include "handItem.h"
#include "logger.h"
#include "physicsBody2d.h"

NPC::NPC() : RenderableEntity( EntityType::ENTITY_NPC ) {
	m_leftHand = new HandItem( eHand::HAND_LEFT );
	m_rightHand = new HandItem( eHand::HAND_RIGHT );
	
	AddChild( m_leftHand );
	AddChild( m_rightHand );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}

NPC::NPC( const Vector2<float> &pPosition ) : RenderableEntity( EntityType::ENTITY_NPC ) {
	SetPosition( Vector3<float>( pPosition.GetX(), pPosition.GetY(), NPC_HEIGHT ) );
	
	m_leftHand = new HandItem( eHand::HAND_LEFT );
	m_rightHand = new HandItem( eHand::HAND_RIGHT );
	
	AddChild( m_leftHand );
	AddChild( m_rightHand );
	
	SetPhysicsBody( new PhysicsBody2D( new CircleCollider( GetPosition().GetXY(), 0.875f ) ) );
	
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

void NPC::Collided( Entity *pOther ) {
	Logger::LogDebug( "NPC - Collided", "Collided" );
}

void NPC::Update( float pDelta ) {
	RenderableEntity::Update( pDelta );
}

void NPC::SetRightHandItem( Item *pItem ) {
	RemoveChild( m_rightHand );
	m_rightHand = pItem;
	AddChild( m_rightHand );
}

void NPC::SetLeftHandItem( Item *pItem ) {
	RemoveChild( m_leftHand );
	m_leftHand = pItem;
	AddChild( m_leftHand );
}





