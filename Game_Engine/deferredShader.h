//
//  deferredShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __DEFERRED_SHADER_H__
#define __DEFERRED_SHADER_H__

#include "gBuffer.h"
#include "shader.h"

class DeferredShader : public Shader {
    
private:
    GBuffer *m_gBuffer;
    
public:
    DeferredShader();
    virtual ~DeferredShader();
    
    virtual void Init();
    
    void Render();
};

#endif /* deferredShader_h */
