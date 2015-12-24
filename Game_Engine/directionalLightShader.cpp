//
//  directionalLightShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "directionalLightshader.h"

DirectionalLightShader::DirectionalLightShader() {
    
}

DirectionalLightShader::~DirectionalLightShader() {
    
}

void DirectionalLightShader::Init() {
    AddVertexShader( "LightShader.vs" );
    AddFragmentShader( "DirectionalLightShader.fs" );
    LinkProgram();
    
    AddUniform( "gDirectionalLight.Base.Color" );
    AddUniform( "gDirectionalLight.Base.AmbientIntensity" );
    AddUniform( "gDirectionalLight.Base.DiffuseIntensity" );
    AddUniform( "gDirectionalLight.Direction" );

    LightShader::Init();
}

void DirectionalLightShader::Enable() {
    glEnableVertexAttribArray( 0 );
}

void DirectionalLightShader::Disable() {
    glDisableVertexAttribArray( 0 );
}

void DirectionalLightShader::SetDirectionalLight( const DirectionalLight &light ) {
    UniformVector3f( "gDirectionalLight.Base.Color", light.m_baseLight.m_color );
    Uniform1f( "gDirectionalLight.Base.AmbientIntensity", light.m_baseLight.m_ambientIntensity );
    Uniform1f( "gDirectionalLight.Base.DiffuseIntensity", light.m_baseLight.m_diffuseIntensity );
    UniformVector3f( "gDirectionalLight.Direction", light.m_direction );
}