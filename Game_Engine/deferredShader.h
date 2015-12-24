//
//  deferredShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __DEFERRED_SHADER_H__
#define __DEFERRED_SHADER_H__

#include <vector>

#include "camera.h"
#include "gBuffer.h"
#include "geometryShader.h"
#include "lightingShader.h"
#include "shader.h"

struct Light {
    Vector3<float> m_position;
    Vector3<float> m_color;
};

class DeferredShader : public Shader {
    
private:
    GBuffer *m_gBuffer;
    GeometryShader *m_geomShader;
    LightingShader *m_lightShader;
    
    std::vector<Light> m_lights;
    
    GLuint quadVAO = 0;
    GLuint quadVBO;
    
public:
    DeferredShader();
    virtual ~DeferredShader();
    
    virtual void Init();
    
    void Render( const Camera &camera, const RenderableEntity &entity );
    void RenderQuad();
};

#endif /* deferredShader_h */
