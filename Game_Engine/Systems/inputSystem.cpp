//
//  input.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "inputSystem.h"

#include "message.h"
#include "payloadType.h"
#include "systemType.h"

InputSystem* InputSystem::s_instance = 0;
InputFramework* InputSystem::s_framework = 0;

int InputSystem::s_drawMode = 0;

InputSystem::InputSystem() : System( SYSTEM_INPUT ) {
    
}

void InputSystem::Init() {
    System::Init();
}

void InputSystem::Update() {
    s_framework->Update();
    
    std::vector<int> downKeys = s_framework->GetDownKeys();
    std::vector<MessagePayload> payload;
    
    for ( unsigned int i = 0; i < downKeys.size(); i++ ) {
        payload.clear();
        payload.emplace_back( MessagePayload( PAYLOAD_INT, std::to_string( downKeys[ i ] ) ) );
        SendMessage( SYSTEM_ALL, Message( SYSTEM_INPUT, MESSAGE_KEYSTROKE, payload ) );
    }
    
    std::vector<int> downButtons = s_framework->GetDownButtons();
    for ( unsigned int i = 0; i < downButtons.size(); i++ ) {
        SendMessage( SYSTEM_ALL, Message( SYSTEM_INPUT, MESSAGE_MOUSE_BUTTON_PRESS ) );
    }
    
    if ( s_framework->IsWindowCloseRequested() ) {
        SendMessage( SYSTEM_WINDOW, Message( SYSTEM_INPUT, MESSAGE_WINDOW_CLOSE_REQUESTED ) );
    }
    
    if ( IsKeyDown( Key::KEY_ESCAPE ) ) {
        SendMessage( SYSTEM_WINDOW, Message( SYSTEM_INPUT, MESSAGE_WINDOW_CLOSE_REQUESTED ) );
    }
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
    std::vector<MessagePayload> payload;
    payload.emplace_back( MessagePayload( PAYLOAD_FLOAT, std::to_string( position.GetX() ) ) );
    payload.emplace_back( MessagePayload( PAYLOAD_FLOAT, std::to_string( position.GetY() ) ) );
    SendMessage( SYSTEM_WINDOW, Message( SYSTEM_INPUT, MESSAGE_UPDATE_MOUSE_POSITION, payload ) );
}

void InputSystem::SetDrawMode( int mode ) {
    s_drawMode = mode;
}

int InputSystem::GetDrawMode() {
    return s_drawMode;
}















