//
//  basicShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/10/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "basicShader.h"

BasicShader::BasicShader() {
    
}

BasicShader::~BasicShader() {
    
}

void BasicShader::Init() {
    AddVertexShader( "StandardShading.vs" );
    AddFragmentShader( "StandardShading.fs" );
    
    LinkProgram();
    
    AddUniform( "MVP" );
    AddUniform( "V" );
    AddUniform( "M" );
    AddUniform( "myTextureSampler" );
    AddUniform( "LightPosition_worldspace" );
}

void BasicShader::Enable() const {
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
}

void BasicShader::Disable() const {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
}

void BasicShader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) {
    UniformVector3f ( "LightPosition_worldspace", Vector3<float>( 8.0f, 8.0f, 8.0f ) );
    UniformMatrix4f( "V", camera.GetView() );
    
    material.m_texture->Bind();
    Uniform1i( "myTextureSampler", 0 );
    
    UniformMatrix4f( "MVP", projected );
    UniformMatrix4f( "M", world );
}