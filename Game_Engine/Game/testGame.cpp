//
//  testGame.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "testGame.h"

#include "world.h"

TestGame::TestGame() {
	
}

void TestGame::LoadGame() {
	World *world = new World();
	AddToScene( world );
	
	// RenderableChunk *chunk = new RenderableChunk( 0, 0 );
	// AddToScene( chunk );
	
	SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_INIT ) );
}