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

enum TILE_TYPE {
	TILE_GRASS,
	TILE_WATER,
	NUM_TILES
};

class TileMap {
	
private:
	static TileMap *s_instance;
	static std::map<std::string, int> s_tileMap;
	
	TileMap() {}
public:
	static TileMap* GetInstance() {
		if ( !s_instance ) {
			s_instance = new TileMap();
		}
		return s_instance;
	}
	
	static void AddTile( const std::string &pKey, int pValue ) {
		s_tileMap[ pKey ] = pValue;
	}
	
	static int GetTile( const std::string &pKey ) {
		return s_tileMap[ pKey ];
	}
};

#endif /* tileMap_h */
