//
//  text2d.h
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __TEXT_2D_H__
#define __TEXT_2D_H__

#include <string>

#include <GL/glew.h>

#include "shader.h"
#include "texture.h"

#define FONT_SIZE 16.0f

class TextShader : public Shader {
  
private:
    Texture *m_texture;
    
    GLuint m_vertexBuffer;
    GLuint m_uvBuffer;
    
    std::string m_file;
    
public:
    TextShader( const std::string &file );
    virtual ~TextShader();
    virtual void Init();
    
    void Render( const char *text, int x, int y, int size );
};

#endif /* text2d_h */
