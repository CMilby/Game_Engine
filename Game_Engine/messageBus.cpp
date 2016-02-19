//
//  messageBus.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "messageBus.h"

#include "system.h"

MessageBus* MessageBus::s_instance = 0;

MessageBus::MessageBus() {
	
}

void MessageBus::PostMessage( const MessageReceiver &receiver, const Message &message ) const {
	if ( receiver == RECEIVER_ALL ) {
		for ( auto const &s : m_systems ) {
			s.second->ReceiveMessage( message );
		}
	} else {
		m_systems.at( receiver )->ReceiveMessage( message );
	}
}

void MessageBus::AddSystem( System *system ) {
	m_systems.emplace( std::pair<MessageReceiver, System*>( system->GetReceiverType(), system ) );
}