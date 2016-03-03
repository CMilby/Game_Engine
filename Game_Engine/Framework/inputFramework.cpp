//
//  inputFramework.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "inputFramework.h"

#include <SDL2/SDL.h>

InputFramework* InputFramework::s_instance = 0;

bool InputFramework::s_inputs[] = { false };
bool InputFramework::s_mouse[] = { false };

int InputFramework::s_mouseX = 0;
int InputFramework::s_mouseY = 0;

std::vector<int> InputFramework::s_downKeys = std::vector<int>();
std::vector<int> InputFramework::s_downButtons = std::vector<int>();

bool InputFramework::s_isWindowCloseRequested = false;

InputFramework::InputFramework() {
	memset( s_inputs, 0, NUM_KEYS * sizeof( bool ) );
	memset( s_mouse, 0, NUM_MOUSE_BUTTONS * sizeof( bool ) );
}

void InputFramework::Update() {
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_QUIT ) {
            s_isWindowCloseRequested = true;
		}
		
		if ( event.type == SDL_KEYDOWN ) {
			int key = event.key.keysym.scancode;
			s_inputs[ key ] = true;
            s_downKeys.emplace_back( key );
		}
		
		if ( event.type == SDL_KEYUP ) {
            int key = event.key.keysym.scancode;
			s_inputs[ key ] = false;
            s_downKeys.erase( std::remove( s_downKeys.begin(), s_downKeys.end(), key ), s_downKeys.end() );
		}
		
		if ( event.type == SDL_MOUSEMOTION ) {
			s_mouseX = event.motion.x;
			s_mouseY = event.motion.y;
		}
		
		if ( event.type == SDL_MOUSEBUTTONDOWN ) {
            int button = event.button.button;
			s_mouse[ button] = true;
            s_downButtons.emplace_back( button );
		}
		
		if ( event.type == SDL_MOUSEBUTTONUP ) {
            int button = event.button.button;
			s_mouse[ button ] = false;
            s_downButtons.erase( std::remove( s_downButtons.begin(), s_downButtons.end(), button ), s_downButtons.end() );
		}
	}
}

bool InputFramework::IsKeyDown( int key ) {
	return s_inputs[ key ];
}

bool InputFramework::IsKeyUp( int key ) {
	return !s_inputs[ key ];
}

void InputFramework::SetKey( int key, bool value ) {
	s_inputs[ key ] = value;
}

bool InputFramework::IsButtonDown( int button ) {
	return s_mouse[ button ];
}

bool InputFramework::IsButtonUp( int button ) {
	return !s_mouse[ button ];
}

void InputFramework::SetButton( int button, bool value ) {
	s_mouse[ button ] = value;
}

void InputFramework::SetCursor( bool visible ) {
	SDL_ShowCursor( visible ? 1 : 0 );
}

Vector2<int> InputFramework::GetCursorPosition() {
	return Vector2<int>( s_mouseX, s_mouseY );
}

std::vector<int> InputFramework::GetDownKeys() {
    return s_downKeys;
}

std::vector<int> InputFramework::GetDownButtons() {
    return s_downButtons;
}

bool InputFramework::IsWindowCloseRequested() {
    return s_isWindowCloseRequested;
}










