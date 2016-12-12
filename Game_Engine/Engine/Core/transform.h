//
//  transform.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "math3d.h"

class Transform {
    
private:
    static Matrix4f s_projection;
    static Matrix4f s_ortho;
    
    Vector3f m_position;
    Vector3f m_scale;
    Quaternion m_rotation;
    
public:
    Transform( const Vector3f &p_position = Vector3f( 0.0f, 0.0f, 0.0f ), const Vector3f &p_scale = Vector3f( 1.0f, 1.0f, 1.0f ), const Quaternion &p_rotation = Quaternion() ) : m_position( p_position ), m_scale( p_scale ), m_rotation( p_rotation ) {}
    
    inline Vector3<float> GetPosition() const { return m_position; }
    inline Vector3<float> GetScale() const { return m_scale; }
    inline Quaternion GetRotation() const { return m_rotation; }
    
    inline void SetPosition( const Vector3f &p_position ) { m_position = p_position; }
    inline void SetScale ( const Vector3f &p_scale ) { m_scale = p_scale; }
    inline void SetRotation( const Quaternion &p_rotation ) { m_rotation = p_rotation; }
    
    Matrix4<float> GetModelMatrix() const;
    
    void Move( const Vector3f &p_direction, float p_amount );
    void Rotate( const Quaternion &p_quat );
    void Rotate( const Vector3f &p_axis, float p_angle );
    
    static void SetPerspectiveProjection( const Matrix4f &p_projection ) { s_projection = p_projection; }
    static void SetPerspectiveProjection( const float p_fov, const float p_aspectRatio, const float p_zNear, const float p_zFar ) { SetPerspectiveProjection( Matrix4f().Perspective( p_fov, p_aspectRatio, p_zNear, p_zFar ) );
    }
    
    static void SetOrthographicProjection( const Matrix4f &p_ortho ) { s_ortho = p_ortho; }
    static void SetOrthographicProjection( const float p_left, const float p_right, const float p_top, const float p_bottom, const float p_zNear, const float p_zFar ) {
        SetOrthographicProjection( Matrix4f().Ortho( p_left, p_right, p_top, p_bottom, p_zNear, p_zFar ) );
    }
    
    static Matrix4f GetProjection() { return s_projection; }
};

#endif /* transform_h */
