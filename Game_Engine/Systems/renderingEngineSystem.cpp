//
//  renderingEngineSystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderingEngineSystem.h"

#include "renderFramework.h"

RenderingEngineSystem::RenderingEngineSystem() : System( SYSTEM_RENDERING_ENGINE ) {
    
}

void RenderingEngineSystem::Init() {
    System::Init();
    
    RenderFramework::InitRenderer();
}

void RenderingEngineSystem::Update() {
    
}

void RenderingEngineSystem::Render() {
    RenderFramework::ClearScreen();
    
    SendMessage( SYSTEM_ENTITY, Message( SYSTEM_RENDERING_ENGINE, MESSAGE_RENDER ) );
}

void RenderingEngineSystem::HandleUpdate( const std::vector<MessagePayload> &payload ) {
    System::HandleUpdate( payload );
    
    Render();
}
