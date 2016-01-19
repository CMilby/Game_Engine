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
    
    for ( unsigned int i = 0; i < MAX_POINT_LIGHTS; i++ ) {
        std::string name = "pointLights[" + std::to_string( i ) + "]";
        
        AddUniform( name + ".base.color" );
        AddUniform( name + ".base.intensity" );
        AddUniform( name + ".atten.constant" );
        AddUniform( name + ".atten.linear" );
        AddUniform( name + ".atten.exponent" );
        AddUniform( name + ".position" );
        AddUniform( name + ".range" );
    }
    
    for ( unsigned int i = 0; i < MAX_SPOT_LIGHTS; i++ ) {
        std::string name = "spotLights[" + std::to_string( i ) + "]";
        
        AddUniform( name + ".pointLight.base.color" );
        AddUniform( name + ".pointLight.base.intensity" );
        AddUniform( name + ".pointLight.atten.constant" );
        AddUniform( name + ".pointLight.atten.linear" );
        AddUniform( name + ".pointLight.atten.exponent" );
        AddUniform( name + ".pointLight.position" );
        AddUniform( name + ".pointLight.range" );
        AddUniform( name + ".direction" );
        AddUniform( name + ".cutoff" );
    }
    
    m_ambientLight = Vector3<float>( 0.1f, 0.1f, 0.1f );
    m_directionalLight = DirectionalLight( BaseLight( Vector3<float>( 1.0f, 1.0f, 1.0f ), 0.5f ), Vector3<float>( 1.0f, 1.0f, 0.5f ).Normalized() );
    
    PointLight pLight( BaseLight( Vector3<float>( 0.0f, 1.0f, 1.0f ), 0.8f ), Attenuation( 0.0f, 0.0f, 1.0f ), Vector3<float>( 3.0f, 1.5f, 3.0f ), 10.0f );
    AddPointLight( pLight );
    
    SpotLight sLight( PointLight( BaseLight( Vector3<float>( 0.0f, 1.0f, 0.0f ), 0.8f ), Attenuation( 0.0f, 0.0f, 0.1f ), Vector3<float>( -4.0f, 2.0f, 4.0f ), 30.0f ), Vector3<float>( 1.0f, 0.0f, -1.0f ), 0.7f );
    AddSpotLight( sLight );
}

void PhongShader::Enable() const {
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
}

void PhongShader::Disable() const {
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
    
    for ( int i = 0; i < m_pointLights.size() && i < MAX_POINT_LIGHTS; i++ ) {
        std::string name = "pointLights[" + std::to_string( i ) + "]";
        
        UniformVector3f( name + ".base.color", m_pointLights[ i ].m_baseLight.m_color );
        Uniform1f( name + ".base.intensity", m_pointLights[ i ].m_baseLight.m_intensity );
        Uniform1f( name + ".atten.constant", m_pointLights[ i ].m_atten.m_constant );
        Uniform1f( name + ".atten.linear", m_pointLights[ i ].m_atten.m_linear );
        Uniform1f( name + ".atten.exponent", m_pointLights[ i ].m_atten.m_exponent );
        UniformVector3f( name + ".position", m_pointLights[ i ].m_position );
        Uniform1f( name + ".range", m_pointLights[ i ].m_range );
    }
    
    for ( int i = 0; i < m_spotLights.size() && i < MAX_SPOT_LIGHTS; i++ ) {
        std::string name = "spotLights[" + std::to_string( i ) + "]";
        
        UniformVector3f( name + ".pointLight.base.color", m_spotLights[ i ].m_pointLight.m_baseLight.m_color );
        Uniform1f( name + ".pointLight.base.intensity", m_spotLights[ i ].m_pointLight.m_baseLight.m_intensity );
        Uniform1f( name + ".pointLight.atten.constant", m_spotLights[ i ].m_pointLight.m_atten.m_constant );
        Uniform1f( name + ".pointLight.atten.linear", m_spotLights[ i ].m_pointLight.m_atten.m_linear );
        Uniform1f( name + ".pointLight.atten.exponent", m_spotLights[ i ].m_pointLight.m_atten.m_exponent );
        UniformVector3f( name + ".pointLight.position", m_spotLights[ i ].m_pointLight.m_position );
        Uniform1f( name + ".pointLight.range", m_spotLights[ i ].m_pointLight.m_range );
        UniformVector3f( name + ".direction", m_spotLights[ i ].m_direction );
        Uniform1f( name + ".cutoff", m_spotLights[ i ].m_cutoff );
    }
    
    Enable();
    mesh.Render();
    Disable();
}















