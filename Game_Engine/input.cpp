//
//  input.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "input.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

Input::Input( Window *window ) {
    m_window = window;
    m_position = glm::vec3( 4, 3, 3 );
    m_horAngle = 0.0f;
    m_vertAngle = 0.0f;
    m_initialFOV = 45.0f;
    m_speed = 3.0f;
    m_mouseSpeed = 0.005f;
    
    m_projectionMatrix = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );
    m_viewMatrix = glm::lookAt( glm::vec3( 0, 0, 5 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
}

void Input::ComputeMatricesFromInputs() {
    static double lastTime = glfwGetTime();
    
    double currentTime = glfwGetTime();
    float deltaTime = float ( currentTime - lastTime );
    
    double xPos, yPos;
    glfwGetCursorPos( m_window->GetWindow(), &xPos, &yPos );
    glfwSetCursorPos( m_window->GetWindow(), 1024 / 2, 768 / 2 );
    
    m_horAngle += m_mouseSpeed * float ( 1024 / 2 - xPos );
    m_vertAngle += m_mouseSpeed * float ( 768 / 2 - yPos );
    
    // m_horAngle = 0;
    // m_vertAngle = 1;
    
    glm::vec3 direction( cos( m_vertAngle ) * sin( m_horAngle ),
                         sin( m_vertAngle ),
                         cos( m_vertAngle ) * cos( m_horAngle ) );
    
    glm::vec3 right( sin( m_horAngle - 3.14f / 2.0f ),
                     0,
                     cos( m_horAngle - 3.14f / 2.0f ) );
    
    glm::vec3 up = glm::cross( right, direction );
    
    if ( m_window->GetKey( GLFW_KEY_UP ) == GLFW_PRESS ) {
        m_position += direction * deltaTime * m_speed;
    }
    
    if ( m_window->GetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
        m_position -= direction * deltaTime * m_speed;
    }
    
    if ( m_window->GetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
        m_position += right * deltaTime * m_speed;
    }
    
    if ( m_window->GetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
        m_position -= right * deltaTime * m_speed;
    }
    
    direction = glm::vec3( 0, 0, 0 );
    
    float fov = m_initialFOV;
    m_projectionMatrix = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );
    m_viewMatrix = glm::lookAt( glm::vec3( 0, 0, 5 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
    
    lastTime = currentTime;
}













