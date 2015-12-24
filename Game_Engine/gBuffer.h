//
//  gBuffer.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __GEOMETRY_BUFFER_H__
#define __GEOMETRY_BUFFER_H__

#include <GL/glew.h>

class GBuffer {
    
private:
    GLuint m_fbo;
    GLuint m_position;
    GLuint m_normal;
    GLuint m_color;
    GLuint m_depth;
    GLuint m_light;
    GLuint m_effect1;
    GLuint m_effect2;
    
    GLenum m_drawBuffers[ 3 ];
    
public:
    GBuffer();
    virtual ~GBuffer();
    
    void Init();
    
    inline GLuint GetFBO() const { return m_fbo; };
    
    void SetDrawBuffers();
    void SetDrawLight();
    void SetDrawEffect();
    void SetDrawNone();
    
    void SetReadEffect();
    
    void Bind();
    void BindDraw();
    void BindRead();
    
    void Unbind();
    void UnbindDraw();
    void UnbindRead();
    
    void SetGeomTextures();
};

#endif /* gBuffer_h */
