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

Input Input::s_instance = Input();
Window Input::s_window = Window();

void Input::SetWindow( const Window &window ) {
    s_window = window;
}

bool Input::IsKeyDown( int key ) {
    return glfwGetKey( s_window.GetWindow(), key ) == GLFW_PRESS;
}

bool Input::IsKeyUp( int key ) {
    return glfwGetKey( s_window.GetWindow(), key ) != GLFW_PRESS;
}

bool Input::IsButtonDown( int button ) {
    return glfwGetMouseButton( s_window.GetWindow(), button ) == GLFW_PRESS;
}

bool Input::IsButtonUp( int button ) {
    return glfwGetMouseButton( s_window.GetWindow(), button ) != GLFW_PRESS;
}

Vector2<float> Input::GetCursorPosition() {
    double xPos, yPos;
    glfwGetCursorPos( s_window.GetWindow(), &xPos, &yPos );
    return Vector2<float>( ( float ) xPos, ( float ) yPos );
}

void Input::SetCursorPosition( const Vector2<float> &position ) {
    glfwSetCursorPos( s_window.GetWindow(), ( double ) position.GetX(), ( double ) position.GetY() );
}















