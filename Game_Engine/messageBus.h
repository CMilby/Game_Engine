//
//  messageBus.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MESSAGE_BUS_H__
#define __MESSAGE_BUS_H__

#include <string>
#include <map>

#include "message.h"
#include "receiverType.h"

class System;

class MessageBus {
	
private:
	static MessageBus *s_instance;
	MessageBus();
	
	std::map<MessageReceiver, System*> m_systems;
	
public:
	static MessageBus* GetInstance() {
        if ( !s_instance ) {
            s_instance = new MessageBus();
        }
        return s_instance;
    }
	
	void AddSystem( System *system );
	
	void PostMessage( const MessageReceiver &receiver, const Message &message ) const;
};

#endif /* messageBus_h */
