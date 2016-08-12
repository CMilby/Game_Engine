//
//  ( *this )ath3d.h
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __MATH_3D_H__
#define __MATH_3D_H__

#include <iostream>
#include <cmath>

#define ToRadian(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415926536f))

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
	
	inline std::string ToString() const {
		std::string myRet;
		for ( unsigned int i = 0; i < D; i++ ) {
			myRet += std::to_string( m_values[ i ] ) + ", ";
		}
		
		return myRet.substr( 0, myRet.length() - 2 );
	}
	
    inline void Print() const {
        for ( unsigned int i = 0; i < D; i++ ) {
            std::cout << m_values[ i ] << " ";
        }
        std::cout << "\n";
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

class Quaternion;

template<class T, unsigned int D>
class Matrix {
    
private:
    T m_values[ D ][ D ];
    
public:
    Matrix() {
        
    }
    
    Matrix( T value ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                m_values[ i ][ j ] = value;
            }
        }
    }
    
    inline Matrix<T, D> InitIdentity() {
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                if ( i == j ) {
                    m_values[ i ][ j ] = T( 1 );
                } else {
                    m_values[ i ][ j ] = T( 0 );
                }
            }
        }
        return *this;
    }
    
    inline Matrix<T, D> InitScale( const Vector<T, D - 1> &vect ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                if ( i == j && i != D - 1 ) {
                    m_values[ i ][ j ] = vect[ i ];
                } else {
                    m_values[ i ][ j ] = T( 0 );
                }
            }
        }
        m_values[ D - 1 ][ D - 1 ] = T( 1 );
        return *this;
    }
    
    inline Matrix<T, D> InitTranslation( const Vector<T, D - 1> &vect ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                if ( i == D - 1 && j != D - 1 ) {
                    m_values[ i ][ j ] = vect[ j ];
                } else if ( i == j ) {
                    m_values[ i ][ j ] = T( 1 );
                } else {
                    m_values[ i ][ j ] = T( 0 );
                }
            }
        }
        m_values[ D - 1 ][ D - 1 ] = T( 1 );
        return *this;
    }
    
    inline Matrix<T, D> operator*( const Matrix<T, D> &matrix ) const {
        Matrix<T, D> product;
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                product.m_values[ i ][ j ] = T( 0 );
                for ( unsigned int k = 0; k < D; k++ ) {
                    product.m_values[ i ][ j ] += m_values[ k ][ j ] * matrix.m_values[ i ][ k ];
                }
            }
        }
        return product;
    }
    
    /*inline Vector<T, D> Transform( const Vector<T, D> &vect ) const {
        Vector<T, D> ret;
        for ( unsigned int i = 0; i < D; i++ ) {
            ret[ i ] = T( 0 );
            for ( unsigned int j = 0; j < D; j++ ) {
                ret[ i ] += m_values[ j ][ i ] * vect[ j ];
            }
        }
        return ret;
    }*/
    
    inline Vector<T, D - 1> Transform( const Vector<T, D - 1> & vect ) const {
        Vector<T, D> r2;
        
        for ( unsigned int i = 0; i < D - 1; i++ ) {
            r2[ i ] = vect[ i ];
        }
        
        r2[ D - 1 ] = T( 1 );
        
        Vector<T, D> ret2 = Transform( r2 );
        Vector<T, D> ret;
        
        for ( unsigned int i = 0; i < D - 1; i++ ) {
            ret[ i ] = ret2[ i ];
        }
        
        return ret;
    }
    
    inline void Set( unsigned int x, unsigned int y, T value ) {
        m_values[ x ][ y ] = value;
    }
    
    inline Matrix<T, D> operator/=( const T &value ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                ( *this )[ i ][ j ] /= value;
            }
        }
        return *this;
    }
    
    inline const T* operator[]( int index) const {
        return m_values[ index ];
    }
    
    inline T* operator[]( int index ) {
        return m_values[ index ];
    }
    
    inline void Print() const {
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                std::cout << m_values[ i ][ j ] << " ";
            }
            std::cout << "\n";
        }
    }
};

