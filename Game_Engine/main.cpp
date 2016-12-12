//
//  main.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include <iostream>
#include <map>

// Architecture Reference
// http://i.stack.imgur.com/jaKUP.png

#include "core_engine.h"

#include "fl_fm_component.h"
#include "render_component.h"

#include "planet.h"

class TestGame : public Game {
    
private:
    
public:
    TestGame();
    
    virtual void Init();
    
private:
    
};

TestGame::TestGame() {
    
}

void TestGame::Init() {
    Entity *camera = new Entity( Vector3f( 0, 5, 15 ) );
    camera->AddComponent( new FreeLookFreeMoveComponent() );
    SetCamera( camera );
    
    Planet *planet = new Planet( 1238, 4, 10.0f, 30 );
    
    Entity *entity = new Entity();
    RenderComponent* render = new RenderComponent( planet->CreateMesh() );
    render->SetShaderType( ShaderType::SHADER_COLORIZED );
    entity->AddComponent( render );
    AddToScene( entity );
    
    // Entity* cube = new Entity();
    // cube->AddComponent( new RenderComponent( "cube.obj", "test.png" ) );
    // AddToScene( cube );
}

int main( int argc, const char *argv[] ) {
    Window *window = new Window( "Test" );
    CoreEngine *engine = new CoreEngine( window, new TestGame() );
    
    engine->Init();
    engine->Start();
    
    return 0;
}









