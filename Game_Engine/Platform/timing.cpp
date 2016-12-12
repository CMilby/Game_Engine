//
//  timing.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "timing.h"

#include <SDL2/SDL.h>

unsigned int Timing::GetTimeMillis() {
    return SDL_GetTicks();
}

unsigned int Timing::GetTimeMillisSpan( unsigned int pStartTime ) {
    int mySpan = Timing::GetTimeMillis() - pStartTime;
    if ( mySpan < 0 ) {
        mySpan += 0x100000 * 1000;
    }
    
    return ( unsigned int ) mySpan;
}

void Timing::Delay( int millis ) {
    SDL_Delay( millis );
}

time_t Timing::GetCurrentTime() {
    return time( 0 );
}
