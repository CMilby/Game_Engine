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
            m_values[ i ] += vect[ i ];
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

template<class T>
inline T Dot( Vector3<T> x, Vector3<T> y ) {
    Vector3<T> tmp( x * y );
    return tmp.GetX() + tmp.GetY() + tmp.GetZ();
}

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
    
    inline Vector<T, D> Transform( const Vector<T, D> &vect ) const {
        Vector<T, D> ret;
        for ( unsigned int i = 0; i < D; i++ ) {
            ret[ i ] = T( 0 );
            for ( unsigned int j = 0; j < D; j++ ) {
                ret[ i ] += m_values[ j ][ i ] * vect[ j ];
            }
        }
        return ret;
    }
    
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
};

class Transform {
    
};

class Color {
    
private:
    
public:
    
};

#endif /* math3d_hpp */
