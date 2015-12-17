//
//  geometryPassTech.h
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __GEOMETRY_PASS_TECH_H__
#define __GEOMETRY_PASS_TECH_H__

#include <GL/glew.h>

#include "math3d.h"
#include "shader.h"

#define COLOR_TEXTURE_UNIT               GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX         0
#define SHADOW_TEXTURE_UNIT              GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX        1
#define NORMAL_TEXTURE_UNIT              GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX        2
#define RANDOM_TEXTURE_UNIT              GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX        3
#define DISPLACEMENT_TEXTURE_UNIT        GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX  4

class GeometryPassTech : public Shader {
    
private:
    int m_pass;
    
    GLuint m_WVPlocation;
    GLuint m_worldMatrixLocation;
    GLuint m_colorTextureUnitLocation;
    
public:
    GeometryPassTech();
    virtual void Init();
    
    void SetWVP( const Matrix4<float> &WVP );
    void SetWorldMatrix( const Matrix4<float> &WVP );
    void SetColorTextureUint( unsigned int textureUnit );
};

#endif /* geometryPassTech_h */
