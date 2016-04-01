//
//  messenger.cpp
//  Game_Engine
//
//  Created by Craig Milby on 4/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "messenger.h"

#include "messageBus.h"

void Messenger::SendMessage( const SystemType &pSystem, const Message &pMessage ) {
	MessageBus::GetInstance()->PostMessage( pSystem, pMessage );
}