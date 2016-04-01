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
#include <sys/timeb.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

int Timing::GetTimeMillis() {
    return SDL_GetTicks();
}

void Timing::Delay( int millis ) {
    SDL_Delay( millis );
}

time_t Timing::GetCurrentTime() {
	return time( 0 );
}

