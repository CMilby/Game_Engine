//
//  phongcpp
//  Game_Engine
//
//  Created by Craig Milby on 11/26/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "phongShader.h"

#include "transform.h"

Vector3<float> PhongShader::s_ambientLight = Vector3<float>( 0.1f, 0.1f, 0.1f );
DirectionalLight PhongShader::s_directionalLight = DirectionalLight( BaseLight( Vector3<float>( 0.0f, 0.0f, 0.0f ), 0 ), Vector3<float>( 0.0f, 0.0f, 0.0f ) );
std::vector<PointLight> PhongShader::s_pointLights = std::vector<PointLight>();
std::vector<SpotLight> PhongShader::s_spotLights = std::vector<SpotLight>();

PhongShader::PhongShader() {
    AddVertexShader( "phongShader.vs" );
    AddFragmentShader( "phongShader.fs" );
    
    SetAttribLocation( "position", 0 );
    SetAttribLocation( "texCoord", 1 );
    SetAttribLocation( "normal", 2 );
    
    LinkProgram();
    
    AddUniform( "transform" );
    AddUniform( "transformProjected" );
    AddUniform( "baseColor" );
    AddUniform( "ambientLight" );
    
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
        AddUniform( plName + ".atten.exponenet" );
        AddUniform( plName + ".position" );
    }
    
    for ( int i = 0; i < MAX_SPOT_LIGHTS; i++ ) {
        std::string slName = "spotLights[" + std::to_string( i ) + "]";
        
        AddUniform( slName + ".pointLight.base.color" );
        AddUniform( slName + ".pointLight.base.intensity" );
        AddUniform( slName + ".pointLight.atten.constant" );
        AddUniform( slName + ".pointLight.atten.linear" );
        AddUniform( slName + ".pointLight.atten.exponent" );
        AddUniform( slName + ".pointLight.position" );
        AddUniform( slName + ".direction" );
        AddUniform( slName + ".cutoff" );
    }
}

PhongShader::~PhongShader() {
    
}

void PhongShader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) const {
    material.m_texture->Bind();
    Uniform1i( "myTextureSampler", 0 );
    
    // UniformMatrix4f( "MVP", Transform::GetProjection() * camera.GetView() * GetModelMatrix() );
    // UniformMatrix4f( "M", GetModelMatrix() );
    
    UniformMatrix4f( "transformProjected", projected );
    UniformMatrix4f( "transform", world );
    UniformVector3f( "baseColor", material.m_color );
    
    UniformVector3f( "ambientLight", s_ambientLight );
    UniformVector3f( "directionalLight.direction", s_directionalLight.m_direction );
    UniformVector3f( "directionalLight.base.color", s_directionalLight.m_baseLight.m_color );
    Uniform1f( "directionalLight.base.intensity", s_directionalLight.m_baseLight.m_intensity );
    
    for ( int i = 0; i < s_pointLights.size(); i++ ) {
        std::string plName = "pointLights[" + std::to_string( i ) + "]";
        
        UniformVector3f( plName + ".base.color", s_pointLights[ i ].m_baseLight.m_color );
        Uniform1f( plName + ".base.intensity", s_pointLights[ i ].m_baseLight.m_intensity );
        Uniform1f( plName + ".atten.constant", s_pointLights[ i ].m_atten.m_constant );
        Uniform1f( plName + ".atten.linear", s_pointLights[ i ].m_atten.m_linear );
        Uniform1f( plName + ".atten.exponent", s_pointLights[ i ].m_atten.m_exponent );
        UniformVector3f( plName + ".position", s_pointLights[ i ].m_position );
    }
    
    for ( int i = 0; i < s_spotLights.size(); i++ ) {
        std::string slName = "spotLights[" + std::to_string( i ) + "]";
        
        UniformVector3f( slName + ".pointLight.base.color", s_spotLights[ i ].m_pointLight.m_baseLight.m_color );
        Uniform1f( slName + ".pointLight.base.intensity", s_spotLights[ i ].m_pointLight.m_baseLight.m_intensity );
        Uniform1f( slName + ".pointLight.atten.constant", s_spotLights[ i ].m_pointLight.m_atten.m_constant );
        Uniform1f( slName + ".pointLight.atten.linear", s_spotLights[ i ].m_pointLight.m_atten.m_linear );
        Uniform1f( slName + ".pointLight.atten.exponent", s_spotLights[ i ].m_pointLight.m_atten.m_exponent );
        UniformVector3f( slName + ".pointLight.position", s_spotLights[ i ].m_pointLight.m_position );
        UniformVector3f( slName + ".direction", s_spotLights[ i ].m_direction );
        Uniform1f( slName + ".cutoff", s_spotLights[ i ].m_cutoff );
    }
    
    Uniform1f( "specularIntensity", material.m_specularIntensity );
    Uniform1f( "specularPower", material.m_specularPower );
    UniformVector3f( "eyePos", camera.GetPosition() );
}















