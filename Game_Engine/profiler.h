//
//  profiler.h
//  Game_Engine
//
//  Created by Craig Milby on 1/19/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PROFILER_H__
#define __PROFILER_H__

#include <string>

#include "time.h"

class Profiler {
    
private:
    float m_startTime;
    float m_stopTime;
    bool m_profiling;
    
public:
    Profiler();
    virtual ~Profiler();
    
    void StartProfile();
    void StopProfile();
    
    std::string ToString();
};

#endif /* profiler_h */
