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
    
    AddUniform( "gWVP" );
    AddUniform( "gWorld" );
    AddUniform( "gColorMap" );
}

void GeometryShader::Enable() {
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
}

void GeometryShader::Disable() {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
}