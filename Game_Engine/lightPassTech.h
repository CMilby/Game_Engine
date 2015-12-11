//
//  lightPassTech.
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __LIGHT_PASS_TECH_H__
#define __LIGHT_PASS_TECH_H__

#include "shader.h"

class LightPassTech : public Shader {
    
private:
    
public:
    LightPassTech();
    virtual void Init();
    
    void SetWVP( const Matrix4<float> &WVP );
    void SetPositionTextureUnit( unsigned int textureUnit );
    void SetColorTextureUnit( unsigned int textureUnit );
    void SetNormalTextureUnit( unsigned int textureUnit );
    void SetEyeWorldPos( const Vector3<float> &pos );
    void SetMatSpecularIntensity( float intensity );
    void SetMatSpecularPower( float power );
    void SetScreenSize( unsigned int width, unsigned int height );
};

#endif /* lightPassTech_h */
