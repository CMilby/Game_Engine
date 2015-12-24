//
//  deferredShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "deferredShader.h"

DeferredShader::DeferredShader() {
    m_gBuffer = new GBuffer();
    m_geomShader = new GeometryShader();
    m_lightShader = new LightingShader();
}

DeferredShader::~DeferredShader() {
    if ( m_gBuffer ) delete m_gBuffer;
    if ( m_geomShader ) delete m_geomShader;
    if ( m_lightShader ) delete m_lightShader;
}

void DeferredShader::Init() {
    m_gBuffer->Init();
    m_geomShader->Init();
    m_lightShader->Init();
    
    Light light;
    light.m_color = Vector3<float>( 0, 1, 0 );
    light.m_position = Vector3<float>( -3, 0, 0 );
    m_lights.push_back( light );
}

void DeferredShader::Render( const Camera &camera, const RenderableEntity &entity ) {
    m_gBuffer->BindGeom();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    m_geomShader->Bind();
    m_geomShader->UniformMatrix4f( "projection", Transform::GetProjection() );
    m_geomShader->UniformMatrix4f( "view", camera.GetView() );
    m_geomShader->UniformMatrix4f( "model", entity.GetModelMatrix() );
    entity.GetMesh().Render();
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    m_lightShader->Bind();
    m_gBuffer->BindLight();
    for ( int i = 0; i < m_lights.size(); i++ ) {
        std::string name = "lights[" + std::to_string( i ) + "]";
        m_lightShader->UniformVector3f( name + ".position", m_lights[ i ].m_position );
        m_lightShader->UniformVector3f( name + ".color", m_lights[ i ].m_color );
        m_lightShader->Uniform1f( name + ".linear", 0.7f );
        m_lightShader->Uniform1f( name + ".quadratic", 1.8f );
    }
    
    m_lightShader->UniformVector3f( "viewPos", camera.GetPosition() );
    
    RenderQuad();
}

void DeferredShader::RenderQuad() {
    if ( quadVAO == 0 ) {
        GLfloat quadVertices[] = {
            // Positions        // Texture Coords
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        
        glGenVertexArrays( 1, &quadVAO );
        glGenBuffers( 1, &quadVBO );
        
        glBindVertexArray( quadVAO );
        glBindBuffer( GL_ARRAY_BUFFER, quadVBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( quadVertices ), &quadVertices, GL_STATIC_DRAW );
    
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid* ) 0 );
        
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), ( GLvoid* ) ( 3 * sizeof( GLfloat ) ) );
    }
    
    glBindVertexArray( quadVAO );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    glBindVertexArray( 0 );
}



















