//
//  texture_resource.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "texture_resource.h"

std::unordered_map<std::string, GLuint> TextureResource::s_textures = std::unordered_map<std::string, GLuint>();
std::unordered_map<std::string, unsigned int> ArrayTextureResource::s_textures = std::unordered_map<std::string, unsigned int>();
