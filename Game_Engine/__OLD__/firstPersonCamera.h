//
//  firstPersonCamera.h
//  Game_Engine
//
//  Created by Craig Milby on 1/20/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __FIRST_PERSON_CAMERA_H__
#define __FIRST_PERSON_CAMERA_H__

#include "camera.h"

class FirstPersonCamera : public Camera {
    
private:
    float m_speed;
    float m_sensitivity;
    bool m_mouseLocked;
    
public:
    FirstPersonCamera( const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Quaternion &rotation = Quaternion( 0, 0, 0, 1 ) );
    virtual ~FirstPersonCamera();
    
    virtual void Init();
    virtual void Input( float delta );
};

#endif /* firstPersonCamera_h */
