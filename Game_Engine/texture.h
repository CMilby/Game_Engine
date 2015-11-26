//
//  texture.h
//  Game_Engine
//
//  Created by Craig Milby on 10/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include <GL/glew.h>

enum TextureType {
    TYPE_PNG,
    TYPE_DDS
};

class Texture {
    
private:
    static Texture *s_lastBind;
    
    GLenum m_textureTarget;
    GLuint m_textureID;
    TextureType m_type;
    bool m_freeTexture;
    
    void InitTexture( int width, int height, unsigned char *data, GLenum textureTarget, GLfloat filter );
    
    GLuint LoadDDS( const std::string &filename );
    GLuint LoadTGA( const std::string &filename );
    
    Texture( int width = 0, int height = 0, unsigned char *data = 0, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR );
    
public:
    Texture( const std::string &file, TextureType texType );
    virtual ~Texture();
    
    void Bind( GLenum textureUint = GL_TEXTURE0 ) const;
    Texture( Texture &texture );
    void operator=( Texture &texture );
    
    inline GLuint GetID() const { return m_textureID; }
    
/*private:
    GLuint m_texture;
    
    GLuint LoadDDS( const std::string &filename );
    GLuint LoadTGA( const std::string &filename );
public:
    Texture( const std::string &filename );
    virtual ~Texture();
    
    void Bind() const;*/
};

#endif /* texture_h */
