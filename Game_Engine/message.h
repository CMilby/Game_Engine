//
//  message.hpp
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
#include "receiverType.h"

class Message {
	
private:
	MessageType m_type;
	std::vector<MessagePayload> m_payload;
	DateTime m_time;
	MessageReceiver m_from;
	
public:
	Message( MessageReceiver from, MessageType type, const std::vector<MessagePayload> payload );
    
    std::string ToString() const;
};

#endif /* message_hpp */
