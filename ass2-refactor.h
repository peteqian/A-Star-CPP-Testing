#ifndef ASS2REFACTOR_H
#define ASS2REFACTOR_H

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct event {
	float time;

	// contents of event struct
	// server
	float busyDuration;

	//event Types
	int eventType;
	int passengerClass;
	float serviceDuration;
	float queueDuration;

};

const int QUEUE_MAX = 500;

class Sim{
	private:
		// Variables of main (4)
		
		event bQueue[QUEUE_MAX];
		int bHead = 0;
		int bTail = 0;
		int bqSize = 0;
		int bqMax = 0;
		float bqTotal;
		event tQueue[QUEUE_MAX];
		int tHead = 0;
		int tTail = 0;
		int tqSize = 0;
		int tqMax = 0;
		float tqTotal;
		int qMax = 0;
		event *bStack;
		event *tStack;

		char filename[20];
		ifstream fin;

		float now;
		float inArrival;
		int inClass;
		float inService;

		int bCount, tCount, bIdle, tIdle;

		float totalService[3];
		float pureService[3];
		int nServed[3];
	public:
		void run();
		void siftUp(int i);
		void siftDown (int i);

};

#endif
