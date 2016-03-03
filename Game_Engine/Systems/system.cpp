//
//  system.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "system.h"

#include "messageBus.h"

System::System( const SystemType &system ) {
	m_systemType = system;
}

System::~System() {
	
}

void System::Init() {
    m_callbacks[ MESSAGE_UPDATE ] = std::bind( &System::HandleUpdate, this, std::placeholders::_1 );
    m_callbacks[ MESSAGE_RENDER ] = std::bind( &System::HandleRender, this, std::placeholders::_1 );
	m_callbacks[ MESSAGE_INPUT ]  = std::bind( &System::HandleInput,  this, std::placeholders::_1 );
}

void System::ReceiveMessage( const Message &message ) {
    HandleCallback( message.GetType(), message.GetPayload() );
}

void System::SendMessage( const SystemType &system, const Message &message ) {
	MessageBus::GetInstance()->PostMessage( system, message );
}

void System::HandleCallback( const MessageType &type, const std::vector<MessagePayload> &payload ) {
    if ( m_callbacks.count( type ) ) {
        m_callbacks[ type ]( payload );
    }
}

void System::HandleUpdate( const std::vector<MessagePayload> &payload ) {
    Update();
}

void System::HandleRender( const std::vector<MessagePayload> &payload ) {
    Render();
}

void System::HandleInput( const std::vector<MessagePayload> &payload ) {
	Input();
}




