//
//  vector.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <fstream>
#include <iostream>
#include <string>

template<class T, unsigned int D> class Vector {
    
private:
    T m_values[ D ];
    
public:
    Vector() {
        for ( unsigned int i = 0; i < D; i++ )
            m_values[ i ] = T( 0 );
    }
    
    Vector( const Vector<T, D> &vect ) {
        for ( unsigned int i = 0; i < D; i++ )
            m_values[ i ] = vect[ i ];
    }
    
    inline T Dot( const Vector<T, D> &vect ) const {
        T result = T( 0 );
        for ( unsigned int i = 0; i < D; i++ ) {
            result += ( *this )[ i ] * vect[ i ];
        }
        return result;
    }
    
    inline T LengthSq() const {
        return this->Dot( *this );
    }
    
    inline T Length() const {
        return sqrt( LengthSq() );
    }
    
    inline Vector<T, D> Normalized() const {
        return *this / Length();
    }
    
    inline T Max() const {
        T max = m_values[ 0 ];
        for ( unsigned int i = 1; i < D; i++ ) {
            if ( m_values[ i ] > max ) {
                max = m_values[ i ];
            }
        }
        return max;
    }
    
    inline Vector<T, D> Max( const Vector<T, D> &pOther ) const {
        Vector<T, D> myResult;
        for ( unsigned int i = 0; i < D; i++ ) {
            myResult[ i ] = m_values[ i ] > pOther[ i ] ? m_values[ i ] : pOther[ i ];
        }
        return myResult;
    }
    
    inline T Min() const {
        T min = m_values[ 0 ];
        for ( unsigned int i = 1; i < D; i++ ) {
            if ( m_values[ i ] < min ) {
                min = m_values[ i ];
            }
        }
        return min;
    }
	
	inline Vector<T, D> Abs() const {
		Vector<T, D> myResult;
		for ( unsigned int i = 0; i < D; i++ ) {
			myResult[ i ] = ( m_values[ i ] < 0 ) ? -m_values[ i ] : m_values[ i ];
		}
		return myResult;
	}
	
    inline Vector<T, D> Reflect( const Vector<T, D> &pNormal ) const {
        return *this - ( pNormal * ( this->Dot( pNormal ) * 2 ) );
    }
    
    inline Vector<T, D> Midpoint( const Vector<T, D> &pOther ) const {
        Vector<T, D> myResult;
        for ( unsigned int i = 0; i < D; i++ ) {
            myResult[ i ] = ( m_values[ i ] + pOther[ i ] ) / T( 2 );
        }
        return myResult;
    }
    
    inline bool Contains( const T &pValue ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] == pValue ) {
                return true;
            }
        }
        
        return false;
    }
	
	inline bool IsZero() const {
		for ( unsigned int i = 0; i < D; i++ ) {
			if ( m_values[ i ] != T( 0 ) ) {
				return false;
			}
		}
		
		return true;
	}
    
    inline Vector<T, D> operator+( const Vector<T, D> &vect ) const {
        Vector<T, D> sum;
        for ( unsigned int i = 0; i < D; i++ ) {
            sum[ i ] = m_values[ i ] + vect[ i ];
        }
        return sum;
    }
    
    inline Vector<T, D> operator+( const T &pScalar ) const {
        Vector<T, D> mySum;
        for ( unsigned int i = 0; i < D; i++ ) {
            mySum[ i ] = m_values[ i ] + pScalar;
        }
        return mySum;
    }
    
    inline Vector<T, D>& operator+=( const Vector<T, D> &vect ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            ( *this )[ i ] = m_values[ i ] + vect[ i ];
        }
        return *this;
    }
    
    inline Vector<T, D> operator-( const Vector<T, D> &vect ) const {
        Vector<T, D> difference;
        for ( unsigned int i = 0; i < D; i++ ) {
            difference[ i ] = m_values[ i ] - vect[ i ];
        }
        return difference;
    }
    
    inline Vector<T, D> operator-( const T &pScalar ) const {
        Vector<T, D> myDifferece;
        for ( unsigned int i = 0; i < D; i++ ) {
            myDifferece[ i ] = m_values[ i ] - pScalar;
        }
        return myDifferece;
    }
    
    inline Vector<T, D>& operator-=( const Vector<T, D> &vect ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            m_values[ i ] -= vect[ i ];
        }
        return  *this;
    }
    
    inline Vector<T, D> operator*( const T &scale ) const {
        Vector<T, D> product;
        for ( unsigned int i = 0; i < D; i++ ) {
            product[ i ] = m_values[ i ] * scale;
        }
        return product;
    }
    
    inline Vector<T, D> operator*( const Vector<T, D> &vect ) {
        Vector<T, D> product;
        for ( unsigned int i = 0; i < D; i++ ) {
            product[ i ] = ( *this )[ i ] * vect[ i ];
        }
        return product;
    }
    
    inline Vector<T, D>& operator*=( const T &scale ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            m_values[ i ] *= scale;
        }
        return *this;
    }
    
    inline Vector<T, D> operator/( const T &scale ) const {
        Vector<T, D> quotient;
        for ( unsigned int i = 0; i < D; i++ ) {
            quotient[ i ] = m_values[ i ] / scale;
        }
        return quotient;
    }
    
    inline Vector<T, D>& operator/=( const T &scale ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            m_values[ i ] /= scale;
        }
        return *this;
    }
    
    inline bool operator==( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] != vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator!=( const Vector<T, D> &vect ) const {
        return !operator==( vect );
    }
    
    inline bool operator<( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] >= vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator>( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] <= vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator<=( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] > vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator>=( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] < vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline T& operator[]( unsigned int index ) {
        return m_values[ index ];
    }
    
    inline T operator[]( unsigned int index ) const {
        return m_values[ index ];
    }
    
    friend std::ostream& operator<<( std::ostream &p_cout, const Vector<T, D> &p_vect ) {
        p_cout << "( ";
        
        std::string myOut;
        for ( unsigned int i = 0; i < D; i++ ) {
            myOut += std::to_string( p_vect.m_values[ i ] ) + ", ";
        }
        
        p_cout << myOut.substr( 0, myOut.size() - 2 ) << " )";
        
        return p_cout;
    }
};

