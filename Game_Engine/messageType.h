//
//  messageType.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MESSAGE_TYPE_H__
#define __MESSAGE_TYPE_H__

#include <string>

enum MessageType {
	MESSAGE_INFO,
	MESSAGE_UPDATE,
	MESSAGE_ERROR,
	MESSAGE_WARNING,
	NUMBER_MESSAGES
};

std::string MessageTypeToString( MessageType type ) {
	switch ( type ) {
		case MESSAGE_INFO:
			return "INFO";
		case MESSAGE_UPDATE:
			return "UPDATE";
		case MESSAGE_ERROR:
			return "ERROR";
		case MESSAGE_WARNING:
			return "WARNING";
		case NUMBER_MESSAGES:
			return "HOW_DID_THIS_EVEN_HAPPEN?";
	}
	return "NO_MESSAGE_TYPE";
}

#endif /* messageType_h */