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

void System::ReceiveMessage( const Message &message ) {
	m_messages.emplace( message );
}

void System::SendMessage( const SystemType &system, const Message &message ) const {
	MessageBus::GetInstance()->PostMessage( system, message );
}

void System::HandleMessages() {
    while ( m_messages.size() > 0 ) {
        Message message = m_messages.front();
        m_messages.pop();
        
		std::cout << message.ToString() << std::endl;
    }
}