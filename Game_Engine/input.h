//
//  input.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __INPUT_H__
#define __INPUT_H__

#include <glm/glm.hpp>

#include "window.h"

class Input {
    
private:
    Window *m_window;
    
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    
    glm::vec3 m_position;
    float m_horAngle;
    float m_vertAngle;
    float m_initialFOV;
    float m_speed;
    float m_mouseSpeed;
    
public:
    Input( Window *window );
    
    void ComputeMatricesFromInputs();
    
    inline glm::mat4 GetViewMatrix() const { return m_viewMatrix; }
    inline glm::mat4 GetProjectionMatrix() const { return m_projectionMatrix; }
};

#endif /* input_h */
