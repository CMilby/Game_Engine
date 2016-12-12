//
//  texture_resource.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TEXTURE_RESOURCE_H__
#define __TEXTURE_RESOURCE_H__

#include <string>
#include <unordered_map>

#include <GL/glew.h>

class TextureResource {
    
private:
    static std::unordered_map<std::string, GLuint> s_textures;
    
    TextureResource();
    void operator=( const TextureResource &p_texResource );
    
public:
    static void AddTexture( const std::string &p_file, GLuint p_id ) {
        s_textures.insert( std::pair<std::string, GLuint>( p_file, p_id ) );
    }
    
    static GLuint GetTexture( const std::string &p_file ) {
        return s_textures.at( p_file );
    }
    
    static bool ContainsTexture( const std::string &p_file ) {
        return s_textures.count( p_file ) == 1;
    }
};

class ArrayTextureResource {
    
private:
    static std::unordered_map<std::string, unsigned int> s_textures;
    
public:
    static void AddTexture( const std::string &p_filename, unsigned int p_layer ) {
        s_textures.insert( std::pair<std::string, unsigned int>( p_filename, p_layer ) );
    }
    
    static unsigned int GetTexture( const std::string &p_filename ) {
        return s_textures.at( p_filename );
    }
};

#endif /* texture_resource_h */
