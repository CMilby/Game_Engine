//
//  axeItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "axeItem.h"

AxeItem::AxeItem( eHand pHand ) : SwingingSword( "Axe", pHand ) {
	m_handLeftOffset = Vector3<float>( -0.35f, 0.5f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.35f, 0.5f, 0.0f );
	
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "axe.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
	
	SetPosition();
	SetScale( Vector3<float>( 0.75f, 0.75f, 0.75f ) );
	
	SetCooldown( 25 );
	SetUseTime( 15 );
	
	SetSwingAngle( 125.0f );
}

AxeItem::AxeItem( const std::string &pItem, eHand pHand ) : SwingingSword( pItem, pHand ) {
	// Used for subclasses
}

AxeItem::~AxeItem() {
	
}