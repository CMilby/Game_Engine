//
//  receiverType.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RECEIVER_TYPE_H__
#define __RECEIVER_TYPE_H__

#include <string>

enum MessageReceiver {
	RECEIVER_ALL,
	RECEIVER_GAME,
	RECEIVER_RENDERING_ENGINE,
	RECEIVER_CORE_ENGINE,
	RECEIVER_INPUT,
	RECEIVER_NONE,
	NUM_RECEIVERS,
};

std::string MessageReceiverToString( MessageReceiver receiver ) {
	switch ( receiver ) {
			
	}
	return "NO_RECEIVER";
}

#endif /* receiverType_h */
