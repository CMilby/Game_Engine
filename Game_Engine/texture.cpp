//
//  texture.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "texture.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "utility.h"

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

Texture* Texture::s_lastBind = 0;

Texture::Texture( int width, int height, unsigned char *data, GLenum textureTarget, GLfloat filter ) {
    InitTexture( width, height, data, textureTarget, filter );
}

Texture::Texture( const std::string &file, TextureType type ) {
    m_type = type;
    
    if ( type == TextureType::TYPE_PNG ) {
        int x;
        int y;
        int numComponenets;
        unsigned char *data = stbi_load( ( Utility::DirectoryPath() + "textures/" + file ).c_str(), &x, &y, &numComponenets, 4 );
        
        if ( data == NULL ) {
            fprintf( stderr, ( "Error loading image\n" ) );
            return;
        }
        
        InitTexture( x, y, data, GL_TEXTURE_2D, GL_LINEAR );
        stbi_image_free( data );
    } else if ( type == TextureType::TYPE_DDS ) {
        m_textureID = LoadDDS( ( Utility::DirectoryPath() + "textures/" + file ).c_str() );
        m_freeTexture = true;
    }
}

void Texture::InitTexture( int width, int height, unsigned char *data, GLenum textureTarget, GLfloat filter ) {
    m_textureTarget = textureTarget;
    m_freeTexture = true;
    
    if ( width > 0 && height > 0 ) {
        glGenTextures( 1, &m_textureID );
        glBindTexture( textureTarget, m_textureID );
        glTexParameterf( textureTarget, GL_TEXTURE_MIN_FILTER, filter );
        glTexParameterf( textureTarget, GL_TEXTURE_MAG_FILTER, filter );
        glTexImage2D( textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
    } else {
        m_textureID = 0;
    }
}

Texture::~Texture() {
    if ( m_freeTexture ) {
        glDeleteTextures( 1, &m_textureID );
    }
}

void Texture::Bind( GLenum textureUnit ) const {
    if ( s_lastBind != this ) {
        if ( m_type == TYPE_PNG ) {
            glActiveTexture( textureUnit );
            glBindTexture( m_textureTarget, m_textureID );
        } else if ( m_type == TYPE_DDS ) {
            glActiveTexture( GL_TEXTURE0 );
            glBindTexture( GL_TEXTURE_2D, m_textureID );
        }
    }
}

GLuint Texture::LoadDDS( const std::string &filename ) {
    unsigned char header[ 124 ];
    
    FILE *fp;
    fp = fopen( filename.c_str(), "rb" );
    if ( fp == NULL ) {
        printf( "%s could not be opened\n", filename.c_str() );
        getchar();
        return 0;
    }
    
    char filecode[ 4 ];
    fread( filecode, 1, 4, fp );
    if ( strncmp( filecode, "DDS ", 4) != 0 ) {
        fclose( fp );
        return 0;
    }
    
    fread( &header, 124, 1, fp );
    
    unsigned int height = *( unsigned int* ) &header[ 8 ];
    unsigned int width = *( unsigned int* ) &header[ 12 ];
    unsigned int linearSize = *( unsigned int* ) & header[ 16 ];
    unsigned int mipMapCount = *( unsigned int* ) &header[ 24 ];
    unsigned int fourCC = *( unsigned int* ) &header[ 80 ];
    
    unsigned char *buffer;
    unsigned int bufSize;
    bufSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = ( unsigned char* ) malloc( bufSize * sizeof( unsigned char ) );
    fread( buffer, 1, bufSize, fp );
    fclose( fp );
    
    // unsigned int components = ( fourCC == FOURCC_DXT1 ) ? 3 : 4;
    unsigned int format;
    
    switch ( fourCC ) {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free( buffer );
            return 0;
    }
    
    GLuint textureID;
    glGenTextures( 1, &textureID );
    
    glBindTexture( GL_TEXTURE_2D, textureID );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    
    unsigned int blockSize = ( format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;
    
    for ( unsigned int level = 0; level < mipMapCount && ( width || height ); level++ ) {
        unsigned int size = ( ( width + 3 ) / 4 ) * ( ( height + 3 ) / 4 ) * blockSize;
        glCompressedTexImage2D( GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset );
        
        offset += size;
        width /= 2;
        height /= 2;
        
        if ( width < 1 ) width = 1;
        if ( height < 1 ) height = 1;
    }
    
    free( buffer );
    return textureID;
}

GLuint Texture::LoadTGA( const std::string &filename ) {
    GLuint textureID;
    glGenTextures( 1, &textureID );
    
    glBindTexture( GL_TEXTURE_2D, textureID );
    return 0;
}

Texture::Texture( Texture &texture ) {
    m_textureTarget = texture.m_textureTarget;
    m_textureID = texture.m_textureID;
    m_freeTexture = true;
    texture.m_freeTexture = false;
}

void Texture::operator=( Texture &texture ) {
    m_textureTarget = texture.m_textureTarget;
    m_textureID = texture.m_textureID;
    m_freeTexture = true;
    texture.m_freeTexture = false;
}










