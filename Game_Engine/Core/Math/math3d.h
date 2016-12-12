//
//  math3d.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MATH3D_H__
#define __MATH3D_H__

#include <cmath>

#include "matrix.h"
#include "quaternion.h"
#include "vector.h"

#define ToRadian(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415926536f))

namespace Math3D {
    
    template<class T>
    inline T Clamp( const T &value, const T &min, const T &max ) {
        if ( value > max ) {
            return max;
        }
        
        if ( value < min ) {
            return min;
        }
        
        return value;
    }
    
    
    template<class T>
    inline T Distance( const Vector3<T> &vect1, const Vector3<T> &vect2 ) {
        return sqrtf( powf( vect2.GetX() - vect1.GetX(), 2.0f ) + powf( vect2.GetY() - vect1.GetY(), 2.0f ) + powf( vect2.GetZ() - vect1.GetZ(), 2.0f ) );
    }
    
    template<class T>
    inline Vector3<T> Midpoint( const Vector3<T> &p_v1, const Vector3<T> &p_v2 ) {
        return Vector3<T>( ( p_v1.GetX() + p_v2.GetX() ) / T( 2 ), ( p_v1.GetY() + p_v2.GetY() ) / T( 2 ), ( p_v1.GetZ() + p_v2.GetZ() ) / T( 2 ) );
    }
    
    inline int FastFloor( const float x ) {
        return x > 0 ? ( int ) x : ( int ) x - 1 ;
    }
    
    inline float Dot( const int *pG, const float pX, const float pY ) {
        return pG[ 0 ] * pX + pG[ 1 ] * pY;
    }
    
    inline float Dot( const int *g, const float x, const float y, const float z ) {
        return g[ 0 ] * x + g[ 1 ] * y + g[ 2 ] * z;
    }
    
    inline float Scale( const float x, const float a, const float b, const float min, const float max ) {
        return ( ( ( b - a ) * ( x - min ) ) / ( max - min ) ) + a;
    }
    
    inline float Max( const float pX, const float pY ) {
        if ( pX > pY ) {
            return pX;
        }
        return pY;
    }
    
    inline float Min( const float x, const float y ) {
        if ( x < y )
            return x;
        return y;
    }
    
    inline bool IsPointWithinCone( const Vector3<float> &pConeTipPosition, const Vector3<float> &pConeCenterLine, const Vector3<float> &pPoint, const float pFOVRadians ) {
        Vector3<float> myDifferenceVector = pPoint - pConeTipPosition;
        myDifferenceVector = myDifferenceVector.Normalized();
        
        return ( pConeCenterLine.Dot( myDifferenceVector ) >= cos( pFOVRadians ) );
    }
    
    inline Quaternion LookAt( const Vector3<float> &pSourcePoint, const Vector3<float> &pDestPoint ) {
        Vector3<float> forwardVector = ( pDestPoint - pSourcePoint ).Normalized();
        float dot = Vector3<float>( 0.0f, 0.0f, -1.0f ).Dot( forwardVector );
        
        if ( fabsf( dot - ( -1.0f ) ) < 0.000001f ) {
            return Quaternion( Vector3<float>( 0.0f, 1.0f, 0.0f ), M_PI);
        }
        if ( fabsf( dot - ( 1.0f ) ) < 0.000001f ) {
            return Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
        }
        
        float rotAngle = ( float ) acosf(dot);
        Vector3<float> rotAxis = Vector3<float>( 0.0f, 0.0f, -1.0f ).Cross( forwardVector );
        rotAxis = rotAxis.Normalized();
        return Quaternion( rotAxis, rotAngle );
    }
    
    inline Vector2<float> RotatePoint( const Vector2<float> &pPoint, const Vector2<float> &pCenter, float pAngle ) {
        pAngle = ToRadian( pAngle );
        
        float s = sinf( pAngle );
        float c = cosf( pAngle );
        
        Vector2<float> myPoint( pPoint.GetX() - pCenter.GetX(), pPoint.GetY() - pCenter.GetY() );
        float xNew = myPoint.GetX() * c - myPoint.GetY() * s;
        float yNew = myPoint.GetX() * s + myPoint.GetY() * c;
        
        myPoint.SetX( xNew + pCenter.GetX() );
        myPoint.SetY( yNew + pCenter.GetY() );
        
        return myPoint;
    }
    
    inline float AngleBetween( const Vector2<float> &pPoint1, const Vector2<float> &pPoint2 ) {
        return atan2f( pPoint1.GetY() - pPoint2.GetY(), pPoint1.GetX() - pPoint2.GetX() );
    }
    
