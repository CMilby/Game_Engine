//
//  planetShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "planetShader.h"

PlanetShader::PlanetShader() {
    
}

PlanetShader::~PlanetShader() {
    
}

void PlanetShader::Init() {
    AddVertexShader( "PlanetShader.vs" );
    AddFragmentShader( "PlanetShader.fs" );
    LinkProgram();
    
    // AddUniform( "transform" );
    AddUniform( "transformProjected" );
}

void PlanetShader::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) {
    // UniformMatrix4f( "transform", world );
    UniformMatrix4f( "transformProjected", projected );
}