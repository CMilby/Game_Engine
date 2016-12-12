//
//  core_engine.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "core_engine.h"

#include "input.h"

#include "system_resource.h"

#include "input_system.h"
#include "render_system.h"
#include "update_system.h"

CoreEngine::CoreEngine( Window *p_window, Game *p_game ) : m_window( p_window ), m_game( p_game ), m_mainCamera( 0 ) {
    m_isRunning = false;
}

CoreEngine::~CoreEngine() {
    
}

void CoreEngine::Init() {
    InputSystem *input = InputSystem::GetInstance();
    UpdateSystem *update = UpdateSystem::GetInstance();
    RenderSystem *render = RenderSystem::GetInstance();
    
    SystemResource::AddSystem( ComponentType::INPUT_COMPONENT, input );
    SystemResource::AddSystem( ComponentType::UPDATE_COMPONENT, update );
    SystemResource::AddSystem( ComponentType::RENDER_COMPONENT, render );
    SystemResource::Init();
    
    m_game->Init();
    m_mainCamera = m_game->GetCamera();
}

void CoreEngine::Start() {
    if ( m_isRunning ) {
        return;
    }
    
    m_isRunning = true;
    
    System *input = SystemResource::GetSystem( ComponentType::INPUT_COMPONENT );
    System *update = SystemResource::GetSystem( ComponentType::UPDATE_COMPONENT );
    System *render = SystemResource::GetSystem( ComponentType::RENDER_COMPONENT );
    
    while ( m_isRunning ) {
        input->Execute( 0.16f );
        if ( Input::IsWindowCloseRequested() || Input::IsKeyDown( Key::KEY_ESCAPE ) ) {
            break;
        }
        
        update->Execute( 0.16f );
        
        render->Execute( m_mainCamera );
        m_window->Update();
    }
}

void CoreEngine::Stop() {
    if ( !m_isRunning ) {
        return;
    }
    
    m_isRunning = false;
}
