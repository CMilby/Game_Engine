//
//  system_resource.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "system_resource.h"

std::unordered_map<ComponentType::ComponentType, System*, EnumHash> SystemResource::s_systems = std::unordered_map<ComponentType::ComponentType, System*, EnumHash>();
