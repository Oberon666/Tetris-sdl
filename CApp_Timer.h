//CAPP_Timer.h
#ifndef CAPP_TIMER_H
#define CAPP_TIMER_H

#include<SDL/SDL.h>

//--------------------------------------------
class Timer{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	const Uint32 getTick() const;

	bool isStarted() const;
	bool isPaused() const;

private:
	Uint32 startTick;
	Uint32 pauseTick;

	bool paused;
	bool started;

};

//--------------------------------------------
#endif // CAPP_TIMER_H
