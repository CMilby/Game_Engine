//
//  geometryShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "geometryShader.h"

GeometryShader::GeometryShader() {
    
}

GeometryShader::~GeometryShader() {
    
}

void GeometryShader::Init() {
    AddVertexShader( "GeometryShader.vs" );
    AddFragmentShader( "GeometryShader.fs" );
    LinkProgram();
    
    AddUniform( "model" );
    AddUniform( "view" );
    AddUniform( "projection" );
    AddUniform( "textureDiffuse" );
    AddUniform( "textureSpecular" );
}