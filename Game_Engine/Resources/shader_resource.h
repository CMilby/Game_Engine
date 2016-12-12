//
//  shader_resource.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SHADER_RESOURCE_H__
#define __SHADER_RESOURCE_H__

#include "hash_utility.h"
#include "shader.h"

class ShaderResource {
    
private:
    static std::unordered_map<ShaderType::ShaderType, Shader*, EnumHash> s_shaders;
    
public:
    static Shader* GetShader( ShaderType::ShaderType p_type ) {
        return s_shaders.at( p_type );
    }
    
    static void AddShader( Shader *p_shader ) {
        s_shaders.insert( std::pair<ShaderType::ShaderType, Shader*>( p_shader->GetType(), p_shader ) );
    }
    
    static void AddShader( Shader *p_shader, ShaderType::ShaderType p_type ) {
        s_shaders.insert( std::pair<ShaderType::ShaderType, Shader*>( p_type, p_shader ) );
    }
    
    static void InitShaders() {
        for ( auto const &s : s_shaders ) {
            s.second->Init();
        }
    }
};

#endif /* shader_resource_h */
