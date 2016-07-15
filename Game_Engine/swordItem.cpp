//
//  swordItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/13/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "swordItem.h"

SwordItem::SwordItem( const Vector3<float> &pPosition, eHand pHand ) : Item( "Sword", pHand ) {
	m_handLeftOffset = Vector3<float>( -0.45f, 0.8f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.45f, 0.8f, 0.0f );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "Sword.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
	
	SetPosition( pPosition );
	SetScale( Vector3<float>( 0.9f, 0.9f, 0.9f ) );
}