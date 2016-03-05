//
//  testGame.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "testGame.h"

#include "renderableEntity.h"

TestGame::TestGame() {
	
}

void TestGame::LoadGame() {
	RenderableEntity *cube = new RenderableEntity( "cube.obj" );
	cube->SetPosition( Vector3<float>( 1.0f, 2.0f, 1.0f ) );
	
	RenderableEntity *plane = new RenderableEntity( "plane.obj" );
	
	RenderableEntity *jeep = new RenderableEntity( "jeep.obj", "jeep_army.png" );
	jeep->SetScale( Vector3<float>( 0.01f, 0.01f, 0.01f ) );
	jeep->SetPosition( Vector3<float>( -4.0f, 0.0f, -5.0f ) );
	
	AddToScene( cube );
	AddToScene( plane );
	AddToScene( jeep );
}