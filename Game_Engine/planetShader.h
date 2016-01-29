//
//  planetShader.h
//  Game_Engine
//
//  Created by Craig Milby on 1/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLANET_SHADER_H__
#define __PLANET_SHADER_H__

#include "shader.h"

class PlanetShader : public Shader {
    
private:
    
public:
    PlanetShader();
    virtual ~PlanetShader();
    virtual void Init();
    
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material );
};

#endif /* planetShader_h */
