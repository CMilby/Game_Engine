//
//  random.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/29/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "random.h"

#include "math3d.h"

float Random::InRangeF( float min, float max ) {
    float random = ( ( float ) rand() ) / ( float ) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}