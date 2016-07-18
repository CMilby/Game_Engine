//
//  tileMap.h
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__

#include <map>
#include <string>

#include "tileType.h"

class TileMap {
	
private:
	static std::map<std::string, int> s_tileMap;
	static std::map<TileType, std::string> s_tileTypeMap;
	
	TileMap() {}
	
protected:
	static void PopulateTileTypeMap() {
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_GRASS, "GRASS" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_RAINFOREST, "RAINFOREST" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_SAND, "SAND" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_SAVANAH, "SAVANAH" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_SNOW, "SNOW" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_STONE, "STONE" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_SWAMP, "SWAMP" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_TAIGA, "TAIGA" ) );
		s_tileTypeMap.insert( std::pair<TileType, std::string>( TileType::TILE_WATER, "WATER" ) );
	}
	
public:
	static void Init() {
		PopulateTileTypeMap();
	}
	
	static void AddTile( const std::string &pKey, int pValue ) {
		s_tileMap.insert( std::pair<std::string, int>( pKey, pValue ) );
	}
	
	static int GetTile( const std::string &pKey ) {
		return s_tileMap[ pKey ];
	}
	
	static int GetTile( const TileType &pTileType ) {
		return GetTile( s_tileTypeMap[ pTileType ] );
	}
};

#endif /* tileMap_h */
