//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>

#include "coreEngine.h"
#include "entity.h"
#include "game.h"
#include "input.h"
#include "window.h"

class TestGame : public Game {
    
public:
    TestGame() {}
    
    virtual void Init();
};

void TestGame::Init() {
    RenderableEntity *monkey = new RenderableEntity( "suzanne.obj", "suzanne.DDS" );
    monkey->SetPosition( Vector3<float>( -2, 1, 1 ) );
    AddToScene( monkey );
    
    RenderableEntity *cube = new RenderableEntity( "cube.obj", "cube.DDS" );
    cube->SetPosition( Vector3<float>( 2, -1, -2 ) );
    AddToScene( cube );
}

int main(int argc, const char * argv[]) {
    Window window( 1024, 768, "Window Title" );
    Input::SetWindow( window );
    TestGame game;
    
    CoreEngine coreEngine( &window, &game );
    coreEngine.Init();
    coreEngine.Start();
}
