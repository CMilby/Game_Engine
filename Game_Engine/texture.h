//
//  texture.h
//  Game_Engine
//
//  Created by Craig Milby on 10/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <map>
#include <string>

#include <GL/glew.h>

class TextureAtlas {
    
private:
    static std::map<std::string, GLuint> s_textureAtlas;
    
public:
    TextureAtlas();
    virtual ~TextureAtlas();
    
    void Add( const std::string &name, GLuint value );
    
    bool Contains( const std::string &name ) const;
    GLuint Get( const std::string &name ) const;
    
    void Remove( const std::string &name );
};

class Texture {
    
private:
    static GLuint s_lastBind;
    static TextureAtlas *s_textureAtlas;
    
    GLuint m_textureID;
    bool m_freeTexture;
    
    void InitTexture( int width, int height, unsigned char *data, GLenum textureTarget, GLfloat filter );
    
    Texture( int width = 0, int height = 0, unsigned char *data = 0, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR );
    
public:
    Texture( const std::string &file );
    virtual ~Texture();
    
    void Bind( GLenum textureUint = GL_TEXTURE0 ) const;
    Texture( Texture &texture );
    void operator=( Texture &texture );
    
    inline GLuint GetID() const { return m_textureID; }
};

#endif /* texture_h */
