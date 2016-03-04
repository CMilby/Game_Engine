//
//  message.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "message.h"

Message::Message( SystemType from, MessageType type, const std::vector<MessagePayload> &payload ) {
	m_from = from;
	m_type = type;
	m_payload = payload;
    m_time = DateTime( Timing::GetCurrentTime() );
}

std::string Message::ToString() const {
    std::string ret = m_time.ToString( "H:m.s" ) + " | " + MessageSystemToString( m_from ) + " | " + MessageTypeToString( m_type ) + " | ";
	for ( unsigned int i = 0; i < m_payload.size(); i++ ) {
		ret += m_payload[ i ].GetPayloadString() + " ";
	}
	return ret;
}