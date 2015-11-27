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

bool Input::s_inputs[] = { false };
bool Input::s_mouse[] = { false };

float Input::s_mouseX = 0;
float Input::s_mouseY = 0;

int Input::s_drawMode = 0;

Input::Input() {
    memset( s_inputs, 0, NUM_KEYS * sizeof( bool ) );
    memset( s_mouse, 0, NUM_MOUSE_BUTTONS * sizeof( bool ) );
}

void Input::Init( const Window &window ) {
    s_window = window;
    glfwSetKeyCallback( s_window.GetWindow(), KeyCallback );
    glfwSetMouseButtonCallback( s_window.GetWindow(), ButtonCallback );
    glfwSetCursorPosCallback( s_window.GetWindow(), CursorPositionCallback );
}

void Input::SetWindow( const Window &window ) {
    s_window = window;
}

bool Input::IsKeyDown( int key ) {
    return s_inputs[ key ];
}

bool Input::IsKeyUp( int key ) {
    return !s_inputs[ key ];
}

void Input::SetKey( int key, bool value ) {
    s_inputs[ key ] = value;
}

bool Input::IsButtonDown( int button ) {
    return s_mouse[ button ];
}

bool Input::IsButtonUp( int button ) {
    return !s_mouse[ button ];
}

void Input::SetButton( int button, bool value ) {
    s_mouse[ button ] = value;
}

void Input::SetCursor( bool visible ) {
    glfwSetInputMode( s_window.GetWindow(), GLFW_CURSOR, ( !visible ) ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL );
}

Vector2<float> Input::GetCursorPosition() {
    double xPos = 0.0, yPos = 0.0;
    glfwGetCursorPos( s_window.GetWindow(), &xPos, &yPos );
    
    s_mouseX = ( float ) xPos;
    s_mouseY = ( float ) yPos;
    
    return Vector2<float>( s_mouseX, s_mouseY );
}

void Input::SetCursorPosition( const Vector2<float> &position ) {
    glfwSetCursorPos( s_window.GetWindow(), position.GetX(), position.GetY() );
}

void Input::KeyCallback( GLFWwindow* handle, int key, int scancode, int action, int mods ) {
    if ( action == GLFW_PRESS ) {
        s_inputs[ key ] = true;
    }
    
    if ( action == GLFW_RELEASE ) {
        s_inputs[ key ] = false;
    }
}

void Input::ButtonCallback( GLFWwindow *handle, int button, int action, int mods ) {
    if ( action == GLFW_PRESS ) {
        s_mouse[ button ] = true;
    }
    
    if ( action == GLFW_RELEASE ) {
        s_mouse[ button ] = false;
    }
}

void Input::CursorPositionCallback( GLFWwindow *handle, double xpos, double ypos ) {
    // s_mouseX = xpos;
    // s_mouseY = ypos;
}

void Input::SetDrawMode( int mode ) {
    s_drawMode = mode;
}

int Input::GetDrawMode() {
    return s_drawMode;
}















