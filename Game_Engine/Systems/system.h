//
//  system.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

#include "message.h"

class System {
	
private:
	SystemType m_systemType;
    
protected:
    std::map<MessageType, std::function<void( const std::vector<MessagePayload>& )>> m_callbacks;
    
    void HandleCallback( const MessageType &type, const std::vector<MessagePayload> &pPayload );
    virtual void HandleUpdate( const std::vector<MessagePayload> &pPayload );
    virtual void HandleRender( const std::vector<MessagePayload> &pPayload );
	virtual void HandleInput( const std::vector<MessagePayload> &pPayload );
    
public:
	System( const SystemType &system );
	virtual ~System();
	
	void SendMessage( const SystemType &system, const Message &message );
	void ReceiveMessage( const Message &message );
	
    virtual void Init();
	virtual void Input( float pDelta ) {}
	virtual void Update( float pDelta ) {}
	virtual void Render() {}
	
    virtual void HandleMessages() {}
    
	inline SystemType GetSystemType() const { return m_systemType; }
};

#endif /* system_h */
