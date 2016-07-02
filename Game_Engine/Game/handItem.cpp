//
//  handItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "handItem.h"

HandItem::HandItem( const Vector3<float> &pPosition ) : Item( pPosition, "Hand" ) {
	SetMesh( new Mesh( "player_plane.obj" ) );
	SetMaterial( new Material( new Texture( "hand.png" ) ) );
	SetShaderType( ShaderType::SHADER_BASIC );
	SetIsVisible( true );
}
