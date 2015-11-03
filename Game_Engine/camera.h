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
    Vector3<float> m_lookAt;
    Matrix4<float> m_view;
    
    float m_speed;
    float m_sensitivity;
    
protected:
    virtual void Init();
    virtual void Input( float delta );
    
public:
    Camera( const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ) ) {
        m_position = position;
        m_lookAt = Vector3<float>( 0, 0, 0 );
        
        m_speed = 0.3f;
        m_sensitivity = 0.005f;
        
        m_view = Matrix4<float>().LookAt( m_position, m_lookAt, Vector3<float>( 0, 1, 0 ) );
    }
    
    Vector3<float> Move( const Vector3<float> &direction, float amount );
    Matrix4<float> GetView() const;
    
    Vector3<float> GetPosition() const;
    // inline Vector3<float> GetLeft() const { return m_up.Cross( m_forward ); }*/
};

#endif /* camera_h */
