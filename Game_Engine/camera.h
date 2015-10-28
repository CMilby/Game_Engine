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

class Camera : public Entity {
    
private:
    Vector3<float> m_position;
    Vector3<float> m_forward;
    Vector3<float> m_up;
    
protected:
    virtual void Input( float delta ) const;
    
public:
    Camera( const Vector3<float> position = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Vector3<float> forward = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Vector3<float> up = Vector3<float>( 0.0f, 1.0f, 0.0f ) ) {
        m_position = position;
        m_forward = forward;
        m_up = up;
    }
    
    inline Matrix4<float> GetView() const { return Matrix4<float>().LookAt( m_position, m_forward, m_up ); }
};

#endif /* camera_h */
