//
//  dirLightPassTech.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "dirLightPassTech.h"

DirLightPassTech::DirLightPassTech() {
    
}

void DirLightPassTech::Init() {
    AddVertexShader( "light_pass.vs" );
    AddFragmentShader( "dir_light_pass.fs" );
    LinkProgram();
    
    AddUniform( "gDirectionalLight.Base.Color" );
    AddUniform( "gDirectionalLight.Base.AmbientIntensity" );
    AddUniform( "gDirectioanlLight.Direction" );
    AddUniform( "gDirectionalLight.Base.DiffuseIntensity" );
    
    LightPassTech::Init();
}

void DirLightPassTech::SetDirectionalLight( const DirectionalLight &light ) {
    UniformVector3f( "gDirectionalLight.Base.Color", light.m_baseLight.m_color );
    UniformVector3f( "gDirectionalLight.Direction", light.m_direction );
    Uniform1f( "gDirectionalLight.Base.AmbientIntensity", light.m_baseLight.m_intensity );
    Uniform1f( "gDirectionalLight.Base.DiffuseIntensity", light.m_baseLight.m_diffuseIntensity );
}