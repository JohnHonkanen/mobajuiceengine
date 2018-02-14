#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

namespace Engine
{
	namespace Utility
	{
		class Clock
		{
		public:
			//Start the Clock
			void StartClock() { startTime = std::clock(); };
			//Update the Clock
			void UpdateClock() { millisecondPassed = std::clock() - startTime; };
			//Reset The Clock
			void ResetClock() { StartClock(); };
			//Set the delay to alarm in milliseconds
			void SetDelay(double milliseconds) { millisecondToDelay = milliseconds; };
			// Delay has passed
			bool Alarm() { return millisecondPassed >= millisecondToDelay; };
		private:
			std::clock_t startTime;
			double millisecondPassed;
			double millisecondToDelay;

		};
	}
}