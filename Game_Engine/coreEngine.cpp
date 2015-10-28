//
//  coreEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "coreEngine.h"

#include "time.h"

CoreEngine::CoreEngine( Window *window, Game *game ) {
    m_window = window;
    m_game = game;
    
    m_renderingEngine = new RenderingEngine();
    m_text2d = new Text2D( "Holstein.DDS" );
    
    m_isRunning = false;
}

CoreEngine::~CoreEngine() {
    if ( m_renderingEngine ) delete m_renderingEngine;
    if ( m_text2d ) delete m_text2d;
}

void CoreEngine::Init() {
    m_renderingEngine->Init();
    m_text2d->Init();
    m_game->Init();
}

void CoreEngine::Start() {
    if ( m_isRunning ) {
        return;
    }
    
    m_isRunning = true;
    
    float lastTime = Timing::GetTime();
    float currentTime = lastTime;
    int frames = 0;
    
    char lastFPM[ 256 ];
    sprintf( lastFPM, "0.00 ms/frame" );
    
    while ( m_isRunning ) {
        currentTime = Timing::GetTime();
        frames++;
        if ( currentTime - lastTime >= 1.0f ) {
            sprintf( lastFPM, "%.2f ms/frame", 1000.0f / ( float ) frames );
            frames = 0;
            lastTime += 1.0f;
        }
        
        m_window->PollEvents();
        
        if ( m_window->ShouldClose() || Input::IsKeyDown( Input::KEY_ESCAPE ) ) {
            Stop();
        }
        
        m_game->ProcessInput( currentTime - lastTime );
        m_game->ProcessUpdate( currentTime - lastTime );
        m_game->ProcessRender( m_renderingEngine );
        
        m_text2d->PrintText2D( lastFPM, 5, 5, 20 );
        
        m_window->SwapBuffers();
    }
}

void CoreEngine::Stop() {
    if ( !m_isRunning ) {
        return;
    }
    
    m_isRunning = false;
}