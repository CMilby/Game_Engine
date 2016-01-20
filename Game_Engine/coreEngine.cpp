//
//  coreEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "coreEngine.h"

#include "logging.h"
#include "time.h"

CoreEngine::CoreEngine( Window *window, Game *game ) {
    m_window = window;
    m_game = game;
    
    m_renderingEngine = new RenderingEngine();
    
    m_isRunning = false;
    m_profiler = new Profiler();
}

CoreEngine::~CoreEngine() {
    if ( m_renderingEngine ) delete m_renderingEngine;
    if ( m_textShader ) delete m_textShader;
}

void CoreEngine::Init() {
    m_renderingEngine->Init();
    
    m_textShader = new TextShader( "Courier_New.png" );
    m_textShader->Init();
    m_game->Init();
    
    m_window->SetFullscreen( true );
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
    
    const std::string function = "CoreEngine: Start";
    
    while ( m_isRunning ) {
        currentTime = Timing::GetTime();
        frames++;
        if ( currentTime - lastTime >= 1000.0f ) {
            sprintf( lastFPM, "%.2f ms/frame", 1000.0f / ( float ) frames );
            printf( "%i\n", frames );
            frames = 0;
            lastTime += 1000.0f;
        }

        Input::Update();
        
        if ( m_window->ShouldClose() || Input::IsKeyDown( Input::KEY_ESCAPE ) ) {
            Stop();
        }
        
        m_profiler->StartProfile();
        m_game->ProcessInput( currentTime - lastTime );
        m_profiler->StopProfile();
        m_profiler->Profile( function, "Game Input:" );
        
        m_profiler->StartProfile();
        m_game->ProcessUpdate( currentTime - lastTime );
        m_profiler->StopProfile();
        m_profiler->Profile( function, "Game Update:" );
        
        m_profiler->StartProfile();
        m_game->ProcessRender( m_renderingEngine );
        m_profiler->StopProfile();
        m_profiler->Profile( function, "Game Render:" );
        
        m_profiler->StartProfile();
        m_textShader->Render( lastFPM, 5, 5, 20 );
        m_profiler->StopProfile();
        m_profiler->Profile( function, "Text Shader:" );
        
        m_profiler->StartProfile();
        m_window->SwapBuffers();
        m_profiler->StopProfile();
        m_profiler->Profile( function, "Swap Buffers:" );
        std::cout << std::endl;
    }
}

void CoreEngine::Stop() {
    if ( !m_isRunning ) {
        return;
    }
    
    m_isRunning = false;
}