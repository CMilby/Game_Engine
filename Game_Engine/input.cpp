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

#include "sdlBackend.h"

Input Input::s_instance = Input();
Window Input::s_window = Window();

bool Input::s_inputs[] = { false };
bool Input::s_mouse[] = { false };

int Input::s_mouseX = 0;
int Input::s_mouseY = 0;

int Input::s_drawMode = 0;

Input::Input() {
    memset( s_inputs, 0, NUM_KEYS * sizeof( bool ) );
    memset( s_mouse, 0, NUM_MOUSE_BUTTONS * sizeof( bool ) );
}

void Input::Init( const Window &window ) {
    s_window = window;
}

void Input::Update() {
    SDL_Event event;
    while ( SDL_PollEvent( &event ) ) {
        if ( event.type == SDL_QUIT ) {
            SDLSetIsCloseRequested( true );
        }
        
        if ( event.type == SDL_KEYDOWN ) {
            s_inputs[ event.key.keysym.scancode ] = true;
        }
        
        if ( event.type == SDL_KEYUP ) {
            s_inputs[ event.key.keysym.scancode ] = false;
        }
        
        if ( event.type == SDL_MOUSEMOTION ) {
            s_mouseX = event.motion.x;
            s_mouseY = event.motion.y;
        }
        
        if ( event.type == SDL_MOUSEBUTTONDOWN ) {
            s_mouse[ event.button.button ] = true;
        }
        
        if ( event.type == SDL_MOUSEBUTTONUP ) {
            s_mouse[ event.button.button ] = false;
        }
    }
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
    SDL_ShowCursor( visible ? 1 : 0 );
}

Vector2<int> Input::GetCursorPosition() {
    return Vector2<int>( s_mouseX, s_mouseY );
}

void Input::SetCursorPosition( const Vector2<int> &position ) {
    s_window.SetMousePosition( position );
}

void Input::SetDrawMode( int mode ) {
    s_drawMode = mode;
}

int Input::GetDrawMode() {
    return s_drawMode;
}















