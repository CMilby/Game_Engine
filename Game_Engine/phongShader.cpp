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
    
    AddUniform( "transform" );
    AddUniform( "transformProjected" );
    
    AddUniform( "baseColor" );
    AddUniform( "eyePos" );
    AddUniform( "ambientLight" );
    AddUniform( "sampler" );
    
    AddUniform( "specularPower" );
    AddUniform( "specularIntensity" );
    
    AddUniform( "directionalLight.base.color" );
    AddUniform( "directionalLight.base.intensity" );
    AddUniform( "directionalLight.direction" );
    
    m_ambientLight = Vector3<float>( 0.1f, 0.1f, 0.1f );
    m_directionalLight = DirectionalLight( BaseLight( Vector3<float>( 1.0f, 1.0f, 1.0f ), 0.5f ), Vector3<float>( 1.0f, 1.0f, 0.5f ).Normalized() );
    
    PointLight pLight( BaseLight( Vector3<float>( 1, 1, 0 ), 8.0f ), Attenuation( 0, 0, 1 ), Vector3<float>( -2, 1, 0 ), 10.0f );
    AddPointLight( pLight );
}

void PhongShader::Enable() {
    glEnableVertexAttribArray( 0);
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
}

void PhongShader::Disable() {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
}

void PhongShader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material, const Mesh &mesh ) {
    
    material.m_texture->Bind();
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
    
    // UniformVector3f( "directionalLight.base.color", m_directionalLight.m_baseLight.m_color );
    // Uniform1f( "directionalLight.base.intensity", m_directionalLight.m_baseLight.m_intensity );
    // UniformVector3f( "directionalLight.direction", m_directionalLight.m_direction );
    
    // Uniform1f( "specularIntensity", material.m_specularIntensity );
    // Uniform1f( "specularPower", material.m_specularPower );
    
    /*UniformMatrix4f( "transformProjected", projected );
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
    UniformVector3f( "eyePos", camera.GetPosition() );*/
}















