//
//  utility.h
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <string>

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

namespace Utility {
  
    void PrintCurrentPath();
    
    std::string DirectoryPath();
    
    unsigned int GetMonitorWidth();
    unsigned int GetMonitorHeight();
    
    unsigned int ScreenHalfWidth();
    unsigned int ScreenHalfHeight();
};

#endif /* utility_h */
