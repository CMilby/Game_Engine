//
//  random.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "mersenne_twister.h"

class Random {
    
private:
    MersenneTwister *m_twister;
    
public:
    Random();
    Random( int pSeed );
    virtual ~Random();
    
    void SetSeed( int pSeed );
    
    double Randomd();
    float Randomf();
    
    int InRange( int pMin, int pMax );
    float InRange( float pMin, float pMax );
};

#endif /* random_h */
