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
    
    /*RenderableEntity *cubeSub = new RenderableEntity( new Mesh( "cube_subdivide.obj" ) );
    cubeSub->GetTransform()->SetPosition( Vector3<float>( 1, 3, 1 ) );
    cubeSub->GetTransform()->Rotate( Vector3<float>( 0, 1, 0 ), 45.0f );
    cubeSub->GetTransform()->Rotate( Vector3<float>( 0, 0, 1 ), 45.0f );
    AddToScene( cubeSub );*/
    
    /*RenderableEntity *jeep = new RenderableEntity( new Mesh( "jeep.obj" ), new Material( new Texture( "jeep_army.png", TYPE_PNG ) ) );
     jeep->GetTransform()->SetScale( Vector3<float>( 0.01f, 0.01f, 0.01f ) );
     jeep->GetTransform()->SetPosition( Vector3<float>( -4.0f, 0.0f, -4.0f ) );
     jeep->GetTransform()->Rotate( Vector3<float>( 0.0f, 1.0f, 0.0f ), 180.0f );
     AddToScene( jeep );*/
    
    RenderableEntity *plane = new RenderableEntity( new Mesh( "plane.obj" ), new Material( new Texture( "Test.png", TYPE_PNG ) ) );
    plane->GetTransform()->SetScale( Vector3<float>( 100.0f, 1.0f, 100.0f ) );
    AddToScene( plane );
    
    RenderableEntity *build = new RenderableEntity( new Mesh( "cube.obj" ), new Material( new Texture( "Plain.png", TYPE_PNG ) ) );
    build->GetTransform()->SetScale( Vector3<float>( 10.0f, 30.0f, 10.0f ) );
    build->GetTransform()->SetPosition( Vector3<float>( -15.0f, 30.0f, -15.0f ) );
    AddToScene( build );
    
    build = new RenderableEntity( new Mesh( "cube.obj" ), new Material( new Texture( "Plain.png", TYPE_PNG ) ) );
    build->GetTransform()->SetScale( Vector3<float>( 10.0f, 30.0f, 10.0f ) );
    build->GetTransform()->SetPosition( Vector3<float>( 30.0f, 30.0f, -15.0f ) );
    AddToScene( build );
}

int main(int argc, const char * argv[]) {
    Window window( 1200, 800, "Game" );
    Input::Init( window );
    TestGame game;
    
    CoreEngine coreEngine( &window, &game );
    coreEngine.Init();
    coreEngine.Start();
}
