//
//  main.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>

#include "coreEngine.h"
#include "input.h"
#include "window.h"

int main(int argc, const char * argv[]) {
    Window *window = new Window( 1024, 768, "Window Title" );
    Input::SetWindow( *window );
    
    CoreEngine coreEngine( window );
    coreEngine.Init();
    coreEngine.Start();
}
