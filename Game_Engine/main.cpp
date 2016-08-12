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
#include "physicsEngineSystem.h"
#include "renderingSystem.h"
#include "windowSystem.h"

// Load Systems
#include "config.h"
#include "configLoader.h"

// Game
#include "cameraEntity.h"
#include "game.h"

int main( int argc, const char *argv[] ) {
	ConfigLoader::GetInstance().LoadConfigFile();
	MessageBus *bus = MessageBus::GetInstance();
    
    CoreEngineSystem *coreEngine = new CoreEngineSystem();
    RenderingSystem *renderingEngine = new RenderingSystem();
	PhysicsEngineSystem *physicsEngine = new PhysicsEngineSystem();
	WindowSystem *window = new WindowSystem( "Game" );
    InputSystem *input = InputSystem::GetInstance();
    EntitySystem *entity = new EntitySystem();
	CameraSystem *camera = new CameraSystem( new CameraEntity( Vector3<float>( 0, 0, 20 ) ) );
	GameSystem *game = new Game();
    
    bus->AddSystem( coreEngine );
    bus->AddSystem( renderingEngine );
	bus->AddSystem( physicsEngine );
    bus->AddSystem( window );
    bus->AddSystem( input );
    bus->AddSystem( game );
    bus->AddSystem( entity );
    bus->AddSystem( camera );
	
    bus->Init();
    bus->PostMessage( SYSTEM_CORE_ENGINE, Message( SYSTEM_MESSAGE_BUS, MESSAGE_CORE_ENGINE_START ) );
}







