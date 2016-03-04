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

void GameSystem::AddToScene( Entity *entity ) {
	std::vector<MessagePayload> payload;
	payload.emplace_back( MessagePayload( PAYLOAD_ENTITY, entity ) );
	SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_ADD_ENTITY, payload ) );
}

void GameSystem::Input() {
	SendMessage( SYSTEM_CAMERA, Message( SYSTEM_GAME, MESSAGE_INPUT ) );
	SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_INPUT ) );
}

void GameSystem::Update() {
	SendMessage( SYSTEM_CAMERA, Message( SYSTEM_GAME, MESSAGE_UPDATE ) );
    SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_UPDATE ) );
}