//
//  math3d.hpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef math3d_hpp
#define math3d_hpp

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
        ( *this )[ 0 ] = ( *this )[ 1 ] = ( *this ) = T ( 0 );
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
    
    inline T GetX() const { return ( *this )[ 0 ]; }
    inline T GetY() const { return ( *this )[ 1 ]; }
    inline T GetZ() const { return ( *this )[ 2 ]; }
    
    inline void SetX( T x ) { ( *this )[ 0 ] = x; }
    inline void SetY( T y ) { ( *this )[ 1 ] = y; }
    inline void SetZ( T z ) { ( *this )[ 2 ] = z; }
};

template<class T, unsigned int D> class Matrix {
    
private:
    T m_values[ D ][ D ];
    
public:
    Matrix();
    
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
};

class Transform {
    
};

class Color {
    
private:
    
public:
    
};

#endif /* math3d_hpp */
