//
//  shader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "shader.h"

#include <fstream>
#include <vector>

std::map<std::string, GLuint> Shader::s_uniformMap = std::map<std::string, GLuint>();
std::map<std::string, GLuint> Shader::s_attributeMap = std::map<std::string, GLuint>();

Shader::Shader() {
    m_program = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram( m_program );
}

void Shader::LoadShader( const std::string &filename, int type ) {
    GLuint shaderID = glCreateShader( type );
    
    std::string shaderCode;
    std::ifstream shaderStream( filename, std::ios::in );
    if ( shaderStream.is_open() ) {
        std::string line = "";
        while ( getline( shaderStream, line ) ) {
            shaderCode += "\n" + line;
        }
        shaderStream.close();
    } else {
        fprintf( stderr, "Error loading shader." );
        return;
    }
    
    GLint result = GL_FALSE;
    int infoLogLength;
    
    char const *sourcePoint = shaderCode.c_str();
    glShaderSource( shaderID, 1, &sourcePoint, NULL );
    glCompileShader( shaderID );
    
    glGetShaderiv( shaderID, GL_COMPILE_STATUS, &result );
    glGetShaderiv( shaderID, GL_INFO_LOG_LENGTH, &infoLogLength );
    
    std::vector<char> shaderErrorMessage( infoLogLength );
    glGetShaderInfoLog( shaderID, infoLogLength, NULL, &shaderErrorMessage[ 0 ] );
    // fprintf( stdout, "%s\n", &shaderErrorMessage[ 0 ] );
    
    AttachShader( shaderID );
}

void Shader::AddFragmentShader( const std::string &filename ) {
    LoadShader( filename, GL_FRAGMENT_SHADER );
}

void Shader::AddVertexShader( const std::string &filename ) {
    LoadShader( filename, GL_VERTEX_SHADER );
}

void Shader::AttachShader( int shaderID ) const {
    glAttachShader( m_program, shaderID );
}

void Shader::LinkProgram() const {
    glLinkProgram( m_program );
}

void Shader::Bind() const {
    glUseProgram( m_program );
}

void Shader::AddUniform( const std::string &name ) {
    s_uniformMap[ name ] = glGetUniformLocation( m_program, name.c_str() );
}

void Shader::AddAttribute( const std::string &name ) {
    s_attributeMap[ name ] = glGetAttribLocation( m_program, name.c_str() );
}







