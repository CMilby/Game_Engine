//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "input.h"
#include "math3d.h"
#include "mesh.h"
#include "renderingEngine.h"
#include "text2d.h"
#include "window.h"

int main(int argc, const char * argv[]) {
    Window *window = new Window( 1024, 768, "Window Title" );
    RenderingEngine *renderingEngine = new RenderingEngine();
    
    Input *input = new Input( window );
    Text2D *text = new Text2D( "Holstein.DDS" );
    
    renderingEngine->Init();
    text->InitText2D();
    
    do {
        renderingEngine->Render();
        
        text->PrintText2D( "Hello World!" , 10, 500, 30 );
        
        window->SwapBuffers();
        window->PollEvents();
    } while ( window->GetKey( GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
              window->ShouldClose() );
    
    delete text;
    delete input;
    delete renderingEngine;
    delete window;
}
