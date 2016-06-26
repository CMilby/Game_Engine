//
//  worldGenerator.h
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __WORLD_GENERATOR_H__
#define __WORLD_GENERATOR_H__

#include <map>

#include "simplexNoise.h"

class WorldGenerator {
	
private:
	static WorldGenerator *s_instance;
	
	SimplexNoise m_elevation;
	SimplexNoise m_temperature;
	SimplexNoise m_rainfall;
	
	WorldGenerator() {}
	
public:
	static WorldGenerator* GetInstance() {
		if ( !s_instance ) {
			s_instance = new WorldGenerator();
		}
		return s_instance;
	}
	
	void Init();
	
	int GenerateTile( int pX, int pY );
};

#endif /* worldGenerator_h */
