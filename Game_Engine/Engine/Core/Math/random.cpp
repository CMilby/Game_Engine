//
//  random.cpp
//  Game_Engine
//
//  Created by Craig Milby on 4/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "random.h"

#include <limits.h>

#include "system.h"

Random::Random() {
	m_twister = new MersenneTwister( 4357 );
}

Random::Random( int pSeed ) {
	m_twister = new MersenneTwister( pSeed );
}

Random::~Random() {
	if ( m_twister != 0 ) {
		delete m_twister;
	}
}

void Random::SetSeed( int pSeed ) {
	m_twister->SetSeed( pSeed );
}

double Random::Randomd() {
	double value = 0;
	
#if OS == MAC
	value = ( ( double ) m_twister->Random() / ( double ) ULONG_MAX ) * 10000000000.0;
	while ( value > 1 ) {
		value -= 1.0;
	}
#elif OS == WINDOWS
	value = ( ( double ) m_twister->Random() / ( double ) ULONG_MAX );
	while ( value > 1 ) {
		value -= 1.0;
	}
#else
	
#endif
	
	return value;
}

float Random::Randomf() {
	float value = 0;
	
#if OS == MAC
	value = ( ( float ) m_twister->Random() / ( float ) ULONG_MAX ) * 10000000000.0;
	while ( value > 1 ) {
		value -= 1.0;
	}
#elif OS == WINDOWS
	value = ( ( float ) m_twister->Random() / ( float ) ULONG_MAX );
	while ( value > 1 ) {
		value -= 1.0;
	}
#else
	
#endif
	
	return value;
}

int Random::InRange( int pMin, int pMax ) {
	return pMin + ( int ) ( Randomd() * ( ( pMax - pMin ) + 1 ) );
}

float Random::InRange( float pMin, float pMax ) {
	return pMin + ( pMax - pMin ) * Randomd();
}