//
//  deferredShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __DEFERRED_SHADER_H__
#define __DEFERRED_SHADER_H__

#include <vector>

#include "dirLightPassTech.h"
#include "gBuffer.h"
#include "geometryPassTech.h"
#include "lightPassTech.h"
#include "nullTech.h"
#include "pointLightPassTech.h"
#include "shader.h"

class DeferredShader : public Shader {
    
private:
    GBuffer *m_gBuffer;
    GeometryPassTech *m_geomPass;
    DirLightPassTech *m_dirLightPass;
    PointLightPassTech *m_pointLightPass;
    NullTech *m_nullTech;
    
    RenderableEntity *m_sphere;
    RenderableEntity *m_quad;
    
    std::vector<PointLight*> m_pointLights;
    
    void GeometryPass( const Matrix4<float> &world, const Matrix4<float> &projected, const Mesh &mesh );
    void StencilPass( unsigned int index, const Camera &camera );
    void PointLightPass( unsigned int index, const Camera &camera );
    void DirectionaLightPass( const Vector3<float> &eyePos );
    void FinalPass();
    
    float CalcPointLightSphere( const PointLight &light );
    
public:
    DeferredShader();
    virtual ~DeferredShader();
    
    void Render( const Matrix4<float> &world, const Matrix4<float> &projected,  const Camera &camera, const Material &material, const Mesh &mesh );
    
    virtual void Init();
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected,  const Camera &camera, const Material &material, const Mesh &mesh );
};

#endif /* deferredShader_h */
