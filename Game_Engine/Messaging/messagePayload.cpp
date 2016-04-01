//
//  messagePayload.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "messagePayload.h"

MessagePayload::MessagePayload( const PayloadType &type, void *payload ) {
	m_type = type;
	m_payload = payload;
}

std::string MessagePayload::GetPayloadString() const {
	std::string *str = static_cast<std::string*>( m_payload );
	std::string ret = *str;
	delete str;
	return ret;
}

int MessagePayload::GetPayloadInt() const {
	return *static_cast<int*>( m_payload );
}

float MessagePayload::GetPayloadFloat() const {
	return *static_cast<float*>( m_payload );
}

Entity* MessagePayload::GetPayloadEntity() const {
	return static_cast<Entity*>( m_payload );
}

PhysicsBody* MessagePayload::GetPayloadPhysicsBody() const {
	return static_cast<PhysicsBody*>( m_payload );
}