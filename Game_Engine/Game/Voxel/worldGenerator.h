//
//  worldGenerator.h
//  Game_Engine
//
//  Created by Craig Milby on 8/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __WORLD_GENERATOR_H__
#define __WORLD_GENERATOR_H__

#include "chunk.h"
#include "simplexNoise.h"

#define OCTAVE 4
#define PERSISTANCE 0.04f
#define SCALE 0.005f

class WorldGenerator {
	
private:
	static WorldGenerator *s_instance;
	
	SimplexNoise *m_noise;
	
public:
	static WorldGenerator* GetInstance() {
		if ( !s_instance ) {
			s_instance = new WorldGenerator();
		}
		return s_instance;
	}
	
	Chunk* GenerateChunk( int pX, int pY, int pZ );
	block_t GenerateBlock( int pX, int pY, int pZ );
};

#endif /* worldGenerator_h */