template<class T> class Vector2 : public Vector<T, 2> {
    
public:
    Vector2() {
        ( *this )[ 0 ] = ( *this )[ 1 ] = T( 0 );
    }
    
    Vector2( const Vector<T, 2> &vect ) {
        ( *this )[ 0 ] = vect[ 0 ];
        ( *this )[ 1 ] = vect[ 1 ];
    }
    
    Vector2( const Vector2<T> &vect ) {
        ( *this )[ 0 ] = vect[ 0 ];
        ( *this )[ 1 ] = vect[ 1 ];
    }
    
    Vector2( T x, T y ) {
        ( *this )[ 0 ] = x;
        ( *this )[ 1 ] = y;
    }
    
    inline T GetX() const { return ( *this )[ 0 ]; }
    inline T GetY() const { return ( *this )[ 1 ]; }
    
    inline void SetX( T x ) { ( *this )[ 0 ] = x; }
    inline void SetY( T y ) { ( *this )[ 1 ] = y; }
};

template<class T> class Vector3 : public Vector<T, 3> {
    
public:
    Vector3() {
        ( *this )[ 0 ] = ( *this )[ 1 ] = ( *this ) [ 2 ] = T ( 0 );
    }
    
    Vector3( const Vector<T, 3> &vect ) {
        ( *this )[ 0 ] = vect[ 0 ];
        ( *this )[ 1 ] = vect[ 1 ];
        ( *this )[ 2 ] = vect[ 2 ];
    }
    
    Vector3( const Vector3<T> &vect ) {
        ( *this )[ 0 ] = vect[ 0 ];
        ( *this )[ 1 ] = vect[ 1 ];
        ( *this )[ 2 ] = vect[ 2 ];
    }
    
    Vector3( T x, T y, T z ) {
        ( *this )[ 0 ] = x;
        ( *this )[ 1 ] = y;
        ( *this )[ 2 ] = z;
    }
    
    Vector3( const Vector2<T> &pVect, T pZ ) {
        ( *this )[ 0 ] = pVect[ 0 ];
        ( *this )[ 1 ] = pVect[ 1 ];
        ( *this )[ 2 ] = pZ;
    }
    
    inline Vector3<T> Cross( const Vector3<T> &vect ) const {
        T x = ( *this )[ 1 ] * vect[ 2 ] - ( *this )[ 2 ] * vect[ 1 ];
        T y = ( *this )[ 2 ] * vect[ 0 ] - ( *this )[ 0 ] * vect[ 2 ];
        T z = ( *this )[ 0 ] * vect[ 1 ] - ( *this )[ 1 ] * vect[ 2 ];
        
        return Vector3<T>( x, y, z );
    }
    
    inline Vector3<T> Lerp( const Vector3<T> &pVect, T pLerpFactor ) const {
        return ( pVect - *this ) * pLerpFactor + *this;
    }
    
    inline Vector3<T> SLerp( const Vector3<T> &pVect, T pLerpFactor ) const {
        T myDot = this->Dot( pVect );
        myDot = Clamp( myDot, T( -1 ), T( 1 ) );
        
        T myTheta = acosf( myDot ) * pLerpFactor;
        Vector3<T> relative = pVect - ( *this ) * myDot;
        relative = relative.Normalized();
        return ( ( ( *this ) * cosf( myTheta ) ) + ( relative * sinf( myTheta ) ) );
    }
    
    inline Vector3<T> NLerp( const Vector3<T> &pVect, T pLerpFactor ) const {
        return this->Lerp( pVect, pLerpFactor ).Normalized();
    }
    
    inline Vector3<T> RotateX( const T &pAngle ) const {
        T myAngle = ToRadian( pAngle );
        return Vector3<T>( GetX(),
                          GetY() * cosf( myAngle ) - GetZ() * sinf( myAngle ),
                          GetY() * sinf( myAngle ) + GetZ() * cosf( myAngle ) );
    }
    
    inline Vector3<T> RotateY( const T &pAngle ) const {
        T myAngle = ToRadian( pAngle );
        return Vector3<T>( GetZ() * sinf( myAngle ) + GetX() * cosf( myAngle ),
                          GetY(),
                          GetZ() * cosf( myAngle ) - GetX() * sinf( myAngle ) );
    }
    
    inline Vector3<T> RotateZ( const T &pAngle ) const {
        T myAngle = ToRadian( pAngle );
        return Vector3<T>( GetX() * cosf( myAngle ) - GetY() * sinf( myAngle ),
                          GetX() * sinf( myAngle ) + GetY() * cosf( myAngle ),
                          GetZ() );
    }
    
    inline T GetX() const { return ( *this )[ 0 ]; }
    inline T GetY() const { return ( *this )[ 1 ]; }
    inline T GetZ() const { return ( *this )[ 2 ]; }
    
    inline void SetX( const T &x ) { ( *this )[ 0 ] = x; }
    inline void SetY( const T &y ) { ( *this )[ 1 ] = y; }
    inline void SetZ( const T &z ) { ( *this )[ 2 ] = z; }
    
    inline void SetXY( const Vector2<T> &pVect ) { SetX( pVect.GetX() ); SetY( pVect.GetY() ); }
    inline void SetXZ( const Vector2<T> &pVect ) { SetX( pVect.GetX() ); SetZ( pVect.GetY() ); }
    
    inline void SetYX( const Vector2<T> &pVect ) { SetY( pVect.GetX() ); SetX( pVect.GetY() ); }
    inline void SetYZ( const Vector2<T> &pVect ) { SetY( pVect.GetX() ); SetZ( pVect.GetY() ); }
    
    inline void SetZX( const Vector2<T> &pVect ) { SetZ( pVect.GetX() ); SetX( pVect.GetY() ); }
    inline void SetZY( const Vector2<T> &pVect ) { SetZ( pVect.GetX() ); SetY( pVect.GetY() ); }
    
    inline Vector2<T> GetXY() const { return Vector2<T>( (*this )[ 0 ], ( *this )[ 1 ] ); }
    inline Vector2<T> GetXZ() const { return Vector2<T>( (*this )[ 0 ], ( *this )[ 2 ] ); }
    
    inline Vector2<T> GetYX() const { return Vector2<T>( (*this )[ 1 ], ( *this )[ 0 ] ); }
    inline Vector2<T> GetYZ() const { return Vector2<T>( (*this )[ 1 ], ( *this )[ 2 ] ); }
    
    inline Vector2<T> GetZX() const { return Vector2<T>( (*this )[ 2 ], ( *this )[ 0 ] ); }
    inline Vector2<T> GetZY() const { return Vector2<T>( (*this )[ 2 ], ( *this )[ 1 ] ); }
};

