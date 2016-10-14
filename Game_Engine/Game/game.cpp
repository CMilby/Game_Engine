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

#include "plane.h"
#include "world.h"

Game::Game() {
	
}

void Game::LoadGame() {
	// AddToScene( ( new Entity( EntityType::ENTITY_GAME_OBJECT ) )->AddComponent( new RenderableComponent( new Plane(), "test.png" ) ) );
	// AddToScene( new Plane() );
	// AddToScene( new Plane( 2, 2 ) );
	
	World *myWorld = new World();
	AddToScene( myWorld );
	
	SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_INIT ) );
}
