//
//  superChunk.h
//  Game_Engine
//
//  Created by Craig Milby on 8/21/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SUPER_CHUNK_H__
#define __SUPER_CHUNK_H__

#include "chunk.h"
#include "entity.h"
#include "voxelShader.h"

#define S_CHUNK_X 1
#define S_CHUNK_Y 1
#define S_CHUNK_Z 1

class SuperChunk : public Entity {
	
private:
	Chunk *m_chunk[ S_CHUNK_X ][ S_CHUNK_Y ][ S_CHUNK_Z ];
	
	Texture *m_texture;
	VoxelShader *m_shader;
	
protected:
	virtual void Render();
	
public:
	SuperChunk();
	virtual ~SuperChunk();
	
	void Set( int pX, int pY, int pZ, block_t pType );
	block_t Get( int pX, int pY, int pZ ) const;
};

#endif /* superChunk_h */
