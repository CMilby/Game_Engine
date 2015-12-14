//
//  phongShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 11/26/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "phongShader.h"

#include "transform.h"

PhongShader::PhongShader() {
    
}

PhongShader::~PhongShader() {
    
}

void PhongShader::Init() {
    AddVertexShader( "PhongShader.vs" );
    AddFragmentShader( "PhongShader.fs" );
    
    LinkProgram();
    
    AddAttribute( "position" );
    AddAttribute( "texCoord" );
    AddAttribute( "normal" );
    
    AddUniform( "transform" );
    AddUniform( "transformProjected" );
    AddUniform( "baseColor" );
    AddUniform( "ambientLight" );
    
    AddUniform( "sampler" );
    AddUniform( "specularIntensity" );
    AddUniform( "specularPower" );
    AddUniform( "eyePos" );
    
    AddUniform( "directionalLight.base.color" );
    AddUniform( "directionalLight.base.intensity" );
    AddUniform( "directionalLight.direction" );
    
    for ( int i = 0; i < MAX_POINT_LIGHTS; i++ ) {
        std::string plName = "pointLights[" + std::to_string( i ) + "]";
        
        AddUniform( plName + ".base.color" );
        AddUniform( plName + ".base.intensity" );
        AddUniform( plName + ".atten.constant" );
        AddUniform( plName + ".atten.linear" );
        AddUniform( plName + ".atten.exponent" );
        AddUniform( plName + ".position" );
        AddUniform( plName + ".range" );
    }
    
    for ( int i = 0; i < MAX_SPOT_LIGHTS; i++ ) {
        std::string slName = "spotLights[" + std::to_string( i ) + "]";
        
        AddUniform( slName + ".pointLight.base.color" );
        AddUniform( slName + ".pointLight.base.intensity" );
        AddUniform( slName + ".pointLight.atten.constant" );
        AddUniform( slName + ".pointLight.atten.linear" );
        AddUniform( slName + ".pointLight.atten.exponent" );
        AddUniform( slName + ".pointLight.position" );
        AddUniform( slName + ".pointLight.range" );
        AddUniform( slName + ".direction" );
        AddUniform( slName + ".cutoff" );
    }
    
    m_ambientLight = Vector3<float>( 0.2f, 0.2f, 0.2f );
    m_directionalLight = DirectionalLight( BaseLight( Vector3<float>( 0.1f, 0.1f, 0.1f ), 1.0f ), Vector3<float>( 8.0f, 8.0f, 8.0f ) );
    
    PointLight pLight( BaseLight( Vector3<float>( 1, 1, 0 ), 8.0f ), Attenuation( 5, 4, 1 ), Vector3<float>( -2, 0, 0 ), 10.0f );
    AddPointLight( pLight );
}

void PhongShader::Enable() {
    glEnableVertexAttribArray( GetAttribute( "position" ) );
    glEnableVertexAttribArray( GetAttribute( "texCoord" ) );
    glEnableVertexAttribArray( GetAttribute( "normal" ) );
}

void PhongShader::Disable() {
    glDisableVertexAttribArray( GetAttribute( "position" ) );
    glDisableVertexAttribArray( GetAttribute( "texCoord" ) );
    glDisableVertexAttribArray( GetAttribute( "normal" ) );
}

void PhongShader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material, const Mesh &mesh ) {
    material.m_texture->Bind();
    Uniform1i( "sampler", 0 );
    
    UniformMatrix4f( "transformProjected", projected );
    UniformMatrix4f( "transform", world );
    UniformVector3f( "baseColor", material.m_color );
    
    UniformVector3f( "ambientLight", m_ambientLight );
    UniformVector3f( "directionalLight.direction", m_directionalLight.m_direction );
    UniformVector3f( "directionalLight.base.color", m_directionalLight.m_baseLight.m_color );
    Uniform1f( "directionalLight.base.intensity", m_directionalLight.m_baseLight.m_intensity );
    
    for ( int i = 0; i < m_pointLights.size(); i++ ) {
        std::string plName = "pointLights[" + std::to_string( i ) + "]";
        
        UniformVector3f( plName + ".base.color", m_pointLights[ i ].m_baseLight.m_color );
        Uniform1f( plName + ".base.intensity", m_pointLights[ i ].m_baseLight.m_intensity );
        Uniform1f( plName + ".atten.constant", m_pointLights[ i ].m_atten.m_constant );
        Uniform1f( plName + ".atten.linear", m_pointLights[ i ].m_atten.m_linear );
        Uniform1f( plName + ".atten.exponent", m_pointLights[ i ].m_atten.m_exponent );
        UniformVector3f( plName + ".position", m_pointLights[ i ].m_position );
    }
    
    for ( int i = 0; i < m_spotLights.size(); i++ ) {
        std::string slName = "spotLights[" + std::to_string( i ) + "]";
        
        UniformVector3f( slName + ".pointLight.base.color", m_spotLights[ i ].m_pointLight.m_baseLight.m_color );
        Uniform1f( slName + ".pointLight.base.intensity", m_spotLights[ i ].m_pointLight.m_baseLight.m_intensity );
        Uniform1f( slName + ".pointLight.atten.constant", m_spotLights[ i ].m_pointLight.m_atten.m_constant );
        Uniform1f( slName + ".pointLight.atten.linear", m_spotLights[ i ].m_pointLight.m_atten.m_linear );
        Uniform1f( slName + ".pointLight.atten.exponent", m_spotLights[ i ].m_pointLight.m_atten.m_exponent );
        UniformVector3f( slName + ".pointLight.position", m_spotLights[ i ].m_pointLight.m_position );
        UniformVector3f( slName + ".direction", m_spotLights[ i ].m_direction );
        Uniform1f( slName + ".cutoff", m_spotLights[ i ].m_cutoff );
    }
    
    Uniform1f( "specularIntensity", material.m_specularIntensity );
    Uniform1f( "specularPower", material.m_specularPower );
    UniformVector3f( "eyePos", camera.GetPosition() );
    
    Enable();
    mesh.Render();
    Disable();
}















