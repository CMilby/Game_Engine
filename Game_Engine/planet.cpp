//
//  planet.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "planet.h"

Planet::Planet( float radius ) {
    m_radius = radius;
    Terrain *terrain;
    
    // terrain = new Terrain( "cube_top_128.obj", m_radius, 1, 1.0f, true, false, true );
    // AddChild( terrain );
    
    // terrain = new Terrain( "cube_bottom_128.obj", m_radius, 1, -1.0f, true, false, true );
    // AddChild( terrain );
    
    terrain = new Terrain( "cube_front.obj", m_radius, 1, 1.0f, true, true, false );
    AddChild( terrain );
    
    // terrain = new Terrain( "cube_back.obj", m_radius, 1, -1.0f, true, true, false );
    // AddChild( terrain );
    
    // terrain = new Terrain( "cube_left.obj", m_radius, 1, -1.0f, false, true, true );
    // AddChild( terrain );
    
    // terrain = new Terrain( "cube_right.obj", m_radius, 1, 1.0f, false, true, true );
    // AddChild( terrain );
}

Planet::~Planet() {
    
}

void Planet::Render() {
    
}










