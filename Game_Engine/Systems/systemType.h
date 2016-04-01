//
//  SYSTEMType.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SYSTEM_TYPE_H__
#define __SYSTEM_TYPE_H__

#include <string>

enum SystemType {
	SYSTEM_ALL,
    SYSTEM_MESSAGE_BUS,
	SYSTEM_GAME,
	SYSTEM_RENDERING_ENGINE,
	SYSTEM_CORE_ENGINE,
	SYSTEM_PHYSICS_ENGINE,
	SYSTEM_INPUT,
	SYSTEM_CAMERA,
    SYSTEM_WINDOW,
    SYSTEM_ENTITY,
	SYSTEM_NONE,
	NUM_SYSTEMS,
};

inline std::string MessageSystemToString( SystemType system ) {
	switch ( system ) {
		case SYSTEM_ALL:
			return "ALL";
        case SYSTEM_MESSAGE_BUS:
            return "MESSAGE_BUS";
		case SYSTEM_GAME:
			return "GAME";
		case SYSTEM_RENDERING_ENGINE:
			return "RENDERING_ENGINE";
		case SYSTEM_CORE_ENGINE:
			return "CORE_ENGINE";
		case SYSTEM_INPUT:
			return "INPUT";
		case SYSTEM_NONE:
			return "NO_SYSTEM";
		case SYSTEM_CAMERA:
			return "CAMERA";
        case SYSTEM_WINDOW:
            return "WINDOW";
        case SYSTEM_ENTITY:
            return "ENTITY";
		case SYSTEM_PHYSICS_ENGINE:
			return "PHYSICS_ENGINE";
		case NUM_SYSTEMS:
			return std::to_string( NUM_SYSTEMS );
	}
	return "NO_SYSTEM";
}

#endif /* SYSTEMType_h */