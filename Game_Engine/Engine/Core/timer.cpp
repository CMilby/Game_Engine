//
//  timer.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "timer.h"

#include <chrono>

#include "time.h"

Timer::Timer( int pInterval, void ( *pTick )( Timer*, int ), bool pStart ) {
	m_interval = pInterval;
	m_tick = pTick;
	m_isRunning = pStart;
	
	if ( pStart ) {
		m_startTime = Timing::GetTimeMillis();
		m_thread = std::thread( &Timer::ThreadMethod, this );
	}
}

Timer::~Timer() {
	Stop();
}

void Timer::ThreadMethod() {
	if ( !m_repeats ) {
		this->Tick();
	} else {
		while ( m_isRunning ) {
			this->Tick();
		}
	}
}

void Timer::Tick() {
	std::this_thread::sleep_for( std::chrono::milliseconds( m_interval ) );
	
	if ( m_isRunning ) {
		m_tick( this, Timing::GetTimeMillis() - m_interval );
	}
}

void Timer::Start() {
	if ( m_isRunning ) {
		return;
	}
	
	m_startTime = Timing::GetTimeMillis();
	m_isRunning = true;
	m_thread = std::thread( &Timer::ThreadMethod, this );
}

void Timer::Stop() {
	if ( !m_isRunning ) {
		return;
	}
	
	m_isRunning = false;
	m_thread.join();
}