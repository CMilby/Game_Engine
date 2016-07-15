//
//  stabbingSwordItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "stabbingSwordItem.h"

StabbingSwordItem::StabbingSwordItem( const Vector3<float> &pPosition, eHand pHand ) : HandItem( "StabbingSword", pHand ) {
	m_handLeftOffset = Vector3<float>( -0.45f, 0.8f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.45f, 0.8f, 0.0f );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "Sword.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
	
	SetPosition( pPosition );
	SetScale( Vector3<float>( 0.9f, 0.9f, 0.9f ) );
	
	SetUseTime( 20 );
	
	m_base = new Entity( GetPosition() );
	m_forward = new Entity( ( ( pHand == HAND_LEFT ) ? m_handLeftOffset : m_handRightOffset ) + Vector3<float>( 0.0f, 1.25f, 0.0f ) );
	
	AddChild( m_base );
	AddChild( m_forward );
}