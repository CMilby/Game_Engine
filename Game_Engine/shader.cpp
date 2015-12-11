//
//  shader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "shader.h"

#include <cassert>
#include <fstream>
#include <vector>

#include "utility.h"

static void checkShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);

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
    if ( !result ) {
        fprintf( stderr, "Failed to compile shader\n" );
    }
    
    glGetShaderiv( shaderID, GL_INFO_LOG_LENGTH, &infoLogLength );
    
    std::vector<char> shaderErrorMessage( infoLogLength );
    glGetShaderInfoLog( shaderID, infoLogLength, NULL, &shaderErrorMessage[ 0 ] );
    if ( shaderErrorMessage.size() > 0 ) {
        fprintf( stdout, "%s\n", &shaderErrorMessage[ 0 ] );
    }
    
    AttachShader( shaderID );
}

void Shader::AddFragmentShader( const std::string &filename ) {
    LoadShader( Utility::DirectoryPath() + "shaders/" + filename, GL_FRAGMENT_SHADER );
}

void Shader::AddVertexShader( const std::string &filename ) {
    LoadShader( Utility::DirectoryPath() + "shaders/" + filename, GL_VERTEX_SHADER );
}

void Shader::AttachShader( int shaderID ) const {
    glAttachShader( m_program, shaderID );
}

void Shader::LinkProgram() const {
    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    
    glValidateProgram(m_program);
    checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

void Shader::Bind() const {
    glUseProgram( m_program );
}

void Shader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) {
    
}

void Shader::AddUniform( const std::string &name ) {
    int location = glGetUniformLocation( m_program, name.c_str() );
    
    if( location == INVALID_LOCATION ) {
        fprintf( stderr, "Can't find uniform %s\n", name.c_str() );
        return;
    }
    
    s_uniformMap[ name ] = location;
}

void Shader::AddAttribute( const std::string &name ) {
    int location = glGetAttribLocation( m_program, name.c_str() );
    
    // printf( "%s %i\n", name.c_str(), location );
    
    if( location == INVALID_LOCATION ) {
        fprintf( stderr, "Can't find attribute %s\n", name.c_str() );
        return;
    }
    
    s_attributeMap[ name ] = location;
}

void Shader::SetAttribLocation( const std::string &name, int location ) const {
    glBindAttribLocation( m_program, location, name.c_str() );
}

void Shader::Uniform1i( const std::string &name, int value ) const {
    glUniform1i( s_uniformMap[ name ], value );
}

void Shader::Uniform1f( const std::string &name, float value ) const {
    glUniform1f( s_uniformMap[ name ], value );
}

void Shader::UniformMatrix4f( const std::string &name, const Matrix4<float> &value ) const {
    glUniformMatrix4fv( s_uniformMap[ name ], 1, GL_FALSE, &value[ 0 ][ 0 ] );
}

void Shader::UniformVector3f( const std::string &name, const Vector3<float> &value ) const {
    glUniform3f( s_uniformMap[ name ], value.GetX(), value.GetY(), value.GetZ() );
}

static void checkShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage) {
    GLint success = 0;
    GLchar error[1024] = { 0 };
    
    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);
    
    if(!success)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        fprintf( stderr, "%s: '%s'\n", errorMessage.c_str(), error);
        // printf( "%s: '%s'\n", errorMessage, error );
    }
}













