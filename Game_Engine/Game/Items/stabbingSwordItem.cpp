//
//  stabbingSwordItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "stabbingSwordItem.h"

#include "physicsBody2d.h"
#include "pointCollider.h"

StabbingSwordItem::StabbingSwordItem( eHand pHand ) : HandItem( "StabbingSword", pHand ) {
	m_handLeftOffset = Vector3<float>( -0.45f, 0.8f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.45f, 0.8f, 0.0f );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "Sword.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
	
	SetPosition();
	SetScale( Vector3<float>( 0.9f, 0.9f, 0.9f ) );
	
	SetUseTime( 20 );
	
	SetPhysicsBody( new PhysicsBody2D( new PointCollider( GetPosition().GetXY() ) ) );
	
	m_forward = new Entity( ( ( pHand == HAND_LEFT ) ? m_handLeftOffset : m_handRightOffset ) + Vector3<float>( 0.0f, 1.25f, 0.0f ) );
	AddChild( m_forward );
}

StabbingSwordItem::StabbingSwordItem( const std::string &pItem, eHand pHand ) : HandItem( pItem, pHand ) {
	// Used for subclasses
}

StabbingSwordItem::~StabbingSwordItem() {
	
}