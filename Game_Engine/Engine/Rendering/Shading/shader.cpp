//
//  shader.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "shader.h"

#include "file_utility.h"
#include "logger.h"

Shader::Shader( ShaderType::ShaderType p_type ) : m_type( p_type ) {
    m_program = glCreateProgram();
    glGenVertexArrays( 1, &m_vao );
    
    glBindVertexArray( m_vao );
}

Shader::~Shader() {
    glDeleteProgram( m_program );
}

void Shader::AddFragmentShader( const std::string &p_filename ) {
    LoadShader( p_filename, GL_FRAGMENT_SHADER );
}

void Shader::AddVertexShader( const std::string &p_filename ) {
    LoadShader( p_filename, GL_VERTEX_SHADER );
}

void Shader::AttachShader( int p_shaderID ) const {
    glAttachShader( m_program, p_shaderID );
}

void Shader::LinkProgram() const {
    glLinkProgram( m_program );
    CheckShaderError( m_program, GL_LINK_STATUS, true, "Error linking shader program" );
    
    glValidateProgram( m_program );
    CheckShaderError( m_program, GL_VALIDATE_STATUS, true, "Invalid shader program" );
    
    Bind();
}

void Shader::EnableVertexAttribArray( unsigned int p_position ) const {
    glEnableVertexAttribArray( p_position );
}

void Shader::DisableVertexAttribArray( unsigned int p_position ) const {
    glDisableVertexAttribArray( p_position );
}

void Shader::Bind() const {
    glUseProgram( m_program );
}

void Shader::UpdateUniforms( const Matrix4f &p_world, const Matrix4f &p_projected, const Entity &p_camera, const Material &p_material ) {
    
}

void Shader::UpdateUniforms( const Matrix4f &p_MVP, const Material &p_material ) {
    
}

void Shader::UpdateUniforms( const Matrix4f &p_model, const Matrix4f &p_view , const Matrix4f &p_projection, Texture *p_texture ) {
    
}

void Shader::AddUniform( const std::string &p_name ) {
    int myLocation = glGetUniformLocation( m_program, p_name.c_str() );
    
    if ( myLocation == INVALID_LOCATION ) {
        Logger::LogSevere( "Shader - AddUniform", "Could not find uniform: " + p_name );
        return;
    }
    
    m_uniformMap.insert( std::pair<std::string, GLuint>( p_name, myLocation ) );
}

GLuint Shader::GetUniform( const std::string &p_name ) const {
    return m_uniformMap.at( p_name );
}

void Shader::AddAttribute( const std::string &p_name ) {
    int myLoaction = glGetAttribLocation( m_program, p_name.c_str() );
    
    if ( myLoaction == INVALID_LOCATION ) {
        Logger::LogSevere( "Shader - AddAttribute", "Could not find attribute: " + p_name );
        return;
    }
    
    m_attributeMap.insert( std::pair<std::string, GLuint>( p_name, myLoaction ) );
}

GLuint Shader::GetAttribute( const std::string &p_name ) const {
    return m_attributeMap.at( p_name );
}

void Shader::SetAttribLocation( const std::string &p_name, int p_location ) const {
    glBindAttribLocation( m_program, p_location, p_name.c_str() );
}

void Shader::Uniform1ui( const std::string &p_name, unsigned int p_value ) const {
    glUniform1ui( m_uniformMap.at( p_name ), p_value );
}

void Shader::Uniform1i( const std::string &p_name, int p_value ) const {
    glUniform1i( m_uniformMap.at( p_name ), p_value );
}

void Shader::Uniform1f( const std::string &p_name, float p_value ) const {
    glUniform1f( m_uniformMap.at( p_name ), p_value );
}

void Shader::UniformMatrix4f( const std::string &p_name, const Matrix4f &p_value ) const {
    glUniformMatrix4fv( m_uniformMap.at( p_name ), 1, GL_FALSE, &p_value[ 0 ][ 0 ] );
}

void Shader::Uniform2f( const std::string &p_name, float p_x, float p_y ) const {
    glUniform2f( m_uniformMap.at( p_name ), p_x, p_y );
}

void Shader::UniformVector3f( const std::string &p_name, const Vector3f &p_value ) const {
    glUniform3f( m_uniformMap.at( p_name ), p_value.GetX(), p_value.GetY(), p_value.GetZ() );
}

void Shader::LoadShader( const std::string &p_filename, int p_type ) {
    GLuint shaderID = glCreateShader( p_type );
    
    std::string shaderCode;
    std::ifstream shaderStream( FileUtility::GetShaderDirectory() + p_filename, std::ios::in );
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

void Shader::CheckShaderError( int p_shader, int p_flag, bool p_isProgram, const std::string &p_errorMessage ) const {
    GLint success = 0;
    GLchar error[ 1024 ] = { 0 };
    
    if( p_isProgram ) {
        glGetProgramiv( p_shader, p_flag, &success );
    } else {
        glGetShaderiv( p_shader, p_flag, &success );
    }
    
    if( !success ) {
        if( p_isProgram ) {
            glGetProgramInfoLog( p_shader, sizeof( error ), NULL, error );
        } else {
            glGetShaderInfoLog( p_shader, sizeof( error ), NULL, error );
        }
        
        fprintf( stderr, "%s: '%s'\n", p_errorMessage.c_str(), error);
    }
}







