//
//  profiler.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/19/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "profiler.h"

#include "config.h"
#include "logging.h"

Profiler::Profiler() {
    m_profiling = false;
}

Profiler::~Profiler() {
    
}

void Profiler::StartProfile() {
    m_startTime = Timing::GetTime();
    m_profiling = true;
}

void Profiler::StopProfile() {
    m_stopTime = Timing::GetTime();
    m_profiling = false;
}

std::string Profiler::ToString() {
    float time = m_stopTime - m_startTime;
    // time /= 100.0f;
    return std::to_string( time ) + " ms";
}

void Profiler::Profile( const std::string &function, const std::string &message ) {
    if ( Config::Debug() ) {
        Logging::LogInfo( function, message + ToString(), 0 );
    }
}