    // Code From...
    // ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
    inline void InvertMatrix( float *mat, float *dst ) {
        float tmp[ 12 ]; /* temp array for pairs */
        float src[ 16 ]; /* array of transpose source matrix */
        float det; /* determinant */
        
        /* transpose matrix */
        for ( unsigned int i = 0; i < 4; i++ ) {
            src[ i ] = mat[ i * 4 ];
            src[ i + 4 ] = mat[ i * 4 + 1 ];
            src[ i + 8 ] = mat[ i * 4 + 2 ];
            src[ i + 12 ] = mat[ i * 4 + 3 ];
        }
        
        /* calculate pairs for first 8 elements (cofactors) */
        tmp[0] = src[10] * src[15];
        tmp[1] = src[11] * src[14];
        tmp[2] = src[9] * src[15];
        tmp[3] = src[11] * src[13];
        tmp[4] = src[9] * src[14];
        tmp[5] = src[10] * src[13];
        tmp[6] = src[8] * src[15];
        tmp[7] = src[11] * src[12];
        tmp[8] = src[8] * src[14];
        tmp[9] = src[10] * src[12];
        tmp[10] = src[8] * src[13];
        tmp[11] = src[9] * src[12];
        
        /* calculate first 8 elements (cofactors) */
        dst[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
        dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
        dst[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
        dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
        dst[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
        dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
        dst[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
        dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
        dst[4] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
        dst[4] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
        dst[5] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
        dst[5] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
        dst[6] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
        dst[6] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
        dst[7] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
        dst[7] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
        /* calculate pairs for second 8 elements (cofactors) */
        tmp[0] = src[2]*src[7];
        tmp[1] = src[3]*src[6];
        tmp[2] = src[1]*src[7];
        tmp[3] = src[3]*src[5];
        tmp[4] = src[1]*src[6];
        tmp[5] = src[2]*src[5];
        
        tmp[6] = src[0]*src[7];
        tmp[7] = src[3]*src[4];
        tmp[8] = src[0]*src[6];
        tmp[9] = src[2]*src[4];
        tmp[10] = src[0]*src[5];
        tmp[11] = src[1]*src[4];
        
        /* calculate second 8 elements (cofactors) */
        dst[8] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
        dst[8] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
        dst[9] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
        dst[9] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
        dst[10] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
        dst[10]-= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
        dst[11] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
        dst[11]-= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
        dst[12] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
        dst[12]-= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
        dst[13] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
        dst[13]-= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
        dst[14] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
        dst[14]-= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
        dst[15] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
        dst[15]-= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
        
        /* calculate determinant */
        det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
        
        /* calculate matrix inverse */
        det = 1/det;
        for (int j = 0; j < 16; j++)
            dst[j] *= det;
    }
    
    template<class T>
    inline Matrix4<T> Matrix4FromPointer( float *mat ) {
        Matrix4<T> mat4;
        
        for ( unsigned int i = 0; i < 16; i++ ) {
            mat4[ i % 4 ][ i / 4 ] = mat[ i ];
        }
        
        return mat4;
    }
    
    inline Vector3<float> Rotate( const Vector3<float> &vect, const Quaternion &quat ) {
        Quaternion w = quat * vect * quat.Conjugate();
        return Vector3<float>( w.GetX(), w.GetY(), w.GetZ() );
    }
    
    inline Vector3<float> Rotate( const Vector3<float> &vect, float angle, const Vector3<float> &axis ) {
        return Math3D::Rotate( vect, Quaternion( axis, angle ) );
    }
    
    inline void SetBit( uint64_t &number, uint64_t bit, uint64_t x ) {
        number ^= ( -x ^ number ) & ( 1ULL << bit );
    }
    
    inline unsigned int GetBit( uint64_t number, uint64_t bit ) {
        return ( number >> bit ) & 1ULL;
    }
    
    inline uint64_t GetBits( uint64_t number, unsigned int a, unsigned int b ) {
        uint64_t r = 0;
        
        for ( unsigned i = a; i <= b; i++ ) {
            Math3D::SetBit( r, i, Math3D::GetBit( number, i ) );
        }
        return r >> a;
    }
    
    inline void SetBits( uint64_t &number, uint64_t mask, unsigned int a, unsigned int b ) {
        for ( unsigned int i = a; i <= b; i++ ) {
            SetBit( number, i, GetBit( mask, i - a ) );
        }
    }
}

#endif /* math3d_h */
