//
//  tileMap.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "tileMap.h"

std::map<std::string, int> TileMap::s_tileMap = std::map<std::string, int>();
std::map<TileType, std::string> TileMap::s_tileTypeMap = std::map<TileType, std::string>();