template<class T> class Vector4 : public Vector<T, 4> {
    
private:
    
public:
    Vector4() {
        ( *this )[ 0 ] = T( 0 );
        ( *this )[ 1 ] = T( 0 );
        ( *this )[ 2 ] = T( 0 );
        ( *this )[ 3 ] = T( 0 );
    }
    
    Vector4( const Vector<T, 4> &pVect ) {
        ( *this )[ 0 ] = pVect[ 0 ];
        ( *this )[ 1 ] = pVect[ 1 ];
        ( *this )[ 2 ] = pVect[ 2 ];
        ( *this )[ 3 ] = pVect[ 3 ];
    }
    
    Vector4( const Vector4<T> &pVect ) {
        ( *this )[ 0 ] = pVect[ 0 ];
        ( *this )[ 1 ] = pVect[ 1 ];
        ( *this )[ 2 ] = pVect[ 2 ];
        ( *this )[ 3 ] = pVect[ 3 ];
    }
    
    Vector4( const T &pX, const T &pY, const T &pZ, const T &pW ) {
        ( *this )[ 0 ] = pX;
        ( *this )[ 1 ] = pY;
        ( *this )[ 2 ] = pZ;
        ( *this )[ 3 ] = pW;
    }
    
    inline void SetX( const T &pX ) { ( *this )[ 0 ] = pX; }
    inline void SetY( const T &pY ) { ( *this )[ 1 ] = pY; }
    inline void SetZ( const T &pZ ) { ( *this )[ 2 ] = pZ; }
    inline void SetW( const T &pW ) { ( *this )[ 3 ] = pW; }
    
    inline T GetX() const { return ( *this )[ 0 ]; }
    inline T GetY() const { return ( *this )[ 1 ]; }
    inline T GetZ() const { return ( *this )[ 2 ]; }
    inline T GetW() const { return ( *this )[ 3 ]; }
};

