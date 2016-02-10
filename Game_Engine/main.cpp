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
    Game::Init();
    
    Camera *camera = new FreeCamera( Vector3<float>( 200.0f, 100.0f, 400.0f ) );
    RenderingEngine::SetMainCamera( *camera );
    AddToScene( camera );
    
    Planet *planet = new Planet( 256.0f );
    AddToScene( planet );
}

int main(int argc, const char * argv[]) {
	Window window( Config::GetScreenWidth(), Config::GetScreenHeight(), "Game" );
    Input::Init( window );
    TestGame game;
    
    CoreEngine coreEngine( &window, &game );
    coreEngine.Init();
    coreEngine.Start();
}
