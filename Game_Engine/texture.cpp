//
//  texture.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "texture.h"

#include <cstdio>
#include <cstdlib>

#include <GLFW/glfw3.h>

#include "utility.h"

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

Texture::Texture( const std::string &filename ) {
    m_texture = LoadDDS( Utility::DirectoryPath() + "textures/" + filename );
}

Texture::~Texture() {
    glDeleteTextures( 1, &m_texture );
}

void Texture::Bind() const {
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_texture );
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











