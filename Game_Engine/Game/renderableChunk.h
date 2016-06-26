//
//  renderableChunk.h
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDERABLE_CHUNK_H__
#define __RENDERABLE_CHUNK_H__

#include <string>

#include "chunk.h"
#include "renderableEntity.h"

#define NUM_TILES 9
#define TILE_SIZE 64
#define TILE_PATH "tiles"

class RenderableChunk : public RenderableEntity {
	
private:
	const std::string k_textureFile = "TexAtlas.png";
	
	Chunk *m_chunk;
	
public:
	RenderableChunk( int pX, int pY );
	virtual ~RenderableChunk();
	
	Vector3<int> GetPosition() const { return m_chunk->GetPosition(); }
};

#endif /* renderableChunk_h */
