//
//  voxelShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/21/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "voxelShader.h"

VoxelShader::VoxelShader() {
	
}

VoxelShader::~VoxelShader() {
	
}

void VoxelShader::Init() {
	AddVertexShader( "VoxelShader.vs" );
	AddFragmentShader( "VoxelShader.fs" );
	
	LinkProgram();
	
	AddUniform( "model" );
	AddUniform( "view" );
	AddUniform( "projection" );
	AddUniform( "sampler" );
}

void VoxelShader::Enable() const {
	EnableVertexAttribArray( 0 );
}

void VoxelShader::Disable() const {
	DisableVertexAttribArray( 0 );
}

void VoxelShader::UpdateUniforms( const Matrix4<float> &pModel, const Matrix4<float> &pView , const Matrix4<float> &pProjection, Texture *pTexture ) {
	pTexture->Bind( GL_TEXTURE0, GL_TEXTURE_2D_ARRAY );
	Uniform1i( "sampler", 0 );
	
	UniformMatrix4f( "model", pModel );
	UniformMatrix4f( "view", pView );
	UniformMatrix4f( "projection", pProjection );
}