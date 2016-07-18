//
//  halberdItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "halberdItem.h"

HalberdItem::HalberdItem( eHand pHand ) : StabbingSwordItem( "Halberd", pHand ) {
	m_handLeftOffset = Vector3<float>( -0.45f, 1.0f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.45f, 1.0f, 0.0f );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "halberd.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
	
	SetPosition();
	SetScale( Vector3<float>( 0.9f, 1.25f, 0.9f ) );
	
	SetUseTime( 20 );
	
	m_forward = new Entity( ( ( pHand == HAND_LEFT ) ? m_handLeftOffset : m_handRightOffset ) + Vector3<float>( 0.0f, 1.25f, 0.0f ) );
	AddChild( m_forward );
}

HalberdItem::HalberdItem( const std::string &pItem, eHand pHand ) : StabbingSwordItem( pItem, pHand ) {
	
}

HalberdItem::~HalberdItem() {
	
}