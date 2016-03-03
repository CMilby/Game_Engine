//
//  gameSystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "gameSystem.h"

GameSystem::GameSystem() : System ( SYSTEM_GAME ) {
    
}

void GameSystem::Init() {
    System::Init();
}

void GameSystem::Update() {
    SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_UPDATE ) );
}