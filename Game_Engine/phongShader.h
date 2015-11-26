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

#define MAX_SPOT_LIGHTS 4
#define MAX_POINT_LIGHTS 4

class PhongShader : public Shader {
    
private:
    static Vector3<float> s_ambientLight;
    static DirectionalLight s_directionalLight;
    static std::vector<PointLight> s_pointLights;
    static std::vector<SpotLight> s_spotLights;
    
public:
    PhongShader();
    virtual ~PhongShader();
    
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) const;
};

#endif /* phongShader_h */
