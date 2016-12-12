//
//  basic_shader.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
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
    
    virtual void UpdateUniforms( const Matrix4f &p_model, const Matrix4f &p_view , const Matrix4f &p_projection, Texture *p_texture );
};

#endif /* basic_shader_h */
