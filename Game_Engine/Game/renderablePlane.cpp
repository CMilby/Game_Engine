//
//  renderablePlane.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderablePlane.h"

#include "plane.h"
#include "renderableComponent.h"

RenderablePlane::RenderablePlane( float p_xOffset, float p_yOffset, float p_zOffset ) : Entity( EntityType::ENTITY_GAME_OBJECT ) {
	// m_position = Vector3<float>( p_xOffset, p_yOffset, p_zOffset );
	
	SetPosition( Vector3<float>( p_xOffset, p_yOffset, p_zOffset ) );
	AddComponent( new RenderableComponent( new Plane( p_xOffset, p_yOffset, p_zOffset ), "test.png" ) );
}

RenderablePlane::~RenderablePlane() {
	
}
