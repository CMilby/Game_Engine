//
//  planet.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "planet.h"

Planet::Planet() {
    m_radius = 5.0f;
    
    Terrain *terrain;
    
    terrain = new Terrain( "cube_top.obj", m_radius, 1, 1.0f, true, false, true );
    // terrain->SetPosition( Vector3<float>( 0.0f, 1.0f, 0.0f ) );
    // terrain->SetScale( Vector3<float>( m_radius, m_radius, m_radius ) );
    AddChild( terrain );
    
    terrain = new Terrain( "cube_bottom.obj", m_radius, 1, -1.0f, true, false, true );
    // terrain->SetPosition( Vector3<float>( 0.0f, -1.0f, 0.0f ) );
    // terrain->GetTransform()->Rotate( Vector3<float>( 1.0f, 0.0f, 0.0f ), 180.0f );
    // terrain->SetScale( Vector3<float>( m_radius, m_radius, m_radius ) );
    AddChild( terrain );
    
    terrain = new Terrain( "cube_front.obj", m_radius, 1, 1.0f, true, true, false );
    // terrain->SetPosition( Vector3<float>( 0.0f, 0.0f, 1.0f ) );
    // terrain->GetTransform()->Rotate( Vector3<float>( 1.0f, 0.0f, 0.0f ), 90.0f );
    // terrain->SetScale( Vector3<float>( m_radius, m_radius, m_radius ) );
    AddChild( terrain );
    
    terrain = new Terrain( "cube_back.obj", m_radius, 1, -1.0f, true, true, false );
    // terrain->SetPosition( Vector3<float>( 0.0f, 0.0f, -1.0f ) );
    // terrain->GetTransform()->Rotate( Vector3<float>( 1.0f, 0.0f, 0.0f ), 270.0f );
    // terrain->SetScale( Vector3<float>( m_radius, m_radius, m_radius ) );
    AddChild( terrain );
    
    terrain = new Terrain( "cube_left.obj", m_radius, 1, -1.0f, false, true, true );
    // terrain->SetPosition( Vector3<float>( 1.0f, 0.0f, 0.0f ) );
    // terrain->GetTransform()->Rotate( Vector3<float>( 0.0f, 0.0f, 1.0f ), 90.0f );
    // terrain->SetScale( Vector3<float>( m_radius, m_radius, m_radius ) );
    AddChild( terrain );
    
    terrain = new Terrain( "cube_right.obj", m_radius, 1, 1.0f, false, true, true );
    // terrain->SetPosition( Vector3<float>( -1.0f, 0.0f, 0.0f ) );
    // terrain->GetTransform()->Rotate( Vector3<float>( 0.0f, 0.0f, 1.0f ), 270.0f );
    // terrain->SetScale( Vector3<float>( m_radius, m_radius, m_radius ) );*/
    AddChild( terrain );
}

Planet::~Planet() {
    
}

void Planet::Render() {
    
}










