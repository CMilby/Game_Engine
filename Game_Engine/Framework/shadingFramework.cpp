//
//  shadingFramework.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "shadingFramework.h"

ShadingFramework::ShadingFramework() {
    m_program = glCreateProgram();
    glGenVertexArrays( 1, &m_vao );
    
    glBindVertexArray( m_vao );
}

ShadingFramework::~ShadingFramework() {
    glDeleteProgram( m_program );
}

void ShadingFramework::AddFragmentShader( const std::string &filename ) {
    LoadShader( filename, GL_FRAGMENT_SHADER );
}

void ShadingFramework::AddVertexShader( const std::string &filename ) {
    LoadShader( filename, GL_VERTEX_SHADER );
}

void ShadingFramework::AttachShader( int shaderID ) const {
    glAttachShader( m_program, shaderID );
}

void ShadingFramework::LinkProgram() const {
    glLinkProgram( m_program );
    CheckShaderError( m_program, GL_LINK_STATUS, true, "Error linking shader program" );
    
    glValidateProgram( m_program );
    CheckShaderError( m_program, GL_VALIDATE_STATUS, true, "Invalid shader program" );
    
    Bind();
}

void ShadingFramework::EnableVertexAttribArray( unsigned int position ) const {
	glEnableVertexAttribArray( position );
}

void ShadingFramework::DisableVertexAttribArray( unsigned int position ) const {
	glDisableVertexAttribArray( position );
}

void ShadingFramework::AddUniform( const std::string &name ) {
    int location = glGetUniformLocation( m_program, name.c_str() );
    
    if( location == INVALID_LOCATION ) {
        fprintf( stderr, "Can't find uniform %s\n", name.c_str() );
        return;
    }
    
    m_uniformMap[ name ] = location;
}

void ShadingFramework::AddAttribute( const std::string &name ) {
    int location = glGetAttribLocation( m_program, name.c_str() );
    
    if( location == INVALID_LOCATION ) {
        fprintf( stderr, "Can't find attribute %s\n", name.c_str() );
        return;
    }
    
    m_attributeMap[ name ] = location;
}

void ShadingFramework::Bind() const {
    glUseProgram( m_program );
}

void ShadingFramework::SetAttribLocation( const std::string &name, int location ) const {
    glBindAttribLocation( m_program, location, name.c_str() );
}

void ShadingFramework::Uniform1ui( const std::string &name, unsigned int value ) const {
    glUniform1ui( m_uniformMap.at( name ), value );
}

void ShadingFramework::Uniform1i( const std::string &name, int value ) const {
    glUniform1i( m_uniformMap.at( name ), value );
}

void ShadingFramework::Uniform1f( const std::string &name, float value ) const {
    glUniform1f( m_uniformMap.at( name ), value );
}

void ShadingFramework::UniformMatrix4f( const std::string &name, const Matrix4<float> &value ) const {
    glUniformMatrix4fv( m_uniformMap.at( name ), 1, GL_FALSE, &value[ 0 ][ 0 ] );
}

void ShadingFramework::Uniform2f( const std::string &name, float x, float y ) const {
    glUniform2f( m_uniformMap.at( name ), x, y );
}

void ShadingFramework::UniformVector3f( const std::string &name, const Vector3<float> &value ) const {
    glUniform3f( m_uniformMap.at( name ), value.GetX(), value.GetY(), value.GetZ() );
}

void ShadingFramework::LoadShader( const std::string &filename, int type ) {
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

void ShadingFramework::CheckShaderError( int shader, int flag, bool isProgram, const std::string& errorMessage ) const {
    GLint success = 0;
    GLchar error[ 1024 ] = { 0 };
    
    if( isProgram ) {
        glGetProgramiv(shader, flag, &success);
    } else {
        glGetShaderiv(shader, flag, &success);
    }
    
    if( !success ) {
        if( isProgram ) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        } else {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }
        
        fprintf( stderr, "%s: '%s'\n", errorMessage.c_str(), error);
    }
}








