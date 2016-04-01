//
//  messenger.h
//  Game_Engine
//
//  Created by Craig Milby on 4/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MESSENGER_H__
#define __MESSENGER_H__

#include "message.h"
#include "systemType.h"

namespace Messenger {

	void SendMessage( const SystemType &pSystem, const Message &pMessage );
}

#endif /* messenger_h */
