//
//  game.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "game.h"

#include "player.h"
#include "world.h"

Game::Game() {
	
}

void Game::LoadGame() {
	Player *player = new Player( Vector2<float>( 0, 0 ) );
	AddToScene( player );
	
	World *world = new World();
	AddToScene( world );
	
	// Player *player = new Player();
	// AddToScene( player );
	
	/*RenderableEntity *cube = new RenderableEntity( "cube.obj" );
	cube->SetShaderType( SHADER_TILE );
	AddToScene( cube );
	
	RenderableEntity *cube1 = new RenderableEntity( "cube.obj" );
	cube->SetShaderType( SHADER_TILE );
	cube1->SetPosition( Vector3<float>(5,5,-5));
	AddToScene( cube1 );*/
	
	SendMessage( SYSTEM_ENTITY, Message( SYSTEM_GAME, MESSAGE_INIT ) );
}