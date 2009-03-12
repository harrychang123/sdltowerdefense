/*
 * Author: Corey Ruda
 * Filename: timer.h
 *
 * This is a timer class
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
private:
	//Data Members
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;

public:
	//Constructor
	Timer();

	//Setter Functions
	void start();
	void stop();
	void pause();
	void unpause();

	//Getter Function
	int get_ticks();
	bool is_started();
	bool is_paused();

};

#endif /* TIMER_H_ */
