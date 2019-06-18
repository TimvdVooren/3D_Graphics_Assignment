#pragma once

class FpsCounter {
	bool enabled = true;

	long timePassedNanos = 0;
	long lastTime = -1;

	long accumulatedTimeNanos = 0;

	float fps = 60;
	int frames = 0;
	long firstFrameTime = 0;

public:
	int fpsRefreshTimeNanos = 500 * 1000 * 1000; 

	FpsCounter();
	~FpsCounter();

	void update();
	long getTimePassedMillis();
	long getTimePassedMicros(); 
	long getTimePassedNanos(); 
	float getFPS();
};