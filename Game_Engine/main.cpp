//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>

#include "camera.h"
#include "coreEngine.h"
#include "cube.h"
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
    Game::Init();
    
    Camera *camera = new Camera( Vector3<float>( 0, 0, 5 ) );
    RenderingEngine::SetMainCamera( *camera );
    AddToScene( camera );
    
    /*RenderableEntity *monkey = new RenderableEntity( new Mesh( "suzanne.obj" ), new Material( new Texture( "test.png", TYPE_PNG ) ) );
    monkey->SetPosition( Vector3<float>( -2, 1, 1 ) );
    AddToScene( monkey );
    
    RenderableEntity *cube = new RenderableEntity( new Mesh( "cube.obj" ), new Material( new Texture( "cube.DDS", TYPE_DDS ) ) );
    cube->SetPosition( Vector3<float>( 2, -1, -2 ) );
    AddToScene( cube );*/
    
    RenderableEntity *sphere = new RenderableEntity( new Mesh( "sphere.obj" ), new Material( new Texture( "test.png", TYPE_PNG ) ) );
    AddToScene( sphere );
}

int main(int argc, const char * argv[]) {
    Window window( 1024, 768, "Window Title" );
    Input::Init( window );
    TestGame game;
    
    CoreEngine coreEngine( &window, &game );
    coreEngine.Init();
    coreEngine.Start();
}
