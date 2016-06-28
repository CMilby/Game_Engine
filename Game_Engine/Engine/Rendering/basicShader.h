//
//  basicShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/10/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __BASIC_SHADER_H__
#define __BASIC_SHADER_H__

#include "shader.h"

class BasicShader : public Shader {
    
private:
    
public:
    BasicShader();
    virtual ~BasicShader();
    virtual void Init();
    
    virtual void UpdateUniforms( const Matrix4<float> &pMVP, const Material &pMaterial );
};

#endif /* basicShader_h */
