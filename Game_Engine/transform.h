//
//  transform.h
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "math3d.h"

class Transform {
    
private:
    static Matrix4<float> s_projection;
    
    Vector3<float> m_position;
    Vector3<float> m_scale;
    Quaternion m_rotation;
    
public:
    Transform( const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Quaternion &rotation = Quaternion(), const Vector3<float> &scale = Vector3<float>( 1.0f, 1.0f, 1.0f ) ) {
        m_position = position;
        m_rotation = rotation;
        m_scale = scale;
    }
    
    inline void SetPosition( const Vector3<float> &position ) { m_position = position; }
    inline void SetScale( const Vector3<float> &scale ) { m_scale = scale; }
    inline void SetRotation( const Quaternion &rotation ) { m_rotation = rotation; }
    
    inline Vector3<float> GetPosition() const { return m_position; }
    inline Vector3<float> GetScale() const { return m_scale; }
    inline Quaternion GetRotation() const { return m_rotation; }
    
    void Rotate( const Vector3<float> &axis, float angle );
    void Rotate( const Quaternion &quat );
    
    inline static Matrix4<float> GetProjection() { return s_projection; }
};

#endif /* transform_h */
