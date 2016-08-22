//
//  game.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "game.h"

#include "entity.h"
#include "renderableComponent.h"

#include "superChunk.h"

Game::Game() {
	
}

void Game::LoadGame() {
	// AddToScene( ( new Entity( EntityType::ENTITY_GAME_OBJECT ) )->AddComponent( new RenderableComponent( "cube.obj", "test.png" ) ) );
	
	SuperChunk *chunk = new SuperChunk();
	chunk->Set( 1, 1, 1, block_t( 0 ) );
	
	AddToScene( chunk );
	
	SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_INIT ) );
}