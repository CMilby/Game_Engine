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
    
    Camera *camera = new Camera( Vector3<float>( 0, 2, 5 ) );
    RenderingEngine::SetMainCamera( *camera );
    AddToScene( camera );
    
    RenderableEntity *cubeSub = new RenderableEntity( new Mesh( "cube_subdivide.obj" ) );
    cubeSub->GetTransform()->SetPosition( Vector3<float>( 1, 3, 1 ) );
    cubeSub->GetTransform()->Rotate( Vector3<float>( 0, 1, 0 ), 45.0f );
    AddToScene( cubeSub );
    
    RenderableEntity *plane = new RenderableEntity( new Mesh( "plane.obj" ) );
    AddToScene( plane );
    
    RenderableEntity *jeep = new RenderableEntity( new Mesh( "jeep.obj" ), new Material( new Texture( "jeep_army.png", TYPE_PNG ) ) );
    jeep->GetTransform()->SetScale( Vector3<float>( 0.01f, 0.01f, 0.01f ) );
    jeep->GetTransform()->SetPosition( Vector3<float>( -4.0f, 0.0f, -4.0f ) );
    jeep->GetTransform()->Rotate( Vector3<float>( 0.0f, 1.0f, 0.0f ), 180.0f );
    AddToScene( jeep );
}

int main(int argc, const char * argv[]) {
    Window window( 1200, 800, "Game" );
    Input::Init( window );
    TestGame game;
    
    CoreEngine coreEngine( &window, &game );
    coreEngine.Init();
    coreEngine.Start();
}
