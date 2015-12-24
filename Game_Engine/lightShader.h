//
//  lightShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __LIGHT_SHADER_H__
#define __LIGHT_SHADER_H__

#include "shader.h"

class LightShader : public Shader {
    
private:
    
public:
    LightShader();
    virtual ~LightShader();
    
    virtual void Init();
};

#endif /* lightShader_h */
