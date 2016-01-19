//
//  time.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "time.h"

#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <sys/time.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

float Timing::GetTime() {
#ifdef __APPLE__
    timeval time;
    gettimeofday( &time, NULL );
    // return ( float ) ( ( time.tv_sec * 1000 ) + ( time.tv_usec / 1000 ) );
    return SDL_GetTicks();
#endif
#ifdef _WIN32
    SYSTEMTIME time;
    GetSystemTime( &time );
    return ( float ) ( ( time.wSeconds * 1000 ) + time.wMilliseconds );
#endif
    return -1.0f;
}