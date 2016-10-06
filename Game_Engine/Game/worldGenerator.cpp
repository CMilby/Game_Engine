//
//  worldGenerator.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "worldGenerator.h"

#include "superChunk.h"
#include "texture.h"

WorldGenerator* WorldGenerator::s_instance = new WorldGenerator();

Chunk* WorldGenerator::GenerateChunk( int pX, int pY, int pZ ) {
	if ( !m_noise ) {
		m_noise = new SimplexNoise( 1234 );
	}
	
	Chunk *chunk = new Chunk();
	
	int grassSide = ArrayTextureAtlas::GetTexture( "GRASS_SIDE" );
	int grass = ArrayTextureAtlas::GetTexture( "GRASS" );
	int dirt = ArrayTextureAtlas::GetTexture( "DIRT" );
	int stone = ArrayTextureAtlas::GetTexture( "COBBLESTONE" );
	
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
			for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
				
				int n = ( int ) m_noise->ScaledOctaveNoise2D( OCTAVE, PERSISTANCE, SCALE, 4.0f, 12.0f, x + S_CHUNK_X * pX, z + S_CHUNK_Z * pZ );
				
				if ( y == n ) {
					
					chunk->Set( x, y, z, block_t( grass, dirt, grassSide, grassSide, grassSide, grassSide ) );
					
				} else if ( y < n - 4 ) {
					
					chunk->Set( x, y, z, block_t( stone ) );
					
				} else if ( y < n ) {
					
					chunk->Set( x, y, z, block_t( dirt ) );
					
				}
				
			}
		}
	}
	
	return chunk;
}

block_t WorldGenerator::GenerateBlock( int pX, int pY, int pZ ) {
	if ( !m_noise ) {
		m_noise = new SimplexNoise( 1234 );
	}
	
	return block_t( 1 );
}
