//
//  messagePayload.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "messagePayload.h"

MessagePayload::MessagePayload( const PayloadType &type, const std::string &payload ) {
	m_type = type;
	m_payload = payload;
}