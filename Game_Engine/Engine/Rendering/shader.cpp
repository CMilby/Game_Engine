//
//  shader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "shader.h"

#include "utility.h"

Shader::Shader() {
    m_framework = new ShadingFramework();
}

Shader::~Shader() {
    if ( m_framework ) delete m_framework;
}

void Shader::AddFragmentShader( const std::string &filename ) {
    m_framework->AddFragmentShader( Utility::DirectoryPath() + "shaders/" + filename );
}

void Shader::AddVertexShader( const std::string &filename ) {
    m_framework->AddVertexShader( Utility::DirectoryPath() + "shaders/" + filename );
}

void Shader::AttachShader( int shaderID ) const {
    m_framework->AttachShader( shaderID );
}

void Shader::LinkProgram() const {
    m_framework->LinkProgram();
}

void Shader::EnableVertexAttribArray( unsigned int position ) const {
	m_framework->EnableVertexAttribArray( position );
}

void Shader::DisableVertexAttribArray( unsigned int position ) const {
	m_framework->DisableVertexAttribArray( position );
}

void Shader::Bind() const {
    m_framework->Bind();
}

void Shader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) {
	
}

void Shader::UpdateUniforms( const Matrix4<float> &pMVP, const Material &pMaterial ) {
	
}

void Shader::AddUniform( const std::string &name ) const {
    m_framework->AddUniform( name );
}

GLuint Shader::GetUniform( const std::string &name ) const {
    return m_framework->GetUniform( name );
}

void Shader::AddAttribute( const std::string &name ) const {
    m_framework->AddAttribute( name );
}

GLuint Shader::GetAttribute( const std::string &name ) const {
    return m_framework->GetAttribute( name );
}

void Shader::SetAttribLocation( const std::string &name, int location ) const {
    m_framework->SetAttribLocation( name, location );
}

void Shader::Uniform1ui( const std::string &name, unsigned int value ) const {
    m_framework->Uniform1ui( name, value );
}

void Shader::Uniform1i( const std::string &name, int value ) const {
    m_framework->Uniform1i( name, value );
}

void Shader::Uniform1f( const std::string &name, float value ) const {
    m_framework->Uniform1f( name, value );
}

void Shader::UniformMatrix4f( const std::string &name, const Matrix4<float> &value ) const {
    m_framework->UniformMatrix4f( name, value );
}

void Shader::Uniform2f( const std::string &name, float x, float y ) const {
    m_framework->Uniform2f( name, x, y );
}

void Shader::UniformVector3f( const std::string &name, const Vector3<float> &value ) const {
    m_framework->UniformVector3f( name, value );
}













