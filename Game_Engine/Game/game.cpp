//
//  game.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "game.h"

Game::Game() {
    m_root = new Entity();
}

Game::~Game() {
    if ( m_root != 0 ) {
        delete m_root;
        m_root = 0;
    }
}

void Game::Init() {
    
}

void Game::AddToScene( Entity *p_entity ) {
    m_root->AddChild( p_entity );
}

void Game::SetCamera( Entity *p_camera ) {
    m_root->AddChild( p_camera );
    m_camera = p_camera;
}
