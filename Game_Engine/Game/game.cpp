//
//  game.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "game.h"

#include "monster.h"
#include "player.h"
#include "world.h"

Game::Game() {
	
}

void Game::LoadGame() {
	World *world = new World();
	AddToScene( world );
	
	Player *player = new Player( Vector2<float>( 0, 0 ) );
	AddToScene( player );
	
	Monster *monster = new Monster( Vector2<float>( 5, 5 ) );
	AddToScene( monster );
	
	SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_INIT ) );
}