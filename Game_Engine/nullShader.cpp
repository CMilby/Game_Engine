//
//  nullShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "nullShader.h"

NullShader::NullShader() {
    
}

NullShader::~NullShader() {
    
}

void NullShader::Init() {
    AddVertexShader( "NullShader.vs" );
    AddFragmentShader( "NullShader.fs" );
    LinkProgram();
    
    AddUniform( "gWVP" );
}

void NullShader::Enable() {
    glEnableVertexAttribArray( 0 );
}

void NullShader::Disable() {
    glDisableVertexAttribArray( 1 );
}