#include "SDL/SDL.h"

class Timer {
	public:
		Timer();
		void Start();
		void Stop();

		int GetTicks();

		bool started();

	private:
		int start_ticks_;
		bool started_;
};

