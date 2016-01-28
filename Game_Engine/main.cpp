//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>

#include "firstPersonCamera.h"
#include "freeCamera.h"
#include "coreEngine.h"
#include "entity.h"
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
    
    Camera *camera = new FreeCamera( Vector3<float>( 0, 0, 20 ) );
    RenderingEngine::SetMainCamera( *camera );
    AddToScene( camera );
    
    /*RenderableEntity *plane = new RenderableEntity( new Mesh( "plane_test.obj" ), new Material( new Texture( "test.png" ) ) );
    // plane->GetTransform()->SetScale( Vector3<float>( 2.0f, 2.0f, 2.0f ) );
    AddToScene( plane );*/
    
    /*RenderableEntity *cube = new RenderableEntity( new Mesh( "cube.obj" ) );
    cube->SetPosition( Vector3<float>( -10, 1, 2 ) );
    plane->AddChild( cube );
    
    cube = new RenderableEntity( new Mesh( "cube.obj" ) );
    cube->SetPosition( Vector3<float>( 10, 1, 5 ) );
    plane->AddChild( cube );
    
    RenderableEntity *ent = new RenderableEntity( new Mesh( "cube.obj" ) );
    ent->SetPosition( Vector3<float>( 10, 4, -1 ) );
    
    RenderableEntity *add = new RenderableEntity( new Mesh( "plane_subdivide.obj" ) );
    add->SetPosition( Vector3<float>( 4, 2, 5 ) );
    ent->AddChild( add );
    
    add = new RenderableEntity( new Mesh( "plane_subdivide.obj" ) );
    add->SetPosition( Vector3<float>( -6, 3, 4 ) );
    ent->AddChild( add );
    
    add = new RenderableEntity( new Mesh( "plane_subdivide.obj" ) );
    add->SetPosition( Vector3<float>( -1, 0, 5 ) );
    ent->AddChild( add );
    
    plane->AddChild( ent );
    AddToScene( plane );*/
    
    /*Terrain *terrain = new Terrain( 1, true, false, true );
    terrain->SetPosition( Vector3<float>( 4, 0, 0 ) );
    terrain->SetScale( Vector3<float>( 2, 2, 2 ) );
    AddToScene( terrain );
    
    terrain = new Terrain( 1, true, false, true );
    terrain->SetPosition( Vector3<float>( -4, 0, 0 ) );
    terrain->SetScale( Vector3<float>( 2, 2, 2 ) );
    AddToScene( terrain );
    
    terrain = new Terrain( 1, true, false, true );
    terrain->SetPosition( Vector3<float>( 0, 0, 4 ) );
    terrain->SetScale( Vector3<float>( 2, 2, 2 ) );
    AddToScene( terrain );
    
    terrain = new Terrain( 1, true, false, true );
    terrain->SetPosition( Vector3<float>( 0, 0, -4 ) );
    terrain->SetScale( Vector3<float>( 2, 2, 2 ) );
    AddToScene( terrain );
    
    terrain = new Terrain( 1, true, false, true );
    terrain->SetPosition( Vector3<float>( 0, 0, 0 ) );
    terrain->SetScale( Vector3<float>( 2, 2, 2 ) );
    AddToScene( terrain );*/
    
    Planet *planet = new Planet();
    AddToScene( planet );
}

int main(int argc, const char * argv[]) {
    Window window( 1200, 800, "Game" );
    Input::Init( window );
    TestGame game;
    
    CoreEngine coreEngine( &window, &game );
    coreEngine.Init();
    coreEngine.Start();
}
