//
//  input.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __INPUT_H__
#define __INPUT_H__

#include "math3d.h"
#include "window.h"

class Input {
    
private:
    Window *m_window;
    
    // glm::mat4 m_viewMatrix;
    // glm::mat4 m_projectionMatrix;
    Matrix4<float> m_viewMatrix;
    Matrix4<float> m_projectionMatrix;

    // glm::vec3 m_position;
    Vector3<float> m_position;
    float m_horAngle;
    float m_vertAngle;
    float m_initialFOV;
    float m_speed;
    float m_mouseSpeed;
    
public:
    Input( Window *window );
    
    void ComputeMatricesFromInputs();
    
    inline Matrix4<float> GetViewMatrix() const { return m_viewMatrix; }
    inline Matrix4<float> GetProjectionMatrix() const { return m_projectionMatrix; }
};

#endif /* input_h */
