//
//  time.h
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __TIME_H__
#define __TIME_H__

#include <string>

namespace Timing {
    
    unsigned int GetTimeMillis();
	unsigned int GetTimeMillisSpan( unsigned int pStartTime );
	
    void Delay( int millis );
    
	time_t GetCurrentTime();
};

#endif /* time_h */
