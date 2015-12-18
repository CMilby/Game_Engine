//
//  renderingEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "renderingEngine.h"

#include "basicShader.h"
#include "deferredShader.h"
#include "phongShader.h"

Camera RenderingEngine::s_mainCamera = Camera();

RenderingEngine::RenderingEngine() {
    m_shader = new PhongShader();
    m_text2d = new Text2D( "Holstein.DDS" );
    m_skybox = new Skybox( "", "stars_rt.jpg", "stars_lf.jpg", "stars_up.jpg", "stars_dn.jpg", "stars_fr.jpg", "stars_bk.jpg" );
    
    m_shaders.emplace_back( m_shader );
    m_shaders.emplace_back( m_skybox );
}

RenderingEngine::~RenderingEngine() {
    if ( m_shader ) delete m_shader;
    if ( m_text2d ) delete m_text2d;
    if ( m_skybox ) delete m_skybox;
}

void RenderingEngine::Init() {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glFrontFace( GL_CCW );
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_DEPTH_CLAMP );
    
    m_shader->Init();
    m_text2d->Init();
    m_skybox->Init();
}

void RenderingEngine::Render( Entity &root ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // root.RenderAll( *m_shader, s_mainCamera );
    // root.RenderAll( *m_skybox, s_mainCamera );
    
    root.RenderAll( m_shaders, s_mainCamera );
    
    char text[ 256 ];
    Vector3<float> pos = s_mainCamera.GetPosition();
    sprintf( text, "%.2f %.2f %.2f", pos.GetX(), pos.GetY(), pos.GetZ() );
    m_text2d->PrintText2D( text, 5, 25, 20 );
}




