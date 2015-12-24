//
//  lightShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "lightShader.h"

LightShader::LightShader() {
    
}

LightShader::~LightShader() {
    
}

void LightShader::Init() {
    AddUniform( "gWVP" );
    AddUniform( "gPositionMap" );
    AddUniform( "gColorMap" );
    AddUniform( "gNormalMap" );
    AddUniform( "gEyeWorldPos" );
    AddUniform( "gMatSpecularIntensity" );
    AddUniform( "gSpecularPower" );
    AddUniform( "gScreenSize" );
}