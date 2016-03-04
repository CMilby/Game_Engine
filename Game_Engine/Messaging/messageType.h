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
	MESSAGE_KEYSTROKE,
	MESSAGE_MOUSE_BUTTON_PRESS,
    MESSAGE_UPDATE_MOUSE_POSITION,
    MESSAGE_WINDOW_CLOSE_REQUESTED,
    MESSAGE_CORE_ENGINE_START,
    MESSAGE_CORE_ENGINE_STOP,
	MESSAGE_UPDATE,
    MESSAGE_RENDER,
	MESSAGE_ERROR,
	MESSAGE_WARNING,
	MESSAGE_INPUT,
	MESSAGE_ADD_ENTITY,
	MESSAGE_LOAD_GAME,
	NUMBER_MESSAGES
};

inline std::string MessageTypeToString( MessageType type ) {
	switch ( type ) {
		case MESSAGE_INFO:
			return "INFO";
		case MESSAGE_KEYSTROKE:
			return "KEYSTROKE";
		case MESSAGE_MOUSE_BUTTON_PRESS:
			return "MOUSE_BUTTON_PRESS";
        case MESSAGE_UPDATE_MOUSE_POSITION:
            return "UPDATE_MOUSE_POSITION";
        case MESSAGE_WINDOW_CLOSE_REQUESTED:
            return "WINDOW_CLOSE_REQUESTED";
        case MESSAGE_CORE_ENGINE_START:
            return "CORE_ENGINE_START";
        case MESSAGE_CORE_ENGINE_STOP:
            return "CORE_ENGINE_STOP";
		case MESSAGE_UPDATE:
			return "UPDATE";
        case MESSAGE_RENDER:
            return "RENDER";
		case MESSAGE_ERROR:
			return "ERROR";
		case MESSAGE_WARNING:
			return "WARNING";
		case MESSAGE_INPUT:
			return "INPUT";
		case MESSAGE_ADD_ENTITY:
			return "ADD_ENTITY";
		case MESSAGE_LOAD_GAME:
			return "MESSAGE_LOAD_GAME";
		case NUMBER_MESSAGES:
			return std::to_string( NUMBER_MESSAGES );
	}
	return "NO_MESSAGE_TYPE";
}

#endif /* messageType_h */
