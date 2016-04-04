//
//  random.h
//  Game_Engine
//
//  Created by Craig Milby on 4/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RANDOM_H__
#define __RANDOM_H__

namespace Random {
	
	void SetSeed( unsigned int pSeed );

	int InRange( int pMin, int pMax );
	float InRange( float pMin, float pMax );
};

#endif /* random_h */
