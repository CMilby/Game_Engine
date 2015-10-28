//
//  game.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/27/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "game.h"

void Game::ProcessInput( float delta ) const {
    m_root.InputAll( delta );
}

void Game::ProcessUpdate( float delta ) const {
    m_root.UpdateAll( delta );
}

void Game::ProcessRender( RenderingEngine *renderingEngine ) const {
    renderingEngine->Render( m_root );
}