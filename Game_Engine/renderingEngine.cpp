//
//  renderingEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "renderingEngine.h"

#include <glm/gtc/matrix_transform.hpp>

RenderingEngine::RenderingEngine() {
    // m_projection = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );
    // m_view = glm::lookAt( glm::vec3( 4, 3, 3 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
    // m_model = glm::mat4( 1.0f );
    
    m_shader = new Shader();
    m_shader->AddVertexShader( "/Users/Craig/Xcode/Game_Engine/Game_Engine/resources/shaders/StandardShading.vertexshader" );
    m_shader->AddFragmentShader( "/Users/Craig/Xcode/Game_Engine/Game_Engine/resources/shaders/StandardShading.fragmentshader" );
    m_shader->LinkProgram();
    
    m_shader->AddUniform( "MVP" );
    m_shader->AddUniform( "V" );
    m_shader->AddUniform( "M" );
    m_shader->AddUniform( "myTextureSampler" );
    m_shader->AddUniform( "LightPosition_worldspace" );
    
    m_shader->AddAttribute( "vertexPosition_modelspace" );
    m_shader->AddAttribute( "vertexUV" );
    m_shader->AddAttribute( "vertexNormal_modelspace" );
    
    printf( "%i\n", ( unsigned int ) m_shader->GetAttribute( "vertexPosition_modelspace" ) );
    printf( "%i\n", ( unsigned int ) m_shader->GetAttribute( "vertexUV" ) );
    printf( "%i\n", ( unsigned int ) m_shader->GetAttribute( "vertexNormal_modelspace" ) );
    
    m_texture = new Texture( "/Users/Craig/Xcode/Game_Engine/Game_Engine/resources/textures/uvmap.DDS" );
}

RenderingEngine::~RenderingEngine() {
    if ( m_shader ) {
        delete m_shader;
    }
    
    if ( m_texture ) {
        delete m_texture;
    }
}

void RenderingEngine::Init() const {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );
}

void RenderingEngine::Render() const {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_shader->Bind();
    
    glm::mat4 MVP = m_projection * m_view * m_model;
    glUniformMatrix4fv( m_shader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[ 0 ][ 0 ] );
    glUniformMatrix4fv( m_shader->GetUniform( "M" ), 1, GL_FALSE, &m_model[ 0 ][ 0 ] );
    glUniformMatrix4fv( m_shader->GetUniform( "V" ), 1, GL_FALSE, &m_view[ 0 ][ 0 ] );
    
    glUniform3f( m_shader->GetUniform( "LightPosition_worldspace" ), 8.0f, 8.0f, 8.0f );
    
    m_texture->Bind();
    glUniform1i( m_shader->GetUniform( "myTextureSampler" ), 0 );
    
    
    /*glEnableVertexAttribArray( 1 );
    
    --> Uniforms
    --> Bind Texture
    --> Render models
     
    glDisableVertexAttribArray( 1 );*/
    
    // Render text
}