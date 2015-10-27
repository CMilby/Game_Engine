//
//  coreEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "coreEngine.h"

#include "time.h"

CoreEngine::CoreEngine( Window *window, Input *input ) {
    m_window = window;
    m_input = input;
    
    m_renderingEngine = new RenderingEngine();
    m_text2d = new Text2D( "Holstein.DDS" );
}

CoreEngine::~CoreEngine() {
    if ( m_window ) delete m_window;
    if ( m_renderingEngine ) delete m_renderingEngine;
    if ( m_input ) delete m_input;
}

void CoreEngine::Init() {
    m_renderingEngine->Init();
    m_text2d->Init();
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
        
        if ( m_window->ShouldClose() && m_input->IsKeyDown( Input::KEY_ESCAPE ) ) {
            Stop();
        }
        
        m_renderingEngine->Render();
        m_text2d->PrintText2D( lastFPM, 5, 5, 20 );
        
        m_window->SwapBuffers();
        m_window->PollEvents();
    }
}

void CoreEngine::Stop() {
    if ( !m_isRunning ) {
        return;
    }
    
    m_isRunning = false;
}