//
//  input.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "input.h"

#include "input_framework.h"

bool Input::IsKeyDown( int p_key ) {
    return InputFramework::IsKeyDown( p_key );
}

bool Input::IsKeyUp( int p_key ) {
    return InputFramework::IsKeyUp( p_key );
}

void Input::SetKey( int p_key, bool p_value ) {
    InputFramework::SetKey( p_key, p_value );
}

bool Input::IsButtonDown( int p_button ) {
    return InputFramework::IsButtonDown( p_button );
}

bool Input::IsButtonUp( int p_button ) {
    return InputFramework::IsButtonDown( p_button );
}

void Input::SetButton( int p_button, bool p_value ) {
    InputFramework::SetButton( p_button, p_value );
}

void Input::SetCursor( bool p_visible ) {
    InputFramework::SetCursor( p_visible );
}

Vector2i Input::GetCursorPosition() {
    return InputFramework::GetCursorPosition();
}

std::vector<int> Input::GetDownKeys() {
    return InputFramework::GetDownKeys();
}

std::vector<int> Input::GetDownButtons() {
    return InputFramework::GetDownButtons();
}

bool Input::IsWindowCloseRequested() {
    return InputFramework::IsWindowCloseRequested();
}

void Input::SetDrawMode( int p_mode ) {
    InputFramework::SetDrawMode( p_mode );
}


