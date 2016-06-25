//
//  simplexNoise.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/29/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "simplexNoise.h"

#include "math3d.h"
#include "random.h"

float SimplexNoise::RawNoise3D( const float x, const float y, const float z ) {
    float n0, n1, n2, n3;
    
    float F3 = 1.0 / 3.0;
    float s = ( x + y + z ) * F3;
    int i = Math3D::FastFloor( x + s );
    int j = Math3D::FastFloor( y + s );
    int k = Math3D::FastFloor( z + s );
    
    float G3 = 1.0 / 6.0;
    float t = ( i + j + k ) * G3;
    float X0 = i - t;
    float Y0 = j - t;
    float Z0 = k - t;
    float x0 = x - X0;
    float y0 = y - Y0;
    float z0 = z - Z0;
    
    int i1, j1, k1;
    int i2, j2, k2;
    
    if ( x0 >= y0 ) {
        if (y0 >= z0 ) {
            i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
        } else if ( x0 >= z0 ) {
            i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1;
        } else {
            i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1;
        }
    } else {
        if ( y0 < z0 ) {
            i1 = 0; j1 = 0; k1 = 1; i2 = 0; j2 = 1; k2 = 1;
        } else if ( x0 < z0 ) {
            i1 = 0; j1 = 1; k1 =0 ; i2 = 0; j2 = 1; k2 = 1;
        } else {
            i1 = 0; j1 = 1; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
        }
    }
    
    float x1 = x0 - i1 + G3;
    float y1 = y0 - j1 + G3;
    float z1 = z0 - k1 + G3;
    float x2 = x0 - i2 + 2.0 * G3;
    float y2 = y0 - j2 + 2.0 * G3;
    float z2 = z0 - k2 + 2.0 * G3;
    float x3 = x0 - 1.0 + 3.0 * G3;
    float y3 = y0 - 1.0 + 3.0 * G3;
    float z3 = z0 - 1.0 + 3.0 * G3;
    
    int ii = i & 255;
    int jj = j & 255;
    int kk = k & 255;
    int gi0 = perm[ ii + perm[ jj + perm[ kk ] ] ] % 12;
    int gi1 = perm[ ii + i1 +perm[ jj + j1 + perm[ kk + k1] ] ] % 12;
    int gi2 = perm[ ii + i2 +perm[ jj + j2 + perm[ kk + k2] ] ] % 12;
    int gi3 = perm[ ii + 1 + perm[ jj + 1 + perm[ kk + 1] ] ] % 12;
    
    float t0 = 0.6 - x0 * x0 - y0 * y0 - z0 * z0;
    if( t0 < 0 ) {
        n0 = 0.0;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * Math3D::Dot( grad3[ gi0 ], x0, y0, z0 );
    }
    
    float t1 = 0.6 - x1 * x1 - y1 * y1 - z1 * z1;
    if( t1 < 0 ) {
        n1 = 0.0;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * Math3D::Dot( grad3[ gi1 ], x1, y1, z1 );
    }
    
    float t2 = 0.6 - x2 * x2 - y2 * y2 - z2 * z2;
    if( t2 < 0) {
        n2 = 0.0;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * Math3D::Dot( grad3[ gi2 ], x2, y2, z2 );
    }
    
    float t3 = 0.6 - x3 * x3 - y3 * y3 - z3 * z3;
    if( t3 < 0 ) {
        n3 = 0.0;
    } else {
        t3 *= t3;
        n3 = t3 * t3 * Math3D::Dot( grad3[ gi3 ], x3, y3, z3 );
    }
    
    return 32.0 * ( n0 + n1 + n2 + n3 );
}

float SimplexNoise::OctaveNoise3D( const float octaves, const float persistence, const float scale, const float x, const float y, const float z ) {
    float total = 0;
    float frequency = scale;
    float amplitude = 1;
                    
    float maxAmplitude = 0;
                    
    for( int i=0; i < octaves; i++ ) {
        total += RawNoise3D( x * frequency, y * frequency, z * frequency ) * amplitude;
        
        frequency *= 2;
        maxAmplitude += amplitude;
        amplitude *= persistence;
    }
                    
    return total / maxAmplitude;
}

float SimplexNoise::ScaledOctaveNoise3D( const float octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y, const float z ) {
    return OctaveNoise3D( octaves, persistence, scale, x, y, z ) * ( hiBound - loBound ) / 2 + ( hiBound + loBound ) / 2;
}

void SimplexNoise::SetSeed() {
	for ( int i = 0; i < 256; i++ ) {
		perm[ i ] = i;
	}
	
	for ( int i = 0; i < 256; i++ ) {
		int k = perm[ i ];
		int j = ( int ) Random::InRange( 0, 255 );
		
		perm[ i ] = perm[ j ];
		perm[ j ] = k;
		
		perm[ 256 + i ] = perm[ j ];
		perm[ 256 + j ] = k;
	}
}