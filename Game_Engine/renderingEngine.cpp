//
//  renderingEngine.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "renderingEngine.h"

#include "phongShader.h"
#include "basicShader.h"

Camera RenderingEngine::s_mainCamera = Camera();

RenderingEngine::RenderingEngine() {
    
}

RenderingEngine::~RenderingEngine() {
    if ( m_standardShader ) delete m_standardShader;
    if ( m_textShader ) delete m_textShader;
    if ( m_skybox ) delete m_skybox;
}

void RenderingEngine::Init() {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glFrontFace( GL_CCW );
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_DEPTH_CLAMP );
    
    m_standardShader = new PhongShader();
    m_textShader = new TextShader( "Courier_New.png" );
    m_skybox = new Skybox( "", "stars_rt.jpg", "stars_lf.jpg", "stars_up.jpg", "stars_dn.jpg", "stars_fr.jpg", "stars_bk.jpg" );
    
    m_standardShader->Init();
    m_textShader->Init();
    m_skybox->Init();
    
    m_shaders.emplace_back( m_standardShader );
    m_shaders.emplace_back( m_skybox );
}

void RenderingEngine::Render( Entity &root ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    root.RenderAll( m_shaders, s_mainCamera );
    
    char text[ 256 ];
    Vector3<float> pos = s_mainCamera.GetPosition();
    sprintf( text, "%.2f %.2f %.2f", pos.GetX(), pos.GetY(), pos.GetZ() );
    m_textShader->Render( text, 5, 25, 20 );
}





