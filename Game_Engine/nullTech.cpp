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
    AddVertexShader( "NullShader.vs" );
    AddFragmentShader( "NullShader.fs" );
    LinkProgram();
    
    AddUniform( "gWVP" );
}

void NullTech::SetWVP( const Matrix4<float> &WVP ) {
    UniformMatrix4f( "gWVP", WVP );
}