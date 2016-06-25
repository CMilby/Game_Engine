//
//  testPlanet.cpp
//  Game_Engine
//
//  Created by Craig Milby on 5/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "testPlanet.h"

#include "testTerrain.h"

TestPlanet::TestPlanet( float pRadius, unsigned int pLoD ) {
	m_radius = pRadius;
	m_LoD = pLoD;
}

void TestPlanet::Init() {
	TestTerrain *terrain_front = new TestTerrain( "cube_front.obj", m_radius, m_LoD, 1, Vector3<bool>( true, true, false ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	terrain_front->SetPosition( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	// terrain_front->ColorizeTerrain();
	AddChild( terrain_front );
	
	RenderableEntity *terrain_back = new TestTerrain( "cube_back.obj", m_radius, m_LoD, 1, Vector3<bool>( true, true, false ), -1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	terrain_back->SetPosition( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	// AddChild( terrain_back );
	
	RenderableEntity *terrain_left = new TestTerrain( "cube_left.obj", m_radius, m_LoD, 1, Vector3<bool>( false, true, true ), -1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	terrain_left->SetPosition( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	// AddChild( terrain_left );
	
	TestTerrain *terrain_right = new TestTerrain( "cube_right.obj", m_radius, m_LoD, 1, Vector3<bool>( false, true, true ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	terrain_right->SetPosition( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	// terrain_right->ColorizeTerrain();
	// AddChild( terrain_right );
	
	RenderableEntity *terrain_top = new TestTerrain( "cube_top.obj", m_radius, m_LoD, 1, Vector3<bool>( true, false, true ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	terrain_top->SetPosition( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	// AddChild( terrain_top );
	
	RenderableEntity *terrain_bottom = new TestTerrain( "cube_bottom.obj", m_radius, m_LoD, 1, Vector3<bool>( true, false, true ), -1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ), 1.0f, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	terrain_bottom->SetPosition( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
	// AddChild( terrain_bottom );
}