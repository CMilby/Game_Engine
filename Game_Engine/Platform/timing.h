//
//  timing.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TIMING_H__
#define __TIMING_H__

#include <string>

namespace Timing {
    
    unsigned int GetTimeMillis();
    unsigned int GetTimeMillisSpan( unsigned int pStartTime );
    
    void Delay( int millis );
    
    time_t GetCurrentTime();
};

#endif /* timing_h */
