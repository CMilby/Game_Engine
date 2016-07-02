//
//  texture.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "texture.h"

#include <fstream>
#include <iostream>
#include <vector>

#include <dirent.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "tileMap.h"
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
        m_freeTexture = false;
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
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, data );
}

Texture::Texture( int pNumTextures, const std::string &pDirectory, int pWidth, int pHeight ) {
	if ( s_textureAtlas->Contains( pDirectory ) ) {
		m_freeTexture = false;
		m_textureID = s_textureAtlas->Get( pDirectory );
		return;
	}
	
	std::ifstream fin;
	std::string dir = Utility::DirectoryPath() + "textures/" + pDirectory;
	std::string filepath;
	
	DIR *dp;
	
	struct dirent *dirp;
	struct stat filestat;
	
	dp = opendir( dir.c_str() );
	if ( dp == NULL ) {
		std::cout << "Error: Could not open directory: " << dir << std::endl;
		exit( 1 );
	}
	
	// GLsizei width = 512;
	// GLsizei height = 512;
	
	int x = 0;
	int y = 0;
	int numComponenets;
	unsigned char *data;
	
	glGenTextures( 1, &m_textureID );
	glBindTexture( GL_TEXTURE_2D_ARRAY, m_textureID );
	glTexStorage3D( GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, pWidth, pHeight, pNumTextures );
	
	int i = 0;
	while ( ( dirp = readdir( dp ) ) ) {
		filepath = dir + "/" + dirp->d_name;
		
		if ( stat( filepath.c_str(), &filestat ) ) {
			continue;
		}
		
		if ( S_ISDIR( filestat.st_mode ) ) {
			continue;
		}
		
		if ( !Utility::EndsWith( filepath, ".png" ) ) {
			continue;
		}
		
		data = stbi_load( filepath.c_str(), &x, &y, &numComponenets, 4 );
		glTexSubImage3D( GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, pWidth, pHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, data );
		stbi_image_free( data );
		
		std::string myName = filepath.substr( Utility::LastIndexOf( filepath, '/' ) + 1 );
		myName = Utility::ToUpper( myName.substr( 0, myName.length() - 4 ) );
		TileMap::AddTile( myName, i );
		
		i++;
	}
	
	closedir( dp );
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	s_textureAtlas->Add( pDirectory, m_textureID );
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

void Texture::Bind( GLenum pTextureUnit, GLenum pTextureType ) const {
    if ( s_lastBind != m_textureID ) {
        glActiveTexture( pTextureUnit );
        glBindTexture( pTextureType, m_textureID );
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







