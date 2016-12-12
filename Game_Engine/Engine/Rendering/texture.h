//
//  texture.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include <GL/glew.h>

class Texture {
    
private:
    static GLuint s_lastBind;
    
    GLuint m_id;
    
public:
    Texture( const std::string &p_file );
    Texture( unsigned int p_width, unsigned int p_height, float p_data[] );
    virtual ~Texture();
    
    void Bind( GLenum p_textureUint = GL_TEXTURE0, GLenum p_textureType = GL_TEXTURE_2D ) const;
    
    void operator=( const Texture &p_texture ) {
        m_id = p_texture.m_id;
    }

private:
    void InitTexture( int p_width, int p_height, unsigned char *p_data, GLenum p_textureTarget, GLfloat p_filter );
};

#endif /* texture_h */
