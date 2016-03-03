//
//  cubemapTexture.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/17/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "cubemapTexture.h"

#include "stb_image.h"
#include "utility.h"

static const GLenum s_types[ 6 ] {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

CubeMapTexture::CubeMapTexture( const std::string &directory,
                               const std::string &posX,
                               const std::string &negX,
                               const std::string &posY,
                               const std::string &negY,
                               const std::string &posZ,
                               const std::string &negZ ) {
    std::string::const_iterator it = directory.end();
    it--;
    std::string baseDir = ( *it == '/' ) ? directory : directory + "/";
    
    m_filenames[ 0 ] = baseDir + posX;
    m_filenames[ 1 ] = baseDir + negX;
    m_filenames[ 2 ] = baseDir + posY;
    m_filenames[ 3 ] = baseDir + negY;
    m_filenames[ 4 ] = baseDir + posZ;
    m_filenames[ 5 ] = baseDir + negZ;
    
    m_textureObj = 0;
}

CubeMapTexture::~CubeMapTexture() {
    if ( m_textureObj != 0 ) {
        glDeleteTextures( 1, &m_textureObj );
    }
}

bool CubeMapTexture::Load() {
    glGenTextures( 1, &m_textureObj );
    glBindTexture( GL_TEXTURE_CUBE_MAP, m_textureObj );
    
    for ( unsigned int i = 0; i < 6; i++ ) {
        int width;
        int height;
        int numComponenets;
        unsigned char *data = stbi_load( ( Utility::DirectoryPath() + "textures/skyboxes" + m_filenames[ i ] ).c_str(), &width, &height, &numComponenets, 4 );
        
        if ( data == NULL ) {
            fprintf( stderr, "Error loading image %s\n", m_filenames[ i ].c_str() );
            return false;
        }
        
        glTexImage2D( s_types[ i ], 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        
        stbi_image_free( data );
    }
    
    return true;
}

void CubeMapTexture::Bind( GLenum textureUnit ) {
    glActiveTexture( textureUnit );
    glBindTexture( GL_TEXTURE_CUBE_MAP, m_textureObj );
}






