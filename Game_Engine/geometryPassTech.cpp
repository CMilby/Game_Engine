//
//  geometryPassTech.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "geometryPassTech.h"

GeometryPassTech::GeometryPassTech() {
    
}

void GeometryPassTech::Init() {
    AddVertexShader( "GeometryPass.vs" );
    AddFragmentShader( "GeometryPass.fs" );
    LinkProgram();
    
    AddUniform( "gWVP" );
    AddUniform( "gWorld" );
    AddUniform( "gColorMap" );
}

void GeometryPassTech::SetWVP( const Matrix4<float> &WVP ) {
    UniformMatrix4f( "gWVP", WVP );
}

void GeometryPassTech::SetWorldMatrix( const Matrix4<float> &WVP ) {
    UniformMatrix4f( "gWorld", WVP );
}

void GeometryPassTech::SetColorTextureUint( unsigned int textureUnit ) {
    Uniform1i( "gColorMap", textureUnit );
}