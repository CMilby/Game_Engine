//
//  worldGenerator.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "worldGenerator.h"

#include <iostream>

#include "simplexNoise.h"

int WorldGenerator::GenerateTile( int pX, int pY ) {
	float myNoise = SimplexNoise::OctaveNoise2D( 3, 0.4f, 0.005f, pX, pY );
	if ( myNoise < 0.0 ) {
		return 0;
	} else {
		return 1;
	}
}