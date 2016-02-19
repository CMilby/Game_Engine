//
//  message.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "message.h"

Message::Message( MessageReceiver from, MessageType type, const std::vector<MessagePayload> payload ) {
	m_from = from;
	m_type = type;
	m_payload = payload;
	m_time = DateTime();
}

std::string Message::ToString() const {
    std::string ret = m_time.ToString() + " | " + MessageTypeToString( m_type ) + " : ";
	
	return ret;
}