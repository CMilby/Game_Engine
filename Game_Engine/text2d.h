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

class Text2D {
  
private:
    Shader *m_shader;
    Texture *m_texture;
    
    GLuint m_vertexBuffer;
    GLuint m_uvBuffer;
    
    std::string m_file;
    
public:
    Text2D( const std::string &file );
    virtual ~Text2D();
    void Init();
    
    void PrintText2D( const char *text, int x, int y, int size );
};

#endif /* text2d_h */
