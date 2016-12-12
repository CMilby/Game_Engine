//
//  colorized_shader.hpp
//  Game_Engine_New
//
//  Created by Craig Milby on 11/13/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __COLORIZED_SHADER_H__
#define __COLORIZED_SHADER_H__

#include "lighting.h"
#include "shader.h"

class ColorizedShader : public Shader {
    
private:
    DirectionalLight m_directionalLight;
    Vector3f m_ambientLight;
    
public:
    ColorizedShader();
    virtual ~ColorizedShader();
    
    virtual void Init();
    
    virtual void UpdateUniforms( const Matrix4f &p_model, const Matrix4f &p_view , const Matrix4f &p_projection, Texture *p_texture );
};

#endif /* colorized_shader_hpp */
