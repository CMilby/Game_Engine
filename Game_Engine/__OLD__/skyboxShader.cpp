//
//  skybox.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/17/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "skyboxShader.h"

Skybox::Skybox( const std::string &directory,
               const std::string &posX,
               const std::string &negX,
               const std::string &posY,
               const std::string &negY,
               const std::string &posZ,
               const std::string &negZ ) {
    m_cubemapTexture = new CubeMapTexture( directory,
                                          posX, negX,
                                          posY, negY,
                                          posZ, negZ );
}

Skybox::~Skybox() {
    if ( m_cubemapTexture ) delete m_cubemapTexture;
}

void Skybox::Init() {
    AddVertexShader( "Skybox.vs" );
    AddFragmentShader( "Skybox.fs" );
    LinkProgram();
    
    Bind();
    AddUniform( "projected" );
    AddUniform( "skybox" );
    
    if ( !m_cubemapTexture->Load() ) {
        fprintf( stderr, "Could not load cubemap" );
        return;
    }
    
    m_skybox = new Mesh( "sphere.obj" );
}

void Skybox::Enable() const {
    glEnableVertexAttribArray( 0 );
}

void Skybox::Disable() const {
    glDisableVertexAttribArray( 0 );
}

void Skybox::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected,  const Camera &camera, const Material &material ) {
    GLint oldCullFaceMode;
    glGetIntegerv( GL_CULL_FACE_MODE, &oldCullFaceMode );
    
    GLint oldDepthFuncMode;
    glGetIntegerv( GL_DEPTH_FUNC, &oldDepthFuncMode );
    
    glCullFace( GL_FRONT );
    glDepthFunc( GL_LEQUAL );
    
    UniformMatrix4f( "projected", Transform::GetProjection() * camera.GetView() * Matrix4<float>().Model( camera.GetPosition(), Vector3<float>( 1.0f, 1.0f, 1.0f ) ) );
    m_cubemapTexture->Bind( GL_TEXTURE0 );
    
    Enable();
    m_skybox->Render();
    Disable();

    glCullFace( oldCullFaceMode );
    glDepthFunc( oldDepthFuncMode );
}















