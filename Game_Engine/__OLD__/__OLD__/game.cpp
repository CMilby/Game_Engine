//
//  game.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/27/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "game.h"

void Game::Init() {
    srand( ( unsigned int ) time( 0 ) );
    
    m_root.InitAll();
}

void Game::ProcessInput( float delta ) {
    m_root.InputAll( delta );
}

void Game::ProcessUpdate( float delta ) {
    m_root.UpdateAll( delta );
}

void Game::ProcessRender( RenderingEngine *renderingEngine ) {
    renderingEngine->Render( m_root );
}