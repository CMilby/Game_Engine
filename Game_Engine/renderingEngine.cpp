//
//  renderingEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "renderingEngine.h"

Camera RenderingEngine::s_mainCamera = Camera();

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
    
    m_text2d = new Text2D( "Holstein.DDS" );
}

RenderingEngine::~RenderingEngine() {
    if ( m_shader ) delete m_shader;
}

void RenderingEngine::Init() const {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );
    
    m_text2d->Init();
}

void RenderingEngine::Render( Entity &root ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_shader->Bind();
    glUniform3f( m_shader->GetUniform( "LightPosition_worldspace" ), 8.0f, 8.0f, 8.0f );
    
    Matrix4<float> view = s_mainCamera.GetView();
    m_shader->UniformMatrix4f( "V", view);
    
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexPosition_modelspace" ) );
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexUV" ) );
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexNormal_modelspace" ) );
    
    root.RenderAll( *m_shader, s_mainCamera );
    
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexPosition_modelspace" ) );
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexUV" ) );
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexNormal_modelspace" ) );
    
    char text[ 256 ];
    Vector3<float> pos = s_mainCamera.GetPosition();
    sprintf( text, "%.2f %.2f %.2f", pos.GetX(), pos.GetY(), pos.GetZ() );
    m_text2d->PrintText2D( text, 5, 25, 20 );
}