template<class T>
class Vector6 : public Vector<T, 6> {
    
private:
    
public:
    Vector6() {
        ( *this )[ 0 ] = T( 0 );
        ( *this )[ 1 ] = T( 0 );
        ( *this )[ 2 ] = T( 0 );
        ( *this )[ 3 ] = T( 0 );
        ( *this )[ 4 ] = T( 0 );
        ( *this )[ 5 ] = T( 0 );
    }
    
    Vector6( const Vector<T, 6> &pVect ) {
        ( *this )[ 0 ] = pVect[ 0 ];
        ( *this )[ 1 ] = pVect[ 1 ];
        ( *this )[ 2 ] = pVect[ 2 ];
        ( *this )[ 3 ] = pVect[ 3 ];
        ( *this )[ 4 ] = pVect[ 4 ];
        ( *this )[ 5 ] = pVect[ 5 ];
    }
    
    Vector6( const Vector6<T> &pVect ) {
        ( *this )[ 0 ] = pVect[ 0 ];
        ( *this )[ 1 ] = pVect[ 1 ];
        ( *this )[ 2 ] = pVect[ 2 ];
        ( *this )[ 3 ] = pVect[ 3 ];
        ( *this )[ 4 ] = pVect[ 4 ];
        ( *this )[ 5 ] = pVect[ 5 ];
    }
    
    Vector6( const T &pX, const T &pY, const T &pZ, const T &pA, const T &pB, const T &pC ) {
        ( *this )[ 0 ] = pX;
        ( *this )[ 1 ] = pY;
        ( *this )[ 2 ] = pZ;
        ( *this )[ 3 ] = pA;
        ( *this )[ 4 ] = pB;
        ( *this )[ 5 ] = pC;
    }
    
    inline void SetX( const T &pX ) { ( *this )[ 0 ] = pX; }
    inline void SetY( const T &pY ) { ( *this )[ 1 ] = pY; }
    inline void SetZ( const T &pZ ) { ( *this )[ 2 ] = pZ; }
    inline void SetA( const T &pA ) { ( *this )[ 3 ] = pA; }
    inline void SetB( const T &pB ) { ( *this )[ 4 ] = pB; }
    inline void SetC( const T &pC ) { ( *this )[ 5 ] = pC; }
    
    inline void SetTop( const T &pTop ) { ( *this )[ 0 ] = pTop; }
    inline void SetBottom( const T &pBottom ) { ( *this )[ 1 ] = pBottom; }
    inline void SetLeft( const T &pLeft ) { ( *this )[ 2 ] = pLeft; }
    inline void SetRight( const T &pRight ) { ( *this )[ 3 ] = pRight; }
    inline void SetFront( const T &pFront ) { ( *this )[ 4 ] = pFront; }
    inline void SetBack( const T &pBack ) { ( *this )[ 5 ] = pBack; }
    
    inline T GetX() const { return ( *this )[ 0 ]; }
    inline T GetY() const { return ( *this )[ 1 ]; }
    inline T GetZ() const { return ( *this )[ 2 ]; }
    inline T GetA() const { return ( *this )[ 3 ]; }
    inline T GetB() const { return ( *this )[ 4 ]; }
    inline T GetC() const { return ( *this )[ 5 ]; }
    
    inline T GetTop() const { return ( *this )[ 0 ]; }
    inline T GetBottom() const { return ( *this )[ 1 ]; }
    inline T GetLeft() const { return ( *this )[ 2 ]; }
    inline T GetRight() const { return ( *this )[ 3 ]; }
    inline T GetFront() const { return ( *this )[ 4 ]; }
    inline T GetBack() const { return ( *this )[ 5 ]; }
};

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;

#endif /* vector_h */
