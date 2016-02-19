//
//  system.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "system.h"

System::System( const MessageReceiver &receiverType ) {
	m_receiverType = receiverType;
}

System::~System() {
	
}

void System::ReceiveMessage( const Message &message ) {
	m_messages.emplace( message );
}

void System::SendMessage( const MessageReceiver &receiver, const Message &message ) const {
	MessageBus::GetInstance()->PostMessage( receiver, message );
}

void System::HandleMessages() {
    while ( m_messages.size() > 0 ) {
        Message message = m_messages.front();
        m_messages.pop();
        
    
    }
}