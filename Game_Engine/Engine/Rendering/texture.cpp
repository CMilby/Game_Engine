//
//  texture.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "texture.h"

#include <fstream>

#include <dirent.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "file_utility.h"
#include "stb_image.h"
#include "string_utility.h"
#include "texture_resource.h"

GLuint Texture::s_lastBind = 0;

Texture::Texture( const std::string &p_file ) {
    if ( TextureResource::ContainsTexture( p_file ) ) {
        m_id = TextureResource::GetTexture( p_file );
        return;
    }
    
    std::ifstream fin;
    std::string dir = FileUtility::GetTextureDirectory() + p_file;
    std::string filepath;
    
    DIR *dp;
    
    struct dirent *dirp;
    struct stat filestat;
    
    int x;
    int y;
    int numComponenets;
    unsigned char *data;
    
    dp = opendir( dir.c_str() );
    if ( dp == NULL ) {
        data = stbi_load( ( FileUtility::GetTextureDirectory() + p_file ).c_str(), &x, &y, &numComponenets, 4 );
        
        if ( data == NULL ) {
            fprintf( stderr, ( "Error loading image\n" ) );
            return;
        }
        
        InitTexture( x, y, data, GL_TEXTURE_2D, GL_LINEAR );
        stbi_image_free( data );
        
        TextureResource::AddTexture( p_file, m_id );
    } else {
        int numTextures = 0;
        
        int width = 64;
        int height = 64;
        
        bool read = true;
        
        while ( ( dirp = readdir( dp ) ) ) {
            filepath = dir + "/" + dirp->d_name;
            
            if ( stat( filepath.c_str(), &filestat ) ) {
                continue;
            }
            
            if ( S_ISDIR( filestat.st_mode ) ) {
                continue;
            }
            
            if ( !StringUtility::EndsWith( filepath, ".png" ) ) {
                continue;
            }
            
            if ( read ) {
                data = stbi_load( filepath.c_str(), &x, &y, &numComponenets, 4 );
                stbi_image_free( data );
                
                width = x;
                height = y;
                
                read = false;
            }
            
            numTextures++;
        }
        
        closedir( dp );
        dp = opendir( dir.c_str() );
        
        glGenTextures( 1, &m_id );
        glBindTexture( GL_TEXTURE_2D_ARRAY, m_id );
        glTexStorage3D( GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, numTextures );
        
        int layer = 0;
        while ( ( dirp = readdir( dp ) ) ) {
            filepath = dir + "/" + dirp->d_name;
            
            if ( stat( filepath.c_str(), &filestat ) ) {
                continue;
            }
            
            if ( S_ISDIR( filestat.st_mode ) ) {
                continue;
            }
            
            if ( !StringUtility::EndsWith( filepath, ".png" ) ) {
                continue;
            }
            
            data = stbi_load( filepath.c_str(), &x, &y, &numComponenets, 4 );
            glTexSubImage3D( GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data );
            stbi_image_free( data );
            
            std::string myName = filepath.substr( StringUtility::LastIndexOf( filepath, '/' ) + 1 );
            myName = StringUtility::ToUpper( myName.substr( 0, myName.length() - 4 ) );
            ArrayTextureResource::AddTexture( myName, layer );
            
            layer++;
        }
        
        closedir( dp );
        
        glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        
        TextureResource::AddTexture( p_file, m_id );
    }
}

Texture::Texture( unsigned int p_width, unsigned int p_height, float p_data[] ) {
    glGenTextures( 1, &m_id );
    glBindTexture( GL_TEXTURE_2D, m_id );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, p_width, p_height, 0, GL_RGBA, GL_FLOAT, p_data );
}

Texture::~Texture() {
    if ( m_id != 0 ) {
        glDeleteTextures( 1, &m_id );
    }
}

void Texture::Bind( GLenum p_textureUint, GLenum p_textureType ) const {
    if ( s_lastBind != m_id ) {
        glActiveTexture( p_textureUint );
        glBindTexture( p_textureType, m_id );
        s_lastBind = m_id;
    }
}

void Texture::InitTexture( int p_width, int p_height, unsigned char *p_data, GLenum p_textureTarget, GLfloat p_filter ) {
    if ( p_width > 0 && p_height > 0 ) {
        glGenTextures( 1, &m_id );
        glBindTexture( p_textureTarget, m_id );
        glTexParameterf( p_textureTarget, GL_TEXTURE_MIN_FILTER, p_filter );
        glTexParameterf( p_textureTarget, GL_TEXTURE_MAG_FILTER, p_filter );
        glTexImage2D( p_textureTarget, 0, GL_RGBA, p_width, p_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_data );
    } else {
        m_id = 0;
    }
}








