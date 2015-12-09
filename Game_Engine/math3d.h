//
//  math3d.hpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef math3d_hpp
#define math3d_hpp

#include <iostream>
#include <cmath>

#define ToRadian(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415926536f))

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
    
    inline Vector<T, D> operator+( const Vector<T, D> &vect ) const {
        Vector<T, D> sum;
        for ( unsigned int i = 0; i < D; i++ ) {
            sum[ i ] = m_values[ i ] + vect[ i ];
        }
        return sum;
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
    
    inline T& operator[]( unsigned int index ) {
        return m_values[ index ];
    }
    
    inline T operator[]( unsigned int index ) const {
        return m_values[ index ];
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
    
    inline Vector3<T> Cross( const Vector3<T> &vect ) const {
        T x = ( *this )[ 1 ] * vect[ 2 ] - ( *this )[ 2 ] * vect[ 1 ];
        T y = ( *this )[ 2 ] * vect[ 0 ] - ( *this )[ 0 ] * vect[ 2 ];
        T z = ( *this )[ 0 ] * vect[ 1 ] - ( *this )[ 1 ] * vect[ 2 ];
        
        return Vector3<T>( x, y, z );
    }
    
    inline T GetX() const { return ( *this )[ 0 ]; }
    inline T GetY() const { return ( *this )[ 1 ]; }
    inline T GetZ() const { return ( *this )[ 2 ]; }
    
    inline void SetX( T x ) { ( *this )[ 0 ] = x; }
    inline void SetY( T y ) { ( *this )[ 1 ] = y; }
    inline void SetZ( T z ) { ( *this )[ 2 ] = z; }
};

class Quaternion;
Vector3<float> Rotate( const Vector3<float> &vect, const Quaternion &quat );
Vector3<float> Rotate( const Vector3<float> &vect, float angle, const Vector3<float> &axis );

template<class T, unsigned int D> class Matrix {
    
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
        
        ret[ 3 ][ 0 ] = -Dot( s, eye );
        ret[ 3 ][ 1 ] = -Dot( u, eye );
        ret[ 3 ][ 2 ] = Dot( f, eye );
        
        return ret;
    }
    
    inline Matrix4<T>Scale( const Vector3<T> &scale ) const {
        Matrix4<T> ret;
        
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
    
    inline Vector3<float> GetForward( const Matrix4<float> &rotation ) const {
        return GetBack( rotation ) * -1;
    }
    
    inline Vector3<float> GetRight( const Matrix4<float> &rotation ) const {
        return Vector3<float>( rotation[ 0 ][ 0 ], rotation[ 1 ][ 0 ], rotation[ 2 ][ 0 ] );
    }
    
    inline Vector3<float> GetLeft( const Matrix4<float> &rotation ) const {
        return GetRight( rotation ) * -1;
    }
    
    inline Vector3<float> GetUp( const Matrix4<float> &rotation ) const {
        return Vector3<float>( rotation[ 0 ][ 1 ], rotation[ 1 ][ 1 ], rotation[ 2 ][ 1 ] );;
    }
    
    inline Vector3<float> GetDown( const Matrix4<float> &rotation ) const {
        return GetUp( rotation ) * -1;
    }
    
    inline Matrix4<float> ToRotationMatrix() {
        Vector3<float> forward = Vector3<float>( 2.0f * ( GetX() * GetZ() - GetW() * GetY() ), 2.0f * ( GetY() * GetZ() + GetW() * GetX() ), 1.0f - 2.0f * ( GetX() * GetX() + GetY() * GetY() ) );
        Vector3<float> up = Vector3<float>( 2.0f * ( GetX() * GetY() + GetW() * GetZ() ), 1.0f - 2.0f * ( GetX() * GetX() + GetZ() * GetZ() ), 2.0f * ( GetY() * GetZ() - GetW() * GetX() ) );
        Vector3<float> right = Vector3<float>( 1.0f - 2.0f * ( GetY() * GetY() + GetZ() * GetZ() ), 2.0f * ( GetX() * GetY() - GetW() * GetZ() ), 2.0f * ( GetX() * GetZ() + GetW() * GetY() ) );
        
        return Matrix4<float>().InitRotationFromVectors( forward, up, right );
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

namespace Random {
    
    float InRangeF( float min, float max );
};

#endif /* math3d_hpp */
