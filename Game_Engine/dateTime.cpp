//
//  dateTime.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "dateTime.h"

DateTime::DateTime() {
	m_now = Timing::GetCurrentTime();
	m_time = localtime( &m_now );
}

DateTime::DateTime( const time_t &time ) {
	m_now = time;
	m_time = localtime( &m_now );
}

int DateTime::GetYear() const {
	return 1900 + m_time->tm_year;
}

int DateTime::GetMonth() const {
	return m_time->tm_mon;
}

int DateTime::GetDay() const {
	return m_time->tm_mday;
}

int DateTime::GetHour() const {
	return m_time->tm_hour;
}

int DateTime::GetMinute() const {
	return m_time->tm_min;
}

int DateTime::GetSecond() const {
	return m_time->tm_sec;
}

std::string DateTime::ToString() const {
	return std::string( ctime( &m_now ) );
}








