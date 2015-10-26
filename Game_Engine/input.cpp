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
}

bool Input::IsKeyDown( int key ) const {
    return glfwGetKey( m_window->GetWindow(), key ) == GLFW_PRESS;
}

bool Input::IsKeyUp( int key ) const {
    return glfwGetKey( m_window->GetWindow(), key ) != GLFW_PRESS;
}

bool Input::IsButtonDown( int button ) const {
    return glfwGetMouseButton( m_window->GetWindow(), button ) == GLFW_PRESS;
}

bool Input::IsButtonUp( int button ) const {
    return glfwGetMouseButton( m_window->GetWindow(), button ) != GLFW_PRESS;
}

Vector2<float> Input::GetCursorPosition() const {
    double xPos, yPos;
    glfwGetCursorPos( m_window->GetWindow(), &xPos, &yPos );
    return Vector2<float>( ( float ) xPos, ( float ) yPos );
}

void Input::SetCursorPosition( const Vector2<float> &position ) {
    glfwSetCursorPos( m_window->GetWindow(), ( double ) position.GetX(), ( double ) position.GetY() );
}















