//
//  pointLightPassTech.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "pointLightPassTech.h"

PointLightPassTech::PointLightPassTech() {
    
}

void PointLightPassTech::Init() {
    AddVertexShader( "light_pass.vs" );
    AddFragmentShader( "point_light_pass.fs" );
    LinkProgram();
    
    AddUniform( "gPointLight.Base.Color" );
    AddUniform( "gPointLight.Base.AmbientIntensity" );
    AddUniform( "gPointLight.Position" );
    AddUniform( "gPointLight.Base.DiffuseIntensity" );
    AddUniform( "gPointLight.Atten.Constant" );
    AddUniform( "gPointLight.Atten.Linear" );
    AddUniform( "gPointLight.Atten.Exp" );
    
    return LightPassTech::Init();
}

void PointLightPassTech::SetPointLight( const PointLight &pLight ) {
    UniformVector3f( "gPointLight.Base.Color", pLight.m_baseLight.m_color );
    Uniform1f( "gPointLight.AmbientIntensity", pLight.m_baseLight.m_intensity );
    Uniform1f( "gPointLight.DiffuseIntensity", pLight.m_baseLight.m_diffuseIntensity );
    UniformVector3f( "gPointLight.Position", pLight.m_position );
    Uniform1f( "gPointLight.Atten.Constant", pLight.m_atten.m_constant );
    Uniform1f( "gPointLight.Atten.Linear", pLight.m_atten.m_linear );
    Uniform1f( "gPointLight.Atten.Exp", pLight.m_atten.m_exponent );
}