//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>

#include "config.h"
#include "coreEngine.h"
#include "entity.h"
#include "firstPersonCamera.h"
#include "freeCamera.h"
#include "game.h"
#include "input.h"
#include "planet.h"
#include "terrain.h"
#include "thirdPersonCamera.h"
#include "window.h"

class TestGame : public Game {
    
public:
    TestGame() {}
    
    virtual void Init();
};

void TestGame::Init() {
	Camera *camera = new FreeCamera( Vector3<float>( 0.0f, 3.0f, 10.0f ) );
    RenderingEngine::SetMainCamera( *camera );
    AddToScene( camera );
	
	RenderableEntity *plane = new RenderableEntity( new Mesh( "plane.obj" ) );
	AddToScene( plane );
	
	RenderableEntity *cube = new RenderableEntity( new Mesh( "cube.obj" ) );
	cube->SetPosition( Vector3<float>( 1.0f, 2.0f, -1.0f ) );
	cube->GetTransform()->Rotate( Vector3<float>( 0.0f, 1.0f, 0.0f ), 45.0f );
	AddToScene( cube );
	
    // Planet *planet = new Planet( 256.0f );
    // AddToScene( planet );
	
	Game::Init();
}

int main(int argc, const char * argv[]) {
	Window window( Config::GetScreenWidth(), Config::GetScreenHeight(), "Game" );
    Input::Init( window );
    TestGame game;
    
    CoreEngine coreEngine( &window, &game );
    coreEngine.Init();
    coreEngine.Start();
}
