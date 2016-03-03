//
//  coreEngineSystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "coreEngineSystem.h"

#include "math3d.h"

CoreEngineSystem::CoreEngineSystem() : System( SYSTEM_CORE_ENGINE ) {
    m_frameRate = 60;
}

void CoreEngineSystem::Init() {
    System::Init();
    
    m_callbacks[ MESSAGE_CORE_ENGINE_START ] = std::bind( &CoreEngineSystem::HandleCoreEngineStart, this, std::placeholders::_1 );
    m_callbacks[ MESSAGE_CORE_ENGINE_STOP ] = std::bind( &CoreEngineSystem::HandleCoreEngineStop, this, std::placeholders::_1 );
}

void CoreEngineSystem::Update() {
    HandleMessages();
}

void CoreEngineSystem::HandleCoreEngineStart( const std::vector<MessagePayload>& payload ) {
    if ( m_isRunning ) {
        return;
    }
    
    m_isRunning = true;
 
    float dt = 1.0f / ( float ) m_frameRate;
    float currentTime = Timing::GetTimeMillis();
    
    while ( m_isRunning ) {
        float newTime = Timing::GetTimeMillis();
        float frameTime = newTime = currentTime;
        currentTime = newTime;
        
        while ( frameTime > 0.0f ) {
            float deltaTime = Math3D::Min( frameTime, dt );
            SendMessage( SYSTEM_INPUT, Message( SYSTEM_CORE_ENGINE, MESSAGE_UPDATE ) );
			SendMessage( SYSTEM_GAME, Message( SYSTEM_CORE_ENGINE, MESSAGE_INPUT ) );
            SendMessage( SYSTEM_GAME, Message( SYSTEM_CORE_ENGINE, MESSAGE_UPDATE ) );
            frameTime -= deltaTime;
        }
        
        SendMessage( SYSTEM_RENDERING_ENGINE, Message( SYSTEM_CORE_ENGINE, MESSAGE_RENDER ) );
        SendMessage( SYSTEM_WINDOW, Message( SYSTEM_CORE_ENGINE, MESSAGE_UPDATE ) );
    }
}

void CoreEngineSystem::HandleCoreEngineStop( const std::vector<MessagePayload>& payload ) {
    if ( !m_isRunning ) {
        return;
    }
    
    m_isRunning = false;
}










