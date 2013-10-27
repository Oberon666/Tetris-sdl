// CAPP_Timer.cpp
#include "CApp_Timer.h"

//--------------------------------------------
Timer::Timer(): startTick(0), pauseTick(0), paused(false), started(false){
}
//--------------------------------------------
void Timer::start(){
	startTick = SDL_GetTicks();
	started = true;
	paused = false;
}
//--------------------------------------------
void Timer::stop(){
	started = false;
	paused = false;
}
//--------------------------------------------
void Timer::pause(){
	if (started && !paused){
		pauseTick = SDL_GetTicks() - startTick;
		paused = true;
	}
}
//--------------------------------------------
void Timer::unpause(){
	if (paused){
		startTick = SDL_GetTicks() - pauseTick;
		pauseTick = 0;
		paused = false;
	}
}
//--------------------------------------------
const Uint32 Timer::getTick() const{
	if (started)
		if (paused)
			return (pauseTick);
		else
			return (SDL_GetTicks() - startTick);
	return (0);
}
//--------------------------------------------
bool Timer::isStarted() const{
	return (started);
}
//--------------------------------------------
bool Timer::isPaused() const{
	return (paused);
}
//--------------------------------------------
