//
//  renderer.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderFramework.h"

#include <GL/glew.h>

void RenderFramework::InitRenderer() {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glFrontFace( GL_CCW );
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_DEPTH_CLAMP );
}

void RenderFramework::ClearScreen() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}