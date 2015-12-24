//
//  lightingShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "lightingShader.h"

LightingShader::LightingShader() {
    
}

LightingShader::~LightingShader() {
    
}

void LightingShader::Init() {
    AddVertexShader( "DeferredShading.vs" );
    AddFragmentShader( "DeferredShading.fs" );
    LinkProgram();
    
    AddUniform( "gPosition" );
    AddUniform( "gNormal" );
    AddUniform( "gSpecular" );
    AddUniform( "viewPos" );
    
    for ( int i = 0; i < 32; i++ ) {\
        std::string name = "lights[" + std::to_string( i ) + "]";
        AddUniform( name + ".color" );
        AddUniform( name + ".position" );
        AddUniform( name + ".linear" );
        AddUniform( name + ".quadratic" );
    }
}