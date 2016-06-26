//
//  worldGenerator.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "worldGenerator.h"

#include <iostream>

#include "math3d.h"
#include "simplexNoise.h"
#include "tileMap.h"

WorldGenerator* WorldGenerator::s_instance = new WorldGenerator();

void WorldGenerator::Init() {
	TileMap::Init();
	
	m_elevation.SetSeed( 41023221 );
	m_temperature.SetSeed( 3213321 );
	m_rainfall.SetSeed( 5121231 );
}

int WorldGenerator::GenerateTile( int pX, int pY ) {
	float elevation = m_elevation.OctaveNoise2D( 4, 0.4f, 0.005f, pX, pY );
	float temperature = m_temperature.OctaveNoise2D( 4, 0.4f, 0.005f, pX, pY );
	float rainfall = m_rainfall.OctaveNoise2D( 4, 0.4f, 0.005f, pX, pY );
	
	elevation = Math3D::Scale( elevation, 0.0f, 1.0f, -1.0f, 1.0f );
	
	if ( elevation < 0.3f ) {
		return TileMap::GetTile( TileType::TILE_WATER );
	} else if ( elevation < 0.32 ) {
		return TileMap::GetTile( TileType::TILE_SAND );
	} else if ( elevation > 0.7f ) {
		return  TileMap::GetTile( TileType::TILE_STONE );
	}
	
	rainfall = Math3D::Scale( rainfall, 0.0f, 1.0f, -1.0f, 1.0f );
	
	if ( rainfall >= 0.75 ) {
		temperature = Math3D::Scale( temperature, 0.5f, 1.0f, -1.0f, 1.0f );
		if ( temperature >= 0.75f ) {
			// Rainforest
			return TileMap::GetTile( TileType::TILE_RAINFOREST );
		} else {
			// Swamp
			return TileMap::GetTile( TileType::TILE_SWAMP );
		}
	} else if ( rainfall >= 0.5f ) {
		temperature = Math3D::Scale( temperature, 0.25f, 1.0f, -1.0f, 1.0f );
		if ( temperature >= 0.75f ) {
			// Seasonal forest
			return TileMap::GetTile( TileType::TILE_GRASS );
		} else if ( temperature >= 0.5f ) {
			// Forest
			return TileMap::GetTile( TileType::TILE_GRASS );
		} else {
			// Taiga
			return TileMap::GetTile( TileType::TILE_TAIGA );
		}
	} else if ( rainfall >= 0.25f ) {
		temperature = Math3D::Scale( temperature, 0.25f, 1.0f, -1.0f, 1.0f );
		if ( temperature >= 0.75f ) {
			// Savanah
			return TileMap::GetTile( TileType::TILE_SAVANAH );
		} else if ( temperature >= 0.5f ) {
			// Woods
			return TileMap::GetTile( TileType::TILE_GRASS );
		} else {
			// Taiga
			return TileMap::GetTile( TileType::TILE_TAIGA );
		}
	} else {
		temperature = Math3D::Scale( temperature, 0.0f, 1.0f, -1.0f, 1.0f );
		if ( temperature >= 0.625 ) {
			// desert
			return TileMap::GetTile( TileType::TILE_SAND );
		} else if ( temperature >= 0.25 ) {
			// Grass desert
			return TileMap::GetTile( TileType::TILE_SAND );
		} else {
			// Tundra
			return TileMap::GetTile( TileType::TILE_SNOW );
		}
	}
	
	return TileMap::GetTile( TileType::TILE_STONE );
}








