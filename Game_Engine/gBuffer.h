//
//  gBuffer.h
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __G_BUFFER_H__
#define __G_BUFFER_H__

#include <GL/glew.h>

class GBuffer {
    
public:
    
    enum GBUFFER_TEXTURE_TYPE {
        GBUFFER_TEXTURE_TYPE_POSITION,
        GBUFFER_TEXTURE_TYPE_DIFFUSE,
        GBUFFER_TEXTURE_TYPE_NORMAL,
        GBUFFER_TEXTURE_TYPE_TEXCOORD,
        GBUFFER_NUM_TEXTURES
    };
    
    GBuffer();
    virtual ~GBuffer();
    
    void Init( unsigned int width, unsigned int height );
    
    void StartFrame();
    void BindGeom();
    void BindStencil();
    void BindLight();
    void BindFinal();
    
private:
    GLuint m_fbo;
    GLuint m_textures[ GBUFFER_NUM_TEXTURES ];
    GLuint m_depthTexture;
    GLuint m_finalTexture;
};

#endif /* gBuffer_h */
