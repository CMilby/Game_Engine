//
//  render_framework.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "render_framework.h"

#include <GL/glew.h>

void RenderFramework::InitRenderer() {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glFrontFace( GL_CCW );
    glCullFace( GL_BACK );
    
    glEnable( GL_CULL_FACE );
    glEnable( GL_TEXTURE_2D );
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_DEPTH_CLAMP );
    
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
}

void RenderFramework::ClearScreen() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void RenderFramework::SetDrawMode( int p_mode ) {
    if ( p_mode == 1 ) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    } else if ( p_mode == 2 ) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
}
