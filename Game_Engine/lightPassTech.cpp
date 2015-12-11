//
//  lightPassTech.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "lightPassTech.h"

LightPassTech::LightPassTech() {
    
}

void LightPassTech::Init() {
    AddUniform( "gWVP" );
    AddUniform( "gPositionMap" );
    AddUniform( "gColorMap" );
    AddUniform( "gNormalMap" );
    AddUniform( "gEyeWorldPos" );
    AddUniform( "gMatSpecularIntensity" );
    AddUniform( "gSpecularPower" );
    AddUniform( "gScreenSize" );
}

void LightPassTech::SetWVP( const Matrix4<float> &WVP ) {
    UniformMatrix4f( "gWVP", WVP );
}

void LightPassTech::SetPositionTextureUnit( unsigned int textureUnit ) {
    Uniform1i( "gPositionMap", textureUnit );
}

void LightPassTech::SetColorTextureUnit( unsigned int textureUnit ) {
    Uniform1i( "gColorMap", textureUnit );
}

void LightPassTech::SetNormalTextureUnit( unsigned int textureUnit ) {
    Uniform1i( "gNormalMap", textureUnit );
}

void LightPassTech::SetEyeWorldPos( const Vector3<float> &pos ) {
    UniformVector3f( "gEyeWorldPos", pos );
}

void LightPassTech::SetScreenSize( unsigned int width, unsigned int height ) {
    Uniform2f( "gScreenSize", width, height );
}