//
//  dateTime.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

#include "time.h"

class DateTime {
	
private:
	time_t m_now;
	tm *m_time;
	
public:
	DateTime();
	DateTime( const time_t &time );
	
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	
	std::string ToString() const;
};

#endif /* dateTime_h */
