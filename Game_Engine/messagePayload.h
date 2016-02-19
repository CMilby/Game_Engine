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
	
	void SetPayload( int payload ) { m_payload = std::to_string( payload ); }
	void SetPayload( float payload ) { m_payload = std::to_string( payload ); }
	void SetPayload( const std::string &payload ) { m_payload = payload; }
	
	template<class T>
	inline T GetPayload() const {
		if ( m_type == TYPE_INT ) {
			return std::stoi( m_payload );
		} else if ( m_type == TYPE_FLOAT ) {
			return std::stof( m_payload );
		}
		return m_payload;
	}
};

#endif /* messagePayload_h */
