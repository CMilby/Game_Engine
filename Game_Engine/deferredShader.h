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
#include "config.h"
#include "directionalLightShader.h"
#include "gBuffer.h"
#include "geometryShader.h"
#include "lightShader.h"
#include "nullShader.h"
#include "pointLightShader.h"
#include "shader.h"

#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0
#define SHADOW_TEXTURE_UNIT             GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX       1
#define NORMAL_TEXTURE_UNIT             GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX       2
#define RANDOM_TEXTURE_UNIT             GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX       3
#define DISPLACEMENT_TEXTURE_UNIT       GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX 4

class DeferredShader : public Shader {
    
private:
    GBuffer *m_gBuffer;
    GeometryShader *m_geomShader;
    PointLightShader *m_pointLightShader;
    DirectionalLightShader *m_dirLightShader;
    NullShader *m_nullShader;
    
    Mesh *m_quad;
    Mesh *m_sphere;
    
    std::vector<PointLight> m_pointLights;
    
    void GeometryPass( const Camera &camera, const RenderableEntity &entity );
    void StencilPass( unsigned int index, const Camera &camera );
    void PointLightPass( unsigned int index, const Camera &camera );
    void DirectionalLightPass( const Camera &camera );
    void FinalPass();
    
    float CalcPointLightBSphere( const PointLight &light );
    
public:
    DeferredShader();
    virtual ~DeferredShader();
    
    virtual void Init();
    
    void Render( const Camera &camera, const RenderableEntity &entity );
};

#endif /* deferredShader_h */
