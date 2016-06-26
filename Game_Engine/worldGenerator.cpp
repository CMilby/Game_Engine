//
//  worldGenerator.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "worldGenerator.h"

#include <iostream>

#include "simplexNoise.h"
#include "tileMap.h"

WorldGenerator* WorldGenerator::s_instance = new WorldGenerator();

void WorldGenerator::Init() {
	TileMap::Init();
	
	m_land.SetSeed( 0 );
	m_temperature.SetSeed( 1 );
	m_rainfall.SetSeed( 2 );
}

int WorldGenerator::GenerateTile( int pX, int pY ) {
	float myNoise = m_land.OctaveNoise2D( 3, 0.4f, 0.005f, pX, pY );
	if ( myNoise < 0.0 ) {
		return TileMap::GetTile( TileType::TILE_WATER );
	} else {
		return TileMap::GetTile( TileType::TILE_GRASS );
	}
	return 0;
}