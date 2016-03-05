//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>

// Systems
#include "cameraSystem.h"
#include "coreEngineSystem.h"
#include "entitySystem.h"
#include "gameSystem.h"
#include "inputSystem.h"
#include "messageBus.h"
#include "renderingEngineSystem.h"
#include "windowSystem.h"

// Game
#include "testGame.h"

int main( int argc, const char *argv[] ) {
    MessageBus *bus = MessageBus::GetInstance();
    
    CoreEngineSystem *coreEngine = new CoreEngineSystem();
    RenderingEngineSystem *renderingEngine = new RenderingEngineSystem();
    WindowSystem *window = new WindowSystem( 800, 600, "Game" );
    InputSystem *input = InputSystem::GetInstance();
    EntitySystem *entity = new EntitySystem();
    CameraSystem *camera = new CameraSystem( new Camera( Vector3<float>( 0, 3, 10 ) ) );
	GameSystem *game = new TestGame();
    
    bus->AddSystem( coreEngine );
    bus->AddSystem( renderingEngine );
    bus->AddSystem( window );
    bus->AddSystem( input );
    bus->AddSystem( game );
    bus->AddSystem( entity );
    bus->AddSystem( camera );
	
    bus->Init();
    bus->PostMessage( SYSTEM_CORE_ENGINE, Message( SYSTEM_MESSAGE_BUS, MESSAGE_CORE_ENGINE_START ) );
}







