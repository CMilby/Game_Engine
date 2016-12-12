//
//  basic_shader.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "basic_shader.h"

BasicShader::BasicShader() : Shader( ShaderType::SHADER_BASIC ) {
    
}

BasicShader::~BasicShader() {
    
}

void BasicShader::Init() {
    AddVertexShader( "StandardShading.vs" );
    AddFragmentShader( "StandardShading.fs" );
    LinkProgram();
    
    AddUniform( "model" );
    AddUniform( "view" );
    AddUniform( "projection" );
    AddUniform( "sampler" );
}

void BasicShader::UpdateUniforms( const Matrix4f &p_model, const Matrix4f &p_view , const Matrix4f &p_projection, Texture *p_texture ) {
    p_texture->Bind();
    Uniform1i( "sampler", 0 );
    
    UniformMatrix4f( "model", p_model );
    UniformMatrix4f( "view", p_view );
    UniformMatrix4f( "projection", p_projection );
}
