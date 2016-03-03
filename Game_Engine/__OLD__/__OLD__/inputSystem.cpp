//
//  input.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "inputSystem.h"

InputSystem* InputSystem::s_instance = 0;
Window* InputSystem::s_window = 0;
InputFramework* InputSystem::s_framework = 0;

int InputSystem::s_drawMode = 0;

InputSystem::InputSystem() : System( SYSTEM_INPUT ) {
    
}

void InputSystem::Update() {
	for ( unsigned int i = 0; i < InputFramework::NUM_KEYS; i++ ) {
		if ( s_framework->IsKeyDown( i ) ) {
			SendMessage( SYSTEM_ALL, Message( SYSTEM_INPUT, MESSAGE_KEYSTROKE ) );
		}
	}
	
	for ( unsigned int i = 0; i < InputFramework::NUM_MOUSE_BUTTONS; i++ ) {
		if ( s_framework->IsButtonDown( i ) ) {
			SendMessage( SYSTEM_ALL, Message( SYSTEM_INPUT, MESSAGE_MOUSE_BUTTON_PRESS ) );
		}
	}
}

void InputSystem::SetWindow( Window *window ) {
    s_window = window;
}

bool InputSystem::IsKeyDown( int key ) const {
	return s_framework->IsKeyDown( key );
}

bool InputSystem::IsKeyUp( int key ) const {
	return s_framework->IsKeyUp( key );
}

bool InputSystem::IsMouseDown( int button ) const {
	return s_framework->IsButtonDown( button );
}

bool InputSystem::IsMouseUp( int button ) const {
	return s_framework->IsButtonUp( button );
}

void InputSystem::SetCursorPosition( const Vector2<int> &position ) {
    s_window->SetMousePosition( position );
}

void InputSystem::SetDrawMode( int mode ) {
    s_drawMode = mode;
}

int InputSystem::GetDrawMode() {
    return s_drawMode;
}















