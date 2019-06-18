//#include "FpsCounter.h"
//#include <chrono>
//
//FpsCounter::FpsCounter()
//{
//}
//
//FpsCounter::~FpsCounter()
//{
//}
//
//void FpsCounter::update()
//{
//	if (!enabled) return;
//
//	if (lastTime == -1) {
//		//Initialization of the counter
//		lastTime = getTimeNanos();
//		timePassedNanos = 0;
//
//		//Initialization for FPS calculation
//		fps = 0;
//		frames = 0;
//		firstFrameTime = lastTime;
//	}
//	else {
//		//Get the current time
//		long currentTime = std::chrono::high_resolution_clock::now();
//		//Time passed
//		timePassedNanos = currentTime - lastTime;
//		//Update last time, it is now the current for next frame calculation
//		lastTime = currentTime;
//		//Accumulate time
//		accumulatedTimeNanos += timePassedNanos;
//
//		//FPS
//		frames++;
//
//		//Calculate fps
//		long dt = currentTime - firstFrameTime;
//		if (dt >= fpsRefreshTimeNanos) {
//			fps = (float)(1000 * frames) / (float)(dt / 1000000);
//			frames = 0;
//			firstFrameTime = currentTime;
//		}
//	}
//}
//
//long FpsCounter::getTimePassedMillis()
//{
//	return timePassedNanos / 1000000;
//}
//
//long FpsCounter::getTimePassedMicros()
//{
//	return timePassedNanos / 1000;
//}
//
//long FpsCounter::getTimePassedNanos()
//{
//	return timePassedNanos;
//}
//
//float FpsCounter::getFPS()
//{
//	return fps;
//}
