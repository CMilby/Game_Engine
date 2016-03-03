//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>

#include "cameraSystem.h"
#include "coreEngineSystem.h"
#include "entitySystem.h"
#include "gameSystem.h"
#include "inputSystem.h"
#include "messageBus.h"
#include "renderingEngineSystem.h"
#include "windowSystem.h"

int main( int argc, const char *argv[] ) {
    MessageBus *bus = MessageBus::GetInstance();
    
    CoreEngineSystem *coreEngine = new CoreEngineSystem();
    RenderingEngineSystem *renderingEngine = new RenderingEngineSystem();
    WindowSystem *window = new WindowSystem( 800, 768, "Game" );
    InputSystem *input = InputSystem::GetInstance();
    GameSystem *game = new GameSystem();
    EntitySystem *entity = new EntitySystem();
    CameraSystem *camera = new CameraSystem();
    
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







