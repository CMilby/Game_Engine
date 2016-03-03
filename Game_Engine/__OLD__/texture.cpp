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

#include "simplexNoise.h"
#include "stb_image.h"
#include "utility.h"

std::map<std::string, GLuint> TextureAtlas::s_textureAtlas = std::map<std::string, GLuint>();

GLuint Texture::s_lastBind = 0;
TextureAtlas* Texture::s_textureAtlas = new TextureAtlas();

TextureAtlas::TextureAtlas() {
    
}

TextureAtlas::~TextureAtlas() {
    
}

void TextureAtlas::Add( const std::string &name, GLuint value ) {
    s_textureAtlas.insert( std::pair<std::string, GLuint>( name, value ) );
}

bool TextureAtlas::Contains( const std::string &name ) const {
    return s_textureAtlas.count( name ) == 1;
}

GLuint TextureAtlas::Get( const std::string &name ) const {
    return s_textureAtlas[ name ];
}

void TextureAtlas::Remove( const std::string &name ) {
    s_textureAtlas.erase( name );
}

Texture::Texture( int width, int height, unsigned char *data, GLenum textureTarget, GLfloat filter ) {
    InitTexture( width, height, data, textureTarget, filter );
}

Texture::Texture( const std::string &file ) {
    if ( s_textureAtlas->Contains( file ) ) {
        m_freeTexture = true;
        m_textureID = s_textureAtlas->Get( file );
    } else {
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
        
        s_textureAtlas->Add( file, m_textureID );
    }
}

Texture::Texture( int width, int height, float data[] ) {
    glGenTextures( 1, &m_textureID );
    glBindTexture( GL_TEXTURE_2D, m_textureID );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, data );
}

void Texture::InitTexture( int width, int height, unsigned char *data, GLenum textureTarget, GLfloat filter ) {
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
    if ( s_lastBind != m_textureID ) {
        glActiveTexture( textureUnit );
        glBindTexture( GL_TEXTURE_2D, m_textureID );
        s_lastBind = m_textureID;
    }
}

Texture::Texture( Texture &texture ) {
    m_textureID = texture.m_textureID;
    m_freeTexture = true;
    texture.m_freeTexture = false;
}

void Texture::operator=( Texture &texture ) {
    m_textureID = texture.m_textureID;
    m_freeTexture = true;
    texture.m_freeTexture = false;
}







