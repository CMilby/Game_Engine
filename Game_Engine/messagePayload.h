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

#include "payloadType.h"

class MessagePayload {
	
private:
    PayloadType m_type;
	std::string m_payload;
	
public:
    MessagePayload( const PayloadType &type, const std::string &payload );
	
	inline void SetPayload( int payload ) { m_payload = std::to_string( payload ); }
	inline void SetPayload( float payload ) { m_payload = std::to_string( payload ); }
	inline void SetPayload( const std::string &payload ) { m_payload = payload; }
	
	inline std::string GetPayload() const { return m_payload; }
	inline float GetPayloadFloat() const { return std::stof( m_payload ); }
	inline int GetPayloadInt() const { return std::stoi( m_payload ); }
};

#endif /* messagePayload_h */
