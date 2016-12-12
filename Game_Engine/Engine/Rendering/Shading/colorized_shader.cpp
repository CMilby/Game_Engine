//
//  colorized_shader.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 11/13/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "colorized_shader.h"

ColorizedShader::ColorizedShader() : Shader( ShaderType::SHADER_COLORIZED ) {
    m_directionalLight = DirectionalLight( BaseLight( Vector3f( 1.0f, 1.0f, 1.0f ), 0.75f ), Vector3f( 1.0f, 0.0f, 0.0f ) );
    m_ambientLight = Vector3f( 0.2f, 0.2f, 0.2f );
}

ColorizedShader::~ColorizedShader() {
    
}

void ColorizedShader::Init() {
    AddVertexShader( "ColorizedShader.vs" );
    AddFragmentShader( "ColorizedShader.fs" );
    LinkProgram();
    
    AddUniform( "model" );
    AddUniform( "view" );
    AddUniform( "projection" );
    
    AddUniform( "ambientLight" );
    AddUniform( "directionalLight.base.color" );
    AddUniform( "directionalLight.base.intensity" );
    AddUniform( "directionalLight.direction" );
}

void ColorizedShader::UpdateUniforms( const Matrix4f &p_model, const Matrix4f &p_view, const Matrix4f &p_projection, Texture *p_texture ) {
    p_texture->Bind();
    
    UniformMatrix4f( "model", p_model );
    UniformMatrix4f( "view", p_view );
    UniformMatrix4f( "projection", p_projection );
    
    UniformVector3f( "ambientLight", m_ambientLight );
    UniformVector3f( "directionalLight.base.color", m_directionalLight.m_baseLight.m_color );
    Uniform1f( "directionalLight.base.intensity", m_directionalLight.m_baseLight.m_intensity );
    UniformVector3f( "directionalLight.direction", m_directionalLight.m_direction );
}
