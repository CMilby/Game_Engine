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
    
	AddUniform( "mvp" );
    AddUniform( "sampler" );
}

void BasicShader::UpdateUniforms( const Matrix4<float> &pMVP, const Material &material ) {
    material.m_texture->Bind();
	Uniform1i( "sampler", 0 );
    UniformMatrix4f( "mvp", pMVP );
}





