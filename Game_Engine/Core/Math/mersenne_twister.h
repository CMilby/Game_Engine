//
//  mersenne_twister.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MERSENNE_TWISTER_H__
#define __MERSENNE_TWISTER_H__

#define N 624
#define M 397
#define MATRIX_A 0x9908b0df
#define UPPER_MASK 0x80000000
#define LOWER_MASK 0x7fffffff

#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y) (y >> 11)
#define TEMPERING_SHIFT_S(y) (y << 7)
#define TEMPERING_SHIFT_T(y) (y << 15)
#define TEMPERING_SHIFT_L(y) (y >> 18)

class MersenneTwister {
    
private:
    unsigned long mt[ N ];
    int mti = N + 1;
    
    unsigned long m_seed;
public:
    MersenneTwister();
    MersenneTwister( unsigned long pSeed);
    
    void SetSeed( unsigned long pSeed );
    
    unsigned long Random();
};

#endif /* mersenne_twister_h */
