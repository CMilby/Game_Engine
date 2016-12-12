//
//  shader_resource.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "shader_resource.h"

std::unordered_map<ShaderType::ShaderType, Shader*, EnumHash> ShaderResource::s_shaders = std::unordered_map<ShaderType::ShaderType, Shader*, EnumHash>();
