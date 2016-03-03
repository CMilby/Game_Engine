//
//  random.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/29/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "random.h"

#include "math3d.h"

float Random::InRangef( float min, float max ) {
    float random = ( ( float ) rand() ) / ( float ) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

int Random::InRangei( int min, int max ) {
    int random = ( int ) ( ( float ) rand() ) / ( float ) RAND_MAX;
    int diff = max - min;
    int r = random * diff;
    return min + r;
}