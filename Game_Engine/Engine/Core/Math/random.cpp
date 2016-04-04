//
//  random.cpp
//  Game_Engine
//
//  Created by Craig Milby on 4/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "random.h"

#include <stdlib.h>

void Random::SetSeed( unsigned int pSeed ) {
	srand( pSeed );
}

int Random::InRange( int pMin, int pMax ) {
	return pMin + ( rand() % ( int ) ( pMax - pMin + 1 ) );
}

float Random::InRange( float pMin, float pMax ) {
	return  ( pMax - pMin ) * ( ( ( ( float ) rand() ) / ( float ) RAND_MAX ) ) + pMin ;
}