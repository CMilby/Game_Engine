//
//  deferredShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "deferredShader.h"

DeferredShader::DeferredShader() {
    m_gBuffer = new GBuffer();
}

DeferredShader::~DeferredShader() {
    if ( m_gBuffer ) delete m_gBuffer;
}

void DeferredShader::Init() {
    m_gBuffer->Init();
}

void DeferredShader::Render() {
    
}