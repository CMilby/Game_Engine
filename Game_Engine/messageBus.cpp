//
//  messageBus.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "messageBus.h"

MessageBus* MessageBus::s_instance = 0;

MessageBus::MessageBus() {
	
}

void MessageBus::Update() {
    for ( auto const &s : m_systems ) {
        s.second->HandleMessages();
    }
}

void MessageBus::PostMessage( const SystemType &system, const Message &message ) const {
	if ( system == SYSTEM_ALL ) {
		for ( auto const &s : m_systems ) {
			s.second->ReceiveMessage( message );
		}
	} else {
		m_systems.at( system )->ReceiveMessage( message );
	}
}

void MessageBus::AddSystem( System *system ) {
	m_systems.emplace( std::pair<SystemType, System*>( system->GetSystemType(), system ) );
}