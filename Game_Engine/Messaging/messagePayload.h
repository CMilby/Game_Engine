//
//  messagePayload.hp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MESSAGE_PAYLOAD_H__
#define __MESSAGE_PAYLOAD_H__

#include <string>

#include "entity.h"
#include "payloadType.h"
#include "physicsBody2d.h"

class MessagePayload {
	
private:
	void *m_payload;
    PayloadType m_type;
	
public:
    MessagePayload( const PayloadType &type, void *payload );
	
	inline void SetPayload( void *payload ) { m_payload = payload; }
	
	std::string GetPayloadString() const;
	float GetPayloadFloat() const;
	int GetPayloadInt() const;
	Entity* GetPayloadEntity() const;
	PhysicsBody2D* GetPayloadPhysicsBody() const;
};

#endif /* messagePayload_h */
