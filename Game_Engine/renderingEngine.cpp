//
//  renderingEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "renderingEngine.h"

#include "basicShader.h"
#include "geometryPassTech.h"
#include "phongShader.h"

Camera RenderingEngine::s_mainCamera = Camera();

RenderingEngine::RenderingEngine() {
    m_shader = new PhongShader();
    // m_geomPass = new GeometryPassTech();
    // m_gBuffer = new GBuffer();
    m_text2d = new Text2D( "Holstein.DDS" );
}

RenderingEngine::~RenderingEngine() {
    if ( m_shader ) delete m_shader;
}

void RenderingEngine::Init() {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );
    
    m_shader->Init();

    // m_gBuffer->Init( 1024, 768 );
    
    /*m_geomPass->Init();
    m_geomPass->Enable();
    m_geomPass->SetColorTextureUint( COLOR_TEXTURE_UNIT_INDEX );*/
    
    m_text2d->Init();
}

void RenderingEngine::Render( Entity &root ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_shader->Enable();
    root.RenderAll( *m_shader, s_mainCamera );
    m_shader->Disable();
    
    char text[ 256 ];
    Vector3<float> pos = s_mainCamera.GetPosition();
    sprintf( text, "%.2f %.2f %.2f", pos.GetX(), pos.GetY(), pos.GetZ() );
    m_text2d->PrintText2D( text, 5, 25, 20 );
}









