//
//  window.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "window.h"

Window::Window( unsigned int width, unsigned int height, const std::string &title ) {
    m_width = width;
    m_heigt = height;
    m_title = title;
    
    if ( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize glfw\n" );
        return;
    }
    
    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    
    m_window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
    if ( m_window == NULL ) {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent( m_window );
    
    glewExperimental = true;
    if ( glewInit() != GLEW_OK ) {
        fprintf( stderr, "Failed to initialize GLEW\n" );
        return;
    }
    
    glfwSetInputMode( m_window, GLFW_STICKY_KEYS, GL_TRUE );
    glfwSetInputMode( m_window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE );
    glfwSetCursorPos( m_window, 1024 / 2, 768 / 2 );
}

Window::~Window() {
    glfwDestroyWindow( m_window );
    glfwTerminate();
}

void Window::SwapBuffers() {
    glfwSwapBuffers( m_window );
}

void Window::PollEvents() {
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose( m_window );
}





