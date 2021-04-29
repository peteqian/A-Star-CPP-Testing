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

class Sim{
	private:

	public:
		void run();
		void siftUp(int i);
		void siftDown (int i);

};

#endif
