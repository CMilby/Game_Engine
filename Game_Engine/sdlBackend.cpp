//
//  sdlBackend.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "sdlBackend.h"

static bool s_isCloseRequested = false;

bool SDLIsCloseRequested() {
    return s_isCloseRequested;
}

void SDLSetIsCloseRequested( bool value ) {
    s_isCloseRequested = value;
}