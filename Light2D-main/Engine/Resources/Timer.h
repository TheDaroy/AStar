#pragma once
#include <chrono>

namespace LightEngine::Resource
{
	class Timer
	{
	public:
		Timer()
		{
			Reset();

		}
		void Reset()
		{
			startTime = std::chrono::high_resolution_clock::now();
		}
		void Update()
		{
			stopTime = std::chrono::high_resolution_clock::now();
			deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
		}
		float DeltaTime()
		{
			return deltaTime;
		}

	private:

		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point stopTime;

		float deltaTime;
		float timeScale;
		unsigned int elapsedTicks;
		unsigned int startTicks;
	};
}

