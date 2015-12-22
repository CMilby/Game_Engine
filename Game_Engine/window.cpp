//
//  window.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "window.h"

#include "config.h"
#include "sdlBackend.h"

Window::Window( unsigned int width, unsigned int height, const std::string &title ) {
    m_width = width;
    m_heigt = height;
    m_title = title;
    
    Config::SetScreenWidth( width );
    Config::SetScreenHeight( height );
    
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        fprintf( stderr, "SDL_Init Failed\n" );
    }
    
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE,32 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    m_window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI );
    
    m_glContext = SDL_GL_CreateContext( m_window );
    if ( m_glContext == NULL ) {
        fprintf( stderr, "Failed to make GL Context\n" );
    }
    
    const unsigned char *version = glGetString( GL_VERSION );
    if ( version == NULL ) {
        fprintf( stderr, "Failed to get version" );
    }
    
    SDL_GL_MakeCurrent( m_window, m_glContext );
    SDL_GL_SetSwapInterval( 1 );
    
    glewExperimental = GL_TRUE;
    GLint status = glewInit();
    if ( status != GLEW_OK ) {
        fprintf( stderr, "Error initalizing glew: %s\n", glewGetErrorString( status ) );
    }
    
    SDLSetIsCloseRequested( false );
}

Window::~Window() {
    SDL_GL_DeleteContext( m_glContext );
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

void Window::SwapBuffers() {
    SDL_GL_SwapWindow( m_window );
}

bool Window::ShouldClose() const {
    return SDLIsCloseRequested();
}

void Window::SetShouldClose( bool value ) {
    SDLSetIsCloseRequested( value );
}

void Window::SetMousePosition( const Vector2<int> &position ) const {
    SDL_WarpMouseInWindow( m_window, position.GetX(), position.GetY() );
}

void Window::SetFullscreen( bool value ) const {
    SDL_SetWindowFullscreen( m_window, value ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );
}

Vector2<int> Window::GetMousePosition() const {
    int x, y;
    SDL_GetMouseState( &x, &y );
    return Vector2<int>( x, y );
}















