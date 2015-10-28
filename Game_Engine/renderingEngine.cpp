//
//  renderingEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "renderingEngine.h"

RenderingEngine::RenderingEngine() {
    m_shader = new Shader();
    m_shader->AddVertexShader( "StandardShading.vertexshader" );
    m_shader->AddFragmentShader( "StandardShading.fragmentshader" );
    m_shader->LinkProgram();
    
    m_shader->AddUniform( "MVP" );
    m_shader->AddUniform( "V" );
    m_shader->AddUniform( "M" );
    m_shader->AddUniform( "myTextureSampler" );
    m_shader->AddUniform( "LightPosition_worldspace" );
    
    m_shader->AddAttribute( "vertexPosition_modelspace" );
    m_shader->AddAttribute( "vertexUV" );
    m_shader->AddAttribute( "vertexNormal_modelspace" );
    
    m_camera = new Camera( Vector3<float>( 0, 0, 5 ) );
    
    m_monkey = new RenderableEntity( "suzanne.obj", "suzanne.DDS" );
    m_monkey->SetPosition( Vector3<float>( -3, 0, 0 ) );
    
    m_cube = new RenderableEntity( "cube.obj", "cube.DDS" );
    m_cube->SetPosition( Vector3<float>( 3, 0, 0 ) );
}

RenderingEngine::~RenderingEngine() {
    if ( m_shader ) delete m_shader;
    if ( m_camera ) delete m_camera;
    if ( m_monkey ) delete m_monkey;
}

void RenderingEngine::Init() const {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );
}

void RenderingEngine::Render( const Entity &renderRoot ) const {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_shader->Bind();
    glUniform3f( m_shader->GetUniform( "LightPosition_worldspace" ), 8.0f, 8.0f, 8.0f );
    
    Matrix4<float> view = m_camera->GetView();
    m_shader->UniformMatrix4f( "V", view);
    
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexPosition_modelspace" ) );
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexUV" ) );
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexNormal_modelspace" ) );
    
    renderRoot.RenderAll( *m_shader, *m_camera );
    
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexPosition_modelspace" ) );
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexUV" ) );
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexNormal_modelspace" ) );
}









