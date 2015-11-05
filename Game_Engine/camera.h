//
//  camera.h
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "entity.h"
#include "math3d.h"
#include "text2d.h"

class Camera : public Entity {
    
private:
    Vector3<float> m_position;
    Quaternion m_rotation;
    
    Matrix4<float> m_view;
    
    float m_speed;
    float m_sensitivity;
    
protected:
    virtual void Init();
    virtual void Input( float delta );
    
public:
    Camera( const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Quaternion &rotation = Quaternion( 0, 0, 0, 1 ) ) {
        m_position = position;
        m_rotation = rotation;
        
        m_view = m_rotation.ToRotationMatrix() * Matrix4<float>().Transform( m_position * -1 );
        
        m_speed = 0.3f;
        m_sensitivity = 0.05f;
    }
    
    void Move( const Vector3<float> &direction, float amount );
    void Rotate( const Vector3<float> &axis, float angle );
    void Rotate( const Quaternion &quaternion );
    
    Matrix4<float> GetView() const;
    Vector3<float> GetPosition() const;
};

#endif /* camera_h */
