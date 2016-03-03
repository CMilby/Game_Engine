//
//  thirdPersonCamera.h
//  Game_Engine
//
//  Created by Craig Milby on 1/20/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __THIRD_PERSON_CAMERA_H__
#define __THIRD_PERSON_CAMERA_H__

#include "camera.h"

class ThirdPersonCamera : public Camera {
    
private:
    Vector3<float> m_offset;
    RenderableEntity *m_character;
    
    float m_moveSpeed;
    float m_sensitivity;
    
public:
    ThirdPersonCamera( const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Quaternion &rotation = Quaternion( 0, 0, 0, 1 ), RenderableEntity *character = new RenderableEntity( new Mesh( "suzanne.obj" ) ) );
    virtual ~ThirdPersonCamera();
    
    virtual void Init();
    virtual void Input( float delta );
    virtual void Render( const std::vector<Shader*> &shaders, const Camera &camera );
};

#endif /* thirdPersonCamera_h */
