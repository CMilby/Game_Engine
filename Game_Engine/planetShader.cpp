//
//  planetShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "planetShader.h"

PlanetShader::PlanetShader() {
    
}

PlanetShader::~PlanetShader() {
    
}

void PlanetShader::Init() {
    AddVertexShader( "PlanetShader.vs" );
    AddFragmentShader( "PlanetShader.fs" );
    LinkProgram();
    
    AddUniform( "transform" );
    AddUniform( "transformProjected" );
    
    AddUniform( "baseColor" );
    AddUniform( "eyePos" );
    AddUniform( "ambientLight" );
    
    AddUniform( "specularPower" );
    AddUniform( "specularIntensity" );
    
    AddUniform( "directionalLight.base.color" );
    AddUniform( "directionalLight.base.intensity" );
    AddUniform( "directionalLight.direction" );
    
    m_ambientLight = Vector3<float>( 0.1f, 0.1f, 0.1f );
    m_directionalLight = DirectionalLight( BaseLight( Vector3<float>( 1.0f, 1.0f, 1.0f ), 0.5f ), Vector3<float>( 1.0f, 1.0f, 0.5f ).Normalized() );
}

void PlanetShader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) {
    
    UniformVector3f( "baseColor", material.m_color );
    UniformVector3f( "eyePos", camera.GetPosition() );
    
    UniformMatrix4f( "transform", world );
    UniformMatrix4f( "transformProjected", projected );
    
    Uniform1f( "specularPower", material.m_specularPower );
    Uniform1f( "specularIntensity", material.m_specularIntensity );
    
    UniformVector3f( "ambientLight", m_ambientLight );
    UniformVector3f( "directionalLight.base.color", m_directionalLight.m_baseLight.m_color );
    Uniform1f( "directionalLight.base.intensity", m_directionalLight.m_baseLight.m_intensity );
    UniformVector3f( "directionalLight.direction", m_directionalLight.m_direction );
}