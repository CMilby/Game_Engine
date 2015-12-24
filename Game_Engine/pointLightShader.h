//
//  pointLightShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __POINT_LIGHT_SHADER_H__
#define __POINT_LIGHT_SHADER_H__

#include "lightShader.h"
#include "lighting.h"

class PointLightShader : public LightShader {
    
private:
    
public:
    PointLightShader();
    virtual ~PointLightShader();
    
    virtual void Init();
    virtual void Enable();
    virtual void Disable();
    
    void SetPointLight( const PointLight &light );
};

#endif /* pointLightShader_h */
