//
//  directionalLightShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __DIRECTIONAL_LIGHT_SHADER_H__
#define __DIRECTIONAL_LIGHT_SHADER_H__

#include "lightShader.h"
#include "lighting.h"

class DirectionalLightShader : public LightShader {
    
private:
    
public:
    DirectionalLightShader();
    virtual ~DirectionalLightShader();
    
    virtual void Init();
    virtual void Enable();
    virtual void Disable();
    
    void SetDirectionalLight( const DirectionalLight &light );
};

#endif /* directionalLightShader_h */
