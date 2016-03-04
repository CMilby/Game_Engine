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
	AddToScene( new RenderableEntity( new Mesh( "cube.obj" ) ) );
}