//
//  game.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/27/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "game.h"

void Game::ProcessInput() const {
    m_renderRoot.InputAll();
}

void Game::ProcessUpdate() const {
    m_renderRoot.UpdateAll();
}

void Game::ProcessRender( RenderingEngine *renderingEngine ) const {
    renderingEngine->Render( m_renderRoot );
}