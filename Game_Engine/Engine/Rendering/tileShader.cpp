//
//  tileShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/22/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "tileShader.h"

TileShader::TileShader() {
	
}

TileShader::~TileShader() {
	
}

void TileShader::Init() {
	AddVertexShader( "TileShader.vs" );
	AddFragmentShader( "TileShader.fs" );
	
	LinkProgram();
	
	AddUniform( "mvp" );
	AddUniform( "sampler" );
}

void TileShader::Enable() const {
	EnableVertexAttribArray( 0 );
}

void TileShader::Disable() const {
	DisableVertexAttribArray( 0 );
}

void TileShader::UpdateUniforms( const Matrix4<float> &pMVP, const Material &pMaterial ) {
	pMaterial.m_texture->Bind( GL_TEXTURE0, GL_TEXTURE_2D_ARRAY );
	Uniform1i( "sampler", 0 );
	UniformMatrix4f( "mvp", pMVP );
}