//
//  system.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include <queue>

#include "message.h"

class System {
	
private:
	SystemType m_systemType;
	std::queue<Message> m_messages;
    
public:
	System( const SystemType &system );
	virtual ~System();
	
	void SendMessage( const SystemType &system, const Message &message ) const;
	void ReceiveMessage( const Message &message );
	
	virtual void Input() {}
	virtual void Update() {}
	virtual void Render() {}
	
	void HandleMessages();
    
	inline SystemType GetSystemType() const { return m_systemType; }
};

#endif /* system_h */
