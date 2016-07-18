//
//  renderableChunk.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderableChunk.h"

RenderableChunk::RenderableChunk( int pX, int pY ) {
	m_chunk = new Chunk( pX, pY );
	SetPosition( Vector3<float>( pX * CHUNK_X, pY * CHUNK_Y, 0 ) );
	
	SetShaderType( ShaderType::SHADER_TILE );
	SetMesh( m_chunk );
	SetMaterial( new Material( new Texture( NUM_TILES, TILE_PATH, TILE_SIZE, TILE_SIZE ) ) );
	SetIsVisible( true );
}

RenderableChunk::~RenderableChunk() {
	
}