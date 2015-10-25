//
//  input.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "input.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Input::Input( Window *window ) {
    m_window = window;
    m_position = Vector3<float>( 4, 4, 3 );
    m_horAngle = 0.0f;
    m_vertAngle = 0.0f;
    m_initialFOV = 45.0f;
    m_speed = 3.0f;
    m_mouseSpeed = 0.005f;
    
    m_projectionMatrix = Matrix4<float>().Perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );
    m_viewMatrix = Matrix4<float>().LookAt( Vector3<float>( 0, 0, 5 ), Vector3<float>( 0, 0, 0 ), Vector3<float>( 0, 1, 0 ) );
}

void Input::ComputeMatricesFromInputs() {
    
}













