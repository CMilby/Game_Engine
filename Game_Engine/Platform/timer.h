//
//  timer.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TIMER_H__
#define __TIMER_H__

#include <thread>

class Timer {
    
private:
    void ( *m_tick )( Timer*, int );
    std::thread m_thread;
    
    int m_startTime;
    int m_interval;
    
    bool m_isRunning;
    bool m_repeats;
    
    void ThreadMethod();
    void Tick();
    
public:
    Timer( int pInterval, void ( *pTick )( Timer*, int ), bool pStart = false );
    virtual ~Timer();
    
    void Start();
    void Stop();
    
    inline bool IsStarted() const { return m_isRunning; }
    
    inline bool Repeats() const { return m_repeats; }
    inline void SetRepets( bool pRepeats ) { m_repeats = pRepeats; }
};

#endif /* timer_h */
