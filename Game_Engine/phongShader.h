//
//  phongShader.h
//  Game_Engine
//
//  Created by Craig Milby on 11/26/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __PHONG_SHADER_H__
#define __PHONG_SHADER_H__

#include <vector>

#include "lighting.h"
#include "shader.h"

class PhongShader : public Shader {
    
private:
    const int MAX_POINT_LIGHTS = 5;
    const int MAX_SPOT_LIGHTS = 5;
    
    Vector3<float> m_ambientLight;
    DirectionalLight m_directionalLight;
    std::vector<PointLight> m_pointLights;
    std::vector<SpotLight> m_spotLights;
    
public:
    PhongShader();
    virtual ~PhongShader();
    virtual void Init();
    
    virtual void Enable() const;
    virtual void Disable() const;
    
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material, const Mesh &mesh );
    
    inline void AddPointLight( const PointLight &plight ) { m_pointLights.push_back( plight ); }
    inline void AddSpotLight( const SpotLight &sLight ) { m_spotLights.push_back( sLight ); }
};

#endif /* phongShader_h */
