//
//  dateTime.cpp
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "dateTime.h"

#include <algorithm>

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

void DateTime::AddYear( int years ) {
	
}

void DateTime::AddMonth( int months ) {
	
}

void DateTime::AddDay( int days ) {
	
}

void DateTime::AddHour( int hours ) {
	
}

void DateTime::AddMinute( int minutes ) {
	
}

void DateTime::AddSeconds( int seconds ) {
	
}

std::string DateTime::ToString() const {
    std::string time = std::string( ctime( &m_now ) );
    time.erase( std::remove( time.begin(), time.end(), '\n' ), time.end() );
    return time;
}

/* Format:
 * Year: Y
 * Month: M
 * Day: D
 * Hour: H
 * Minute: m
 * Second: s
 */
std::string DateTime::ToString( const std::string &format ) const {
	std::string time = "";
	for ( int i = 0; i < format.size(); i++ ) {
		switch ( format[ i ] ) {
			case 'Y':
                time += std::to_string( GetYear() );
				break;
			case 'M':
                time += std::to_string( GetMonth() );
				break;
			case 'D':
                time += std::to_string( GetDay() );
				break;
			case 'H':
                time += std::to_string( GetHour() );
				break;
            case 'm': {
                std::string min = std::to_string( GetMinute() );
                if ( min.size() == 1 ) {
                    min = "0" + min;
                }
                time += min;
				break;
            }
            case 's': {
                std::string sec = std::to_string( GetSecond() );
                if ( sec.size() == 1 ) {
                    sec = "0" + sec;
                }
                time += sec;
				break;
            }
			default:
				time += format[ i ];
		}
	}
	return time;
}








