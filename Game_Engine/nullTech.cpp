//
//  nullTech.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "nullTech.h"

NullTech::NullTech() {
    
}

NullTech::~NullTech() {
    
}

void NullTech::Init() {
    AddVertexShader( "null_technique.vs" );
    AddFragmentShader( "null_technique.fs" );
    LinkProgram();
    
    AddUniform( "gWVP" );
}

void NullTech::SetWVP( const Matrix4<float> &WVP ) {
    UniformMatrix4f( "gWVP", WVP );
}