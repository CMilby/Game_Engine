//
//  pointLightShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "pointLightShader.h"

PointLightShader::PointLightShader() {
    
}

PointLightShader::~PointLightShader() {
    
}

void PointLightShader::Init() {
    AddVertexShader( "LightShader.vs" );
    AddFragmentShader( "PointLightShader.fs" );
    LinkProgram();
    
    AddUniform( "gPointLight.Base.Color" );
    AddUniform( "gPointLight.Base.AmbientIntensity" );
    AddUniform( "gPointLight.Base.DiffuseIntensity" );
    AddUniform( "gPointLight.Atten.Constant" );
    AddUniform( "gPointLight.Atten.Linear" );
    AddUniform( "gPointLight.Atten.Exponent" );
    AddUniform( "gPointLight.Position" );
    
    LightShader::Init();
}

void PointLightShader::Enable() {
    glEnableVertexAttribArray( 1 );
}

void PointLightShader::Disable() {
    glDisableVertexAttribArray( 0 );
}

void PointLightShader::SetPointLight( const PointLight &light ) {
    UniformVector3f( "gPointLight.Base.Color", light.m_baseLight.m_color );
    Uniform1f( "gPointLight.Base.AmbientIntensity", light.m_baseLight.m_ambientIntensity );
    Uniform1f( "gPointLight.Base.DiffuseIntensity", light.m_baseLight.m_diffuseIntensity );
    Uniform1f( "gPointLight.Atten.Constant", light.m_atten.m_constant );
    Uniform1f( "gPointLight.Atten.Linear", light.m_atten.m_linear );
    Uniform1f( "gPointLight.Atten.Exponent", light.m_atten.m_exponent );
    UniformVector3f( "gPointLight.Atten.Exponent", light.m_position );
}







