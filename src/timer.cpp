#include "timer.h"

Timer::Timer() {
  start_ticks_ = 0;
	started_ = false;
}

void Timer::Start() {
	started_ = true;
	start_ticks_ = SDL_GetTicks();
}

void Timer::Stop() {
	started_ = false;
}

int Timer::GetTicks() {
	if (started_)
		return SDL_GetTicks() - start_ticks_;
	return 0;
}

bool Timer::started() {
	return started_;
}
