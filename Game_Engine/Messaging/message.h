//
//  message.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <vector>

#include "dateTime.h"
#include "messagePayload.h"
#include "messageType.h"
#include "systemType.h"

class Message {
	
private:
	MessageType m_type;
	std::vector<MessagePayload> m_payload;
	DateTime m_time;
	SystemType m_from;
	
public:
	Message( SystemType from, MessageType type, const std::vector<MessagePayload> &payload = std::vector<MessagePayload>() );
    
    inline MessageType GetType() const { return m_type; }
    inline std::vector<MessagePayload> GetPayload() const { return m_payload; }
    
    std::string ToString() const;
};

#endif /* message_h */
