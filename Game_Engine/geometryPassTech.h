//
//  geometryPassTech.hpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __GEOMETRY_PASS_TECH_H__
#define __GEOMETRY_PASS_TECH_H__

#include <GL/glew.h>

#include "gBuffer.h"
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
    
public:
    enum GEOMETRY_PASS {
        GEOMETRY_PASS,
        LIGHT_PASS
    };
    
    GeometryPassTech();
    virtual void Init();
    
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material );
    
    static void SetGBuffer( const GBuffer &buffer ) { s_gBuffer = buffer; }
    
    void SetWVP( const Matrix4<float> &WVP );
    void SetWorldMatrix( const Matrix4<float> &WVP );
    void SetColorTextureUint( unsigned int textureUnit );
    
private:
    static GBuffer s_gBuffer;
    
    int m_pass;
    
    GLuint m_WVPlocation;
    GLuint m_worldMatrixLocation;
    GLuint m_colorTextureUnitLocation;

};

#endif /* geometryPassTech_hpp */
