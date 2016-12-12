//
//  quaternion.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "matrix.h"
#include "vector.h"

class Quaternion : public Vector<float, 4> {
    
public:
    Quaternion( const Vector<float, 4> &quat ) {
        ( *this )[ 0 ] = quat[ 0 ];
        ( *this )[ 1 ] = quat[ 1 ];
        ( *this )[ 2 ] = quat[ 2 ];
        ( *this )[ 3 ] = quat[ 3 ];
    }
    
    Quaternion( const Quaternion &quat ) {
        ( *this )[ 0 ] = quat[ 0 ];
        ( *this )[ 1 ] = quat[ 1 ];
        ( *this )[ 2 ] = quat[ 2 ];
        ( *this )[ 3 ] = quat[ 3 ];
    }
    
    Quaternion( float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f ) {
        ( *this )[ 0 ] = x;
        ( *this )[ 1 ] = y;
        ( *this )[ 2 ] = z;
        ( *this )[ 3 ] = w;
    }
    
    Quaternion( const Vector3<float> &vect, float angle ) {
        angle = ( float ) ( ( angle * 3.1415926536f / 180.0f ) );
        float sinAngle = sinf( angle / 2.0f );
        float cosAngle = cosf( angle / 2.0f );
        
        ( *this )[ 0 ] = vect[ 0 ] * sinAngle;
        ( *this )[ 1 ] = vect[ 1 ] * sinAngle;
        ( *this )[ 2 ] = vect[ 2 ] * sinAngle;
        ( *this )[ 3 ] = cosAngle;
    }
    
    inline Quaternion operator*( const Quaternion &r ) const {
        const float w = ( GetW() * r.GetW() ) - ( GetX() * r.GetX() ) - ( GetY() * r.GetY() ) - ( GetZ() * r.GetZ() );
        const float x = ( GetX() * r.GetW() ) + ( GetW() * r.GetX() ) + ( GetY() * r.GetZ() ) - ( GetZ() * r.GetY() );
        const float y = ( GetY() * r.GetW() ) + ( GetW() * r.GetY() ) + ( GetZ() * r.GetX() ) - ( GetX() * r.GetZ() );
        const float z = ( GetZ() * r.GetW() ) + ( GetW() * r.GetZ() ) + ( GetX() * r.GetY() ) - ( GetY() * r.GetX() );
        
        return Quaternion( x, y, z, w );
    }
    
    inline Quaternion operator*( const Vector3<float> &v ) const {
        const float w = -( GetX() * v.GetX() ) - ( GetY() * v.GetY() ) - ( GetZ() * v.GetZ() );
        const float x =  ( GetW() * v.GetX() ) + ( GetY() * v.GetZ() ) - ( GetZ() * v.GetY() );
        const float y =  ( GetW() * v.GetY() ) + ( GetZ() * v.GetX() ) - ( GetX() * v.GetZ() );
        const float z =  ( GetW() * v.GetZ() ) + ( GetX() * v.GetY() ) - ( GetY() * v.GetX() );
        
        return Quaternion( x, y, z, w );
    }
    
    inline Quaternion Conjugate() const {
        return Quaternion( -( *this )[ 0 ], -( *this )[ 1 ], -( *this )[ 2 ], ( *this )[ 3 ] );
    }
    
    inline Vector3<float> GetBack( const Matrix4<float> &rotation ) const {
        return Vector3<float>( rotation[ 0 ][ 2 ], rotation[ 1 ][ 2 ], rotation[ 2 ][ 2 ] );
    }
    
    inline Vector3<float> GetBack() const {
        return GetBack( this->ToRotationMatrix() );
    }
    
    inline Vector3<float> GetForward( const Matrix4<float> &rotation ) const {
        return GetBack( rotation ) * -1;
    }
    
    inline Vector3<float> GetForward() const {
        return GetForward( this->ToRotationMatrix() );
    }
    
    inline Vector3<float> GetRight( const Matrix4<float> &rotation ) const {
        return Vector3<float>( rotation[ 0 ][ 0 ], rotation[ 1 ][ 0 ], rotation[ 2 ][ 0 ] );
    }
    
    inline Vector3<float> GetRight() const {
        return GetRight( this->ToRotationMatrix() );
    }
    
    inline Vector3<float> GetLeft( const Matrix4<float> &rotation ) const {
        return GetRight( rotation ) * -1;
    }
    
    inline Vector3<float> GetLeft() const {
        return GetLeft( this->ToRotationMatrix() );
    }
    
    inline Vector3<float> GetUp( const Matrix4<float> &rotation ) const {
        return Vector3<float>( rotation[ 0 ][ 1 ], rotation[ 1 ][ 1 ], rotation[ 2 ][ 1 ] );;
    }
    
    inline Vector3<float> GetUp() const {
        return GetUp( this->ToRotationMatrix() );
    }
    
    inline Vector3<float> GetDown( const Matrix4<float> &rotation ) const {
        return GetUp( rotation ) * -1;
    }
    
    inline Vector3<float> GetDown() const {
        return GetDown( this->ToRotationMatrix() );
    }
    
    inline Matrix4<float> ToRotationMatrix() const {
        Vector3<float> forward = Vector3<float>( 2.0f * ( GetX() * GetZ() - GetW() * GetY() ), 2.0f * ( GetY() * GetZ() + GetW() * GetX() ), 1.0f - 2.0f * ( GetX() * GetX() + GetY() * GetY() ) );
        Vector3<float> up = Vector3<float>( 2.0f * ( GetX() * GetY() + GetW() * GetZ() ), 1.0f - 2.0f * ( GetX() * GetX() + GetZ() * GetZ() ), 2.0f * ( GetY() * GetZ() - GetW() * GetX() ) );
        Vector3<float> right = Vector3<float>( 1.0f - 2.0f * ( GetY() * GetY() + GetZ() * GetZ() ), 2.0f * ( GetX() * GetY() - GetW() * GetZ() ), 2.0f * ( GetX() * GetZ() + GetW() * GetY() ) );
        
        return Matrix4<float>().InitRotationFromVectors( forward, up, right );
    }
    
    // What do I even use this for?
    // Arcball I think?
    inline Vector3<float> ZDirection() {
        Vector3<float> vect( 0.0f, 0.0f, 0.0f );
        vect.SetX( 2 * GetW() * GetY() + 2 * GetX() * GetZ() );
        vect.SetY( 2 * GetY() * GetZ() - 2 * GetX() * GetW() );
        vect.SetZ( GetW() * GetW() + GetZ() * GetZ() - GetX() * GetX() - GetY() * GetY() );
        return vect;
    }
    
    inline float GetX() const { return ( *this )[ 0 ]; }
    inline float GetY() const { return ( *this )[ 1 ]; }
    inline float GetZ() const { return ( *this )[ 2 ]; }
    inline float GetW() const { return ( *this )[ 3 ]; }
    
    inline void SetX( float x ) { ( *this )[ 0 ] = x; }
    inline void SetY( float y ) { ( *this )[ 1 ] = y; }
    inline void SetZ( float z ) { ( *this )[ 2 ] = z; }
    inline void SetW( float w ) { ( *this )[ 3 ] = w; }
};

#endif /* quaternion_h */
