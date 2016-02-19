//
//  system.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <queue>

#include "message.h"
#include "messageBus.h"
#include "receiverType.h"

class System {
	
private:
	MessageReceiver m_receiverType;
	std::queue<Message> m_messages;
	
protected:
    void HandleMessages();
    
public:
	System( const MessageReceiver &receiverType );
	virtual ~System();
	
	void SendMessage( const MessageReceiver &receiver, const Message &message ) const;
	void ReceiveMessage( const Message &message );
	
	virtual void Input() {}
	virtual void Update() {}
	virtual void Render() {}
	
	inline MessageReceiver GetReceiverType() const { return m_receiverType; }
};

#endif /* system_h */
