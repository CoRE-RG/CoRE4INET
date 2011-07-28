/*
 * ScheduleInfo.h
 *
 *  Created on: Mar 4, 2011
 *      Author: root
 */

#ifndef SCHEDULEINFO_H_
#define SCHEDULEINFO_H_

#include <stdint.h>

class ScheduleInfo
{
//public:
//	ScheduleInfo();
//	~ScheduleInfo();

private:
	u_int16_t _ctID;
	u_int64_t _windowStart;
	u_int64_t _windowEnd;

public:
	void setCTID(u_int16_t ctID){
		_ctID = ctID;
	}
	u_int16_t getCTID(){
		return _ctID;
	}

	void setWindowStart(u_int64_t windowStart){
		_windowStart = windowStart;
	}
	u_int64_t getWindowStart(){
		return _windowStart;
	}

	void setWindowEnd(u_int64_t windowEnd){
		_windowEnd = windowEnd;
	}
	u_int64_t getWindowEnd(){
		return _windowEnd;
	}
};

#endif /* SCHEDULEINFO_H_ */
