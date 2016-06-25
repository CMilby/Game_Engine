//
//  random.cpp
//  Game_Engine
//
//  Created by Craig Milby on 4/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "random.h"

#include <stdlib.h>

#include "simplexNoise.h"

void Random::SetSeed( unsigned int pSeed ) {
	srand( pSeed );
	
	SimplexNoise::SetSeed();
}

int Random::InRange( int pMin, int pMax ) {
	return rand() % ( pMax - pMin + 1 ) + pMin;
}

float Random::InRange( float pMin, float pMax ) {
	float random = ( (float ) rand() ) / ( float ) RAND_MAX;
	float diff = pMax - pMin;
	float r = random * diff;
	return pMin + r;
}