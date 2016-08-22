//
//  renderableChunk.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderableChunk.h"

#include "renderableComponent.h"

RenderableChunk::RenderableChunk( int pX, int pY ) : Entity( EntityType::ENTITY_GAME_OBJECT ) {
	m_chunk = new Chunk( pX, pY );
	SetPosition( Vector3<float>( pX * CHUNK_X, pY * CHUNK_Y, 0 ) );
	
	RenderableComponent *component = new RenderableComponent();
	component->SetShaderType( ShaderType::SHADER_TILE );
	component->SetMesh( m_chunk );
	component->SetMaterial( new Material( new Texture( NUM_TILES, TILE_PATH, TILE_SIZE, TILE_SIZE ) ) );
	component->SetIsVisible( true );
	AddComponent( component );
}

RenderableChunk::~RenderableChunk() {
	
}