//
//  input.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "inputSystem.h"

Input* Input::s_instance = 0;
Window* Input::s_window = 0;
InputFramework* Input::s_framework = 0;

int Input::s_drawMode = 0;

Input::Input() : System( RECEIVER_INPUT ) {
    
}

void Input::Update() {
	for ( unsigned int i = 0; i < InputFramework::NUM_KEYS; i++ ) {
		if ( s_framework->IsKeyDown( i ) ) {
			std::vector<MessagePayload> payload;
			SendMessage( RECEIVER_ALL, Message( RECEIVER_INPUT, MESSAGE_KEYSTROKE, payload ) );
		}
	}
	
	for ( unsigned int i = 0; i < InputFramework::NUM_MOUSE_BUTTONS; i++ ) {
		if ( s_framework->IsKeyDown( i ) ) {
			std::vector<MessagePayload> payload;
			SendMessage( RECEIVER_ALL, Message( RECEIVER_INPUT, MESSAGE_BUTTON_PRESS, payload ) );
		}
	}
}

void Input::SetWindow( Window *window ) {
    s_window = window;
}

bool Input::IsKeyDown( int key ) const {
	return s_framework->IsKeyDown( key );
}

bool Input::IsKeyUp( int key ) const {
	return s_framework->IsKeyUp( key );
}

bool Input::IsMouseDown( int button ) const {
	return s_framework->IsButtonDown( button );
}

bool Input::IsMouseUp( int button ) const {
	return s_framework->IsButtonUp( button );
}

void Input::SetCursorPosition( const Vector2<int> &position ) {
    s_window->SetMousePosition( position );
}

void Input::SetDrawMode( int mode ) {
    s_drawMode = mode;
}

int Input::GetDrawMode() {
    return s_drawMode;
}















