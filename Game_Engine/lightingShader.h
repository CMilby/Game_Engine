//
//  lightingShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __LIGHTING_SHADER_H__
#define __LIGHTING_SHADER_H__

#include "shader.h"

class LightingShader : public Shader {
    
private:
    
public:
    LightingShader();
    virtual ~LightingShader();
    
    virtual void Init();
};

#endif /* lightingShader_h */