template<class T> class Matrix3 : public Matrix<T, 3> {
    
public:
    Matrix3() {
        this->InitIdentity();
    }
    
    Matrix3( T value ) {
        for ( unsigned int i = 0; i < 3; i++ ) {
            for ( unsigned int j = 0; j < 3; j++ ) {
                ( *this )[ i ][ j ] = value;
            }
        }
    }
    
    Matrix3( const Matrix<T, 3> &matrix ) {
        for ( unsigned int i = 0; i < 3; i++ ) {
            for ( unsigned int j = 0; j < 3; j++ ) {
                ( *this )[ i ][ j ] = matrix[ i ][ j ];
            }
        }
    }
    
    Matrix3( const Matrix3<T> &matrix ) {
        for ( unsigned int i = 0; i < 3; i++ ) {
            for ( unsigned int j = 0; j < 3; j++ ) {
                ( *this )[ i ][ j ] = matrix[ i ][ j ];
            }
        }
    }
    
    Matrix3( const Matrix<T, 4> &matrix ) {
        for ( unsigned int i = 0; i < 3; i++ ) {
            for ( unsigned int j = 0; j < 3; j++ ) {
                ( *this )[ i ][ j ] = matrix[ i ][ j ];
            }
        }
    }
};

template<class T> class Matrix4 : public Matrix<T, 4> {
  
public:
    Matrix4() {
        this->InitIdentity();
    }
    
    Matrix4( T value ) {
        for ( unsigned int i = 0; i < 4; i++ ) {
            for ( unsigned int j = 0; j < 4; j++ ) {
                ( *this )[ i ][ j ] = value;
            }
        }
    }
    
    Matrix4( const Matrix<T, 4> &matrix ) {
        for ( unsigned int i = 0; i < 4; i++ ) {
            for ( unsigned int j = 0; j < 4; j++ ) {
                ( *this )[ i ][ j ] = matrix[ i ][ j ];
            }
        }
    }
    
    Matrix4( const Matrix4<T> &matrix ) {
        for ( unsigned int i = 0; i < 4; i++ ) {
            for ( unsigned int j = 0; j < 4; j++ ) {
                ( *this )[ i ][ j ] = matrix[ i ][ j ];
            }
        }
    }
	
	Matrix4( const Vector4<T> &pCol0, const Vector4<T> &pCol1, const Vector4<T> &pCol2, const Vector4<T> &pCol3 ) {
		( *this )[ 0 ][ 0 ] = pCol0.GetX();
		( *this )[ 1 ][ 0 ] = pCol0.GetY();
		( *this )[ 2 ][ 0 ] = pCol0.GetZ();
		( *this )[ 3 ][ 0 ] = pCol0.GetW();
		
		( *this )[ 0 ][ 1 ] = pCol1.GetX();
		( *this )[ 1 ][ 1 ] = pCol1.GetY();
		( *this )[ 2 ][ 1 ] = pCol1.GetZ();
		( *this )[ 3 ][ 1 ] = pCol1.GetW();
		
		( *this )[ 0 ][ 2 ] = pCol2.GetX();
		( *this )[ 1 ][ 2 ] = pCol2.GetY();
		( *this )[ 2 ][ 2 ] = pCol2.GetZ();
		( *this )[ 3 ][ 2 ] = pCol2.GetW();
		
		( *this )[ 0 ][ 3 ] = pCol3.GetX();
		( *this )[ 1 ][ 3 ] = pCol3.GetY();
		( *this )[ 2 ][ 3 ] = pCol3.GetZ();
		( *this )[ 3 ][ 3 ] = pCol3.GetW();
	}
    
    template<unsigned int D>
    Matrix4( const Matrix<T, D> &matrix ) {
        unsigned int size = ( D < 4 ) ? D : 4;
        for ( unsigned int i = 0; i < size; i++ ) {
            for ( unsigned int j = 0; j < size; j++ ) {
                ( *this )[ i ][ j ] = matrix[ i ][ j ];
            }
        }
    }
    
    inline Matrix4<T> Perspective( T fov, T aspectRatio, T zNear, T zFar ) {
        Matrix4<T> ret( static_cast<T>( 0 ) );
        T const tanHalfFOV = tan( fov / T( 2 ) );
        
        ret[ 0 ][ 0 ] = T( 1 ) / ( tanHalfFOV * aspectRatio );
        ret[ 1 ][ 1 ] = T( 1 ) / tanHalfFOV;
        ret[ 2 ][ 2 ] = -( zFar + zNear ) / ( zFar - zNear );
        ret[ 3 ][ 2 ] = -( T( 2 ) * zFar * zNear ) / ( zFar - zNear );
        ret[ 2 ][ 3 ] = -T( 1 );
        
        return ret;
    }
    
    inline Matrix4<T> LookAt( const Vector3<T> &eye, const Vector3<T> &center, const Vector3<T> & up ) {
        Vector3<T> const f( ( center - eye ).Normalized() );
        Vector3<T> const s( f.Cross( up ).Normalized() );
        Vector3<T> const u( s.Cross( f ) );
        
        Matrix4<T> ret( T( 1 ) );
        
        ret[ 0 ][ 0 ] = s.GetX();
        ret[ 1 ][ 0 ] = s.GetY();
        ret[ 2 ][ 0 ] = s.GetZ();
        
        ret[ 0 ][ 1 ] = u.GetX();
        ret[ 1 ][ 1 ] = u.GetY();
        ret[ 2 ][ 1 ] = u.GetZ();
        
        ret[ 0 ][ 2 ] = -f.GetX();
        ret[ 1 ][ 2 ] = -f.GetY();
        ret[ 2 ][ 2 ] = -f.GetZ();
        
        ret[ 0 ][ 3 ] = T( 0 );
        ret[ 1 ][ 3 ] = T( 0 );
        ret[ 2 ][ 3 ] = T( 0 );
        
        ret[ 3 ][ 0 ] = -s.Dot( eye );
        ret[ 3 ][ 1 ] = -u.Dot( eye );
        ret[ 3 ][ 2 ] = f.Dot( eye );
        
        return ret;
    }
    
    inline Matrix4<T>Scale( const Vector3<T> &scale ) const {
        Matrix4<T> ret = Matrix4<float>().InitIdentity();
        
        ret[ 0 ][ 0 ] = scale.GetX();
        ret[ 1 ][ 1 ] = scale.GetY();
        ret[ 2 ][ 2 ] = scale.GetZ();
        
        return ret;
    }
    
    inline Matrix4<T> Transform( const Vector3<T> &position ) const {
        Matrix4<T> ret;
        
        ret[ 3 ][ 0 ] = position.GetX();
        ret[ 3 ][ 1 ] = position.GetY();
        ret[ 3 ][ 2 ] = position.GetZ();
        
        return ret;
    }
    
    inline Matrix4<T> Model( const Vector3<T> &position, const Vector3<T> &scale ) const {
        Matrix4<T> ret;
        
        ret[ 0 ][ 0 ] = scale.GetX();
        ret[ 1 ][ 1 ] = scale.GetY();
        ret[ 2 ][ 2 ] = scale.GetZ();
        
        ret[ 3 ][ 0 ] = position.GetX();
        ret[ 3 ][ 1 ] = position.GetY();
        ret[ 3 ][ 2 ] = position.GetZ();
        
        return ret;
    }
    
    inline Matrix4<T> InitRotationFromVectors( const Vector3<T> &n, const Vector3<T> &v, const Vector3<T> &u ) {
        Matrix4<T> ret = Matrix4<T>().InitIdentity();
        
        ret[ 0 ][ 0 ] = u.GetX();
        ret[ 1 ][ 0 ] = u.GetY();
        ret[ 2 ][ 0 ] = u.GetZ();
        
        ret[ 0 ][ 1 ] = v.GetX();
        ret[ 1 ][ 1 ] = v.GetY();
        ret[ 2 ][ 1 ] = v.GetZ();
        
        ret[ 0 ][ 2 ] = n.GetX();
        ret[ 1 ][ 2 ] = n.GetY();
        ret[ 2 ][ 2 ] = n.GetZ();
        
        return ret;
    }
    
    inline Matrix4<T> InitCameraTransform( const Vector3<T> &target, const Vector3<T> &up ) const {
        Matrix4<T> ret = Matrix4<T>().InitIdentity();
        
        Vector3<float> n = target;
        n = n.Normalized();
        
        Vector3<float> u = up;
        u = u.Normalized();
        u = u.Cross( n );
        
        Vector3<float> v = n.Cross( u );
        
        ret[ 0 ][ 0 ] = u.GetX();
        ret[ 0 ][ 1 ] = u.GetY();
        ret[ 0 ][ 2 ] = u.GetZ();
        
        ret[ 1 ][ 0 ] = v.GetX();
        ret[ 1 ][ 1 ] = v.GetY();
        ret[ 1 ][ 2 ] = v.GetZ();
        
        ret[ 2 ][ 0 ] = n.GetX();
        ret[ 2 ][ 1 ] = n.GetY();
        ret[ 2 ][ 2 ] = n.GetZ();
        
        return ret;
    }
    
    // Thanks GLM!
	// Why do I even have this?!?!?
    inline Matrix4<T> InverseTranspose() {
        T SubFactor00 = ( *this )[2][2] * ( *this )[3][3] - ( *this )[3][2] * ( *this )[2][3];
        T SubFactor01 = ( *this )[2][1] * ( *this )[3][3] - ( *this )[3][1] * ( *this )[2][3];
        T SubFactor02 = ( *this )[2][1] * ( *this )[3][2] - ( *this )[3][1] * ( *this )[2][2];
        T SubFactor03 = ( *this )[2][0] * ( *this )[3][3] - ( *this )[3][0] * ( *this )[2][3];
        T SubFactor04 = ( *this )[2][0] * ( *this )[3][2] - ( *this )[3][0] * ( *this )[2][2];
        T SubFactor05 = ( *this )[2][0] * ( *this )[3][1] - ( *this )[3][0] * ( *this )[2][1];
        T SubFactor06 = ( *this )[1][2] * ( *this )[3][3] - ( *this )[3][2] * ( *this )[1][3];
        T SubFactor07 = ( *this )[1][1] * ( *this )[3][3] - ( *this )[3][1] * ( *this )[1][3];
        T SubFactor08 = ( *this )[1][1] * ( *this )[3][2] - ( *this )[3][1] * ( *this )[1][2];
        T SubFactor09 = ( *this )[1][0] * ( *this )[3][3] - ( *this )[3][0] * ( *this )[1][3];
        T SubFactor10 = ( *this )[1][0] * ( *this )[3][2] - ( *this )[3][0] * ( *this )[1][2];
        T SubFactor11 = ( *this )[1][1] * ( *this )[3][3] - ( *this )[3][1] * ( *this )[1][3];
        T SubFactor12 = ( *this )[1][0] * ( *this )[3][1] - ( *this )[3][0] * ( *this )[1][1];
        T SubFactor13 = ( *this )[1][2] * ( *this )[2][3] - ( *this )[2][2] * ( *this )[1][3];
        T SubFactor14 = ( *this )[1][1] * ( *this )[2][3] - ( *this )[2][1] * ( *this )[1][3];
        T SubFactor15 = ( *this )[1][1] * ( *this )[2][2] - ( *this )[2][1] * ( *this )[1][2];
        T SubFactor16 = ( *this )[1][0] * ( *this )[2][3] - ( *this )[2][0] * ( *this )[1][3];
        T SubFactor17 = ( *this )[1][0] * ( *this )[2][2] - ( *this )[2][0] * ( *this )[1][2];
        T SubFactor18 = ( *this )[1][0] * ( *this )[2][1] - ( *this )[2][0] * ( *this )[1][1];
    
        Matrix4<T> inverse;
        inverse[ 0 ][0] = + ( ( *this )[1][1] * SubFactor00 - ( *this )[1][2] * SubFactor01 + ( *this )[1][3] * SubFactor02);
        inverse[ 0 ][1] = - ( ( *this )[1][0] * SubFactor00 - ( *this )[1][2] * SubFactor03 + ( *this )[1][3] * SubFactor04);
        inverse[ 0 ][2] = + ( ( *this )[1][0] * SubFactor01 - ( *this )[1][1] * SubFactor03 + ( *this )[1][3] * SubFactor05);
        inverse[ 0 ][3] = - ( ( *this )[1][0] * SubFactor02 - ( *this )[1][1] * SubFactor04 + ( *this )[1][2] * SubFactor05);
        
        inverse[ 1 ][0] = - ( ( *this )[0][1] * SubFactor00 - ( *this )[0][2] * SubFactor01 + ( *this )[0][3] * SubFactor02);
        inverse[ 1 ][1] = + ( ( *this )[0][0] * SubFactor00 - ( *this )[0][2] * SubFactor03 + ( *this )[0][3] * SubFactor04);
        inverse[ 1 ][2] = - ( ( *this )[0][0] * SubFactor01 - ( *this )[0][1] * SubFactor03 + ( *this )[0][3] * SubFactor05);
        inverse[ 1 ][3] = + ( ( *this )[0][0] * SubFactor02 - ( *this )[0][1] * SubFactor04 + ( *this )[0][2] * SubFactor05);
        
        inverse[ 2 ][0] = + ( ( *this )[0][1] * SubFactor06 - ( *this )[0][2] * SubFactor07 + ( *this )[0][3] * SubFactor08);
        inverse[ 2 ][1] = - ( ( *this )[0][0] * SubFactor06 - ( *this )[0][2] * SubFactor09 + ( *this )[0][3] * SubFactor10);
        inverse[ 2 ][2] = + ( ( *this )[0][0] * SubFactor11 - ( *this )[0][1] * SubFactor09 + ( *this )[0][3] * SubFactor12);
        inverse[ 2 ][3] = - ( ( *this )[0][0] * SubFactor08 - ( *this )[0][1] * SubFactor10 + ( *this )[0][2] * SubFactor12);
        
        inverse[ 3 ][0] = - ( ( *this )[0][1] * SubFactor13 - ( *this )[0][2] * SubFactor14 + ( *this )[0][3] * SubFactor15);
        inverse[ 3 ][1] = + ( ( *this )[0][0] * SubFactor13 - ( *this )[0][2] * SubFactor16 + ( *this )[0][3] * SubFactor17);
        inverse[ 3 ][2] = - ( ( *this )[0][0] * SubFactor14 - ( *this )[0][1] * SubFactor16 + ( *this )[0][3] * SubFactor18);
        inverse[ 3 ][3] = + ( ( *this )[0][0] * SubFactor15 - ( *this )[0][1] * SubFactor17 + ( *this )[0][2] * SubFactor18);
        
        T determinant = ( *this )[ 0 ][ 0 ] * inverse[ 0 ][ 0 ] +
                        ( *this )[ 0 ][ 1 ] * inverse[ 0 ][ 1 ] +
                        ( *this )[ 0 ][ 2 ] * inverse[ 0 ][ 2 ] +
                        ( *this )[ 0 ][ 3 ] * inverse[ 0 ][ 3 ];
        inverse /= determinant;
        return inverse;
    }
	
	
	
	// Thanks GLM!
	/*inline Matrix4<T> Inverse() {
		T Coef00 = ( *this )[2][2] * ( *this )[3][3] - ( *this )[3][2] * ( *this )[2][3];
		T Coef02 = ( *this )[1][2] * ( *this )[3][3] - ( *this )[3][2] * ( *this )[1][3];
		T Coef03 = ( *this )[1][2] * ( *this )[2][3] - ( *this )[2][2] * ( *this )[1][3];
		
		T Coef04 = ( *this )[2][1] * ( *this )[3][3] - ( *this )[3][1] * ( *this )[2][3];
		T Coef06 = ( *this )[1][1] * ( *this )[3][3] - ( *this )[3][1] * ( *this )[1][3];
		T Coef07 = ( *this )[1][1] * ( *this )[2][3] - ( *this )[2][1] * ( *this )[1][3];
		
		T Coef08 = ( *this )[2][1] * ( *this )[3][2] - ( *this )[3][1] * ( *this )[2][2];
		T Coef10 = ( *this )[1][1] * ( *this )[3][2] - ( *this )[3][1] * ( *this )[1][2];
		T Coef11 = ( *this )[1][1] * ( *this )[2][2] - ( *this )[2][1] * ( *this )[1][2];
		
		T Coef12 = ( *this )[2][0] * ( *this )[3][3] - ( *this )[3][0] * ( *this )[2][3];
		T Coef14 = ( *this )[1][0] * ( *this )[3][3] - ( *this )[3][0] * ( *this )[1][3];
		T Coef15 = ( *this )[1][0] * ( *this )[2][3] - ( *this )[2][0] * ( *this )[1][3];
		
		T Coef16 = ( *this )[2][0] * ( *this )[3][2] - ( *this )[3][0] * ( *this )[2][2];
		T Coef18 = ( *this )[1][0] * ( *this )[3][2] - ( *this )[3][0] * ( *this )[1][2];
		T Coef19 = ( *this )[1][0] * ( *this )[2][2] - ( *this )[2][0] * ( *this )[1][2];
		
		T Coef20 = ( *this )[2][0] * ( *this )[3][1] - ( *this )[3][0] * ( *this )[2][1];
		T Coef22 = ( *this )[1][0] * ( *this )[3][1] - ( *this )[3][0] * ( *this )[1][1];
		T Coef23 = ( *this )[1][0] * ( *this )[2][1] - ( *this )[2][0] * ( *this )[1][1];
		
		Vector4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
		Vector4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
		Vector4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
		Vector4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
		Vector4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
		Vector4<T> Fac5(Coef20, Coef20, Coef22, Coef23);
		
		Vector4<T> Vec0(( *this )[1][0], ( *this )[0][0], ( *this )[0][0], ( *this )[0][0]);
		Vector4<T> Vec1(( *this )[1][1], ( *this )[0][1], ( *this )[0][1], ( *this )[0][1]);
		Vector4<T> Vec2(( *this )[1][2], ( *this )[0][2], ( *this )[0][2], ( *this )[0][2]);
		Vector4<T> Vec3(( *this )[1][3], ( *this )[0][3], ( *this )[0][3], ( *this )[0][3]);
		
		Vector4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		Vector4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		Vector4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		Vector4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
		
		Vector4<T> SignA(+1, -1, +1, -1);
		Vector4<T> SignB(-1, +1, -1, +1);
		Matrix4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
		
		Vector4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);
		
		Vector4<T> Dot0( ( *this )[ 0 ] * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
		
		T OneOverDeterminant = static_cast<T>( 1 ) / Dot1;
		
		return Inverse * OneOverDeterminant;
	}*/

    inline Matrix4<T> Ortho( const T &left, const T &right, const T &top, const T &bottom, const T &near, const T &far ) {
        Matrix4<float> ret = Matrix4<float>().InitIdentity();
		
        ret[ 0 ][ 0 ] =  T( 2 ) / ( right - left );
        ret[ 1 ][ 1 ] =  T( 2 ) / ( top - bottom );
        ret[ 2 ][ 2 ] = - T( 2 ) / ( far - near );
		
        ret[ 3 ][ 0 ] = - ( right + left ) / ( right - left );
        ret[ 3 ][ 1 ] = - ( top + bottom ) / ( top - bottom );
        ret[ 3 ][ 2 ] = - ( far + near ) / ( far - near );
		
        return ret;
    }
	
	inline Matrix4<T> RotationX( const T &pAngle ) {
		Matrix4<T> ret = Matrix4<T>().InitIdentity();
		
		ret[ 1 ][ 1 ] = cos( pAngle );
		ret[ 1 ][ 2 ] = -sin( pAngle );
		ret[ 2 ][ 1 ] = sin( pAngle );
		ret[ 2 ][ 2 ] = cos( pAngle );
		
		return ret;
	}
	
	inline Matrix4<T> RotationY( const T &pAngle ) {
		Matrix4<T> ret = Matrix4<T>().InitIdentity();
		
		ret[ 0 ][ 0 ] = cos( pAngle );
		ret[ 0 ][ 2 ] = sin( pAngle );
		ret[ 2 ][ 0 ] = -sin( pAngle );
		ret[ 2 ][ 2 ] = cos( pAngle );
		
		return ret;
	}
	
	inline Matrix4<T> RotationZ( const T &pAngle ) {
		Matrix4<T> ret = Matrix4<T>().InitIdentity();
		
		ret[ 0 ][ 0 ] = cos( pAngle );
		ret[ 0 ][ 1 ] = -sin( pAngle );
		ret[ 1 ][ 0 ] = sin( pAngle );
		ret[ 1 ][ 1 ] = cos( pAngle );
		
		return ret;
	}
	
	inline float* ToPointer() const {
		float *mat = new float[ 16 ];
		
		unsigned int index = 0;
		for ( unsigned int i = 0; i < 4; i++ ) {
			for ( unsigned int j = 0; j < 4; j++ ) {
				mat[ index ] = ( *this )[ i ][ j ];
			}
		}
		
		return mat;
	}
	
	inline Vector3<T> GetPosition() const {
		return Vector3<T>( ( *this )[ 3 ][ 0 ], ( *this )[ 3 ][ 1 ], ( *this )[ 3 ][ 2 ] );
	}
};

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
        angle = ToRadian( angle );
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
}

#endif /* math3d_h */






