//
//  matrix.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <fstream>
#include <iostream>
#include <string>

#include "vector.h"

class Quaternion;

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
    
    friend std::ostream& operator<<( std::ostream &p_cout, const Matrix<T, D> &p_mat ) {
        std::string myOut = "";
        for ( unsigned int i = 0; i < D; i++ ) {
            for ( unsigned int j = 0; j < D; j++ ) {
                myOut += std::to_string( p_mat.m_values[ i ][ j ] ) + ", ";
            }
            
            myOut = myOut.substr( 0, myOut.size() - 2 ) + "\n";
        }
        
        p_cout << myOut;
        return p_cout;
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

typedef Matrix4<float> Matrix4f;

#endif /* matrix_h */
