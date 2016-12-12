//
//  mersenne_twister.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "mersenne_twister.h"

MersenneTwister::MersenneTwister() {
    m_seed = 4357;
    SetSeed( m_seed );
}

MersenneTwister::MersenneTwister( unsigned long pSeed ) {
    m_seed = pSeed;
    SetSeed( m_seed );
}

void MersenneTwister::SetSeed( unsigned long pSeed ) {
    mt[ 0 ] = pSeed & 0xffffffff;
    for ( mti = 1; mti < N; mti++ ) {
        mt[ mti ] = ( 69069 * mt[ mti - 1 ] ) & 0xffffffff;
    }
    
    m_seed = pSeed;
}

unsigned long MersenneTwister::Random() {
    unsigned long y;
    static unsigned long mag01[ 2 ] = { 0x0, MATRIX_A };
    
    if ( mti >= N ) {
        int kk;
        
        if ( mti == N + 1 ) {
            SetSeed( 4357 );
        }
        
        for ( kk = 0; kk < N - M; kk++ ) {
            y = ( mt[ kk ] & UPPER_MASK ) | ( mt[ kk + 1 ] & LOWER_MASK );
            mt[ kk ] = mt[ kk + M ] ^ ( y >> 1 ) ^ mag01[ y & 0x1 ];
        }
        
        for (; kk < N - 1; kk++ ) {
            y = ( mt[ kk ] & UPPER_MASK ) | ( mt[ kk + 1 ] & LOWER_MASK );
            mt[ kk ] = mt[ kk + ( M - N ) ] ^ ( y >> 1 ) ^ mag01[ y & 0x1 ];
        }
        
        y = ( mt[ N - 1 ] & UPPER_MASK ) | ( mt[ 0 ] & LOWER_MASK );
        mt[ N - 1 ] = mt[ M - 1 ] ^ ( y >> 1 ) ^ mag01[ y & 0x1 ];
        
        mti = 0;
    }
    
    y = mt[ mti++ ];
    y ^= TEMPERING_SHIFT_U( y );
    y ^= TEMPERING_SHIFT_S( y ) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T( y ) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L( y );
    
    return y;
}
