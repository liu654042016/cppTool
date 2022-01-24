//#pragma once
#ifndef _RUNTIME_H_
#define _RUNTIME_H_
#define __WIN32__


#include <iostream>
#ifdef __WIN32__
#include <windows.h>
#else
#include<cstring>
#include <time.h>
#include <sys/time.h>
#endif // __WIN32__

class RuningTimer {
public:
	typedef struct tagTimeval {
		int sec;
		long msec;
		long usec;
	} Timeval;

public:
	Timeval* costTime;
	RuningTimer() {
		costTime =  new Timeval ;
		memset(costTime, 0, sizeof(Timeval));
#ifdef __WIN32__
        //BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
        //精度us
        LARGE_INTEGER tmp;
        QueryPerformanceFrequency(&tmp);
        freq_ = tmp.QuadPart;
#else

#endif // __WIN32__
	}
	~RuningTimer() {
		delete costTime;
	}
	void Reset() {
		memset(costTime, 0, sizeof(Timeval));
	}

	void ShowCostTime() {
		std::cout<<"Running time is : "<<costTime->sec<<"s "<<this->costTime->msec<<"ms "<< this->costTime->usec<<"us"<<std::endl;
	}

	void GetTime(int& _sec, long& _msec, long& _usec) {
		_sec = costTime->sec; _msec = costTime->msec; _usec = costTime->msec;
	}


	void Start() {
#ifdef __WIN32__
        QueryPerformanceCounter(&begin_);
#else
		gettimeofday(&begin_, 0);
#endif // __WIN32__
	}

	void Stop() {
#ifdef __WIN32__
        QueryPerformanceCounter(&end_);
        long result = (long)(((end_.QuadPart - begin_.QuadPart) * 1000000) / freq_); // total us
        costTime->sec  = (int)(result / 1000000);
        costTime->msec = (long)((result / 1000) % 1000);
        costTime->usec = (long)(result % 1000);
#else
		gettimeofday(&end_, 0);
		tim_subtract(&begin_, &end_);
#endif // __WIN32__
	}
private:
#ifndef __WIN32__
	int tim_subtract(struct timeval *begin, struct timeval *end) {
		if (begin->tv_sec > end->tv_sec) {
			memset(costTime, -1, sizeof(Timeval));
			return -1;
		}

		if ((begin->tv_sec == end->tv_sec) && (begin->tv_usec > end->tv_usec)) {
			memset(costTime, -2, sizeof(Timeval));
			return -2;
		}

		costTime->sec = (end->tv_sec - begin->tv_sec);
		costTime->usec = (end->tv_usec - begin->tv_usec);

		if (costTime->usec < 0) {
			costTime->sec--;
			costTime->usec += 1000000;
		}

		costTime->msec = costTime->usec / 1000;
		costTime->usec = costTime->usec % 1000;

		return 0;
	}
#endif // __WIN32__



private:
	
#ifdef __WIN32__
    LONGLONG freq_;
    LARGE_INTEGER begin_;
    LARGE_INTEGER end_;
#else
	struct timeval begin_, end_;
#endif // __WIN32__

};

#endif // _RUNTIME_H_
