#include "TimeManager.h"

TimeManager &TimeManager::instance() {
	static TimeManager gameTimer;
	return gameTimer;
}

TimeManager::TimeManager() :
	currentTime_(1.0),
	deltaTime_(0.0),
	frequence_(1.0)
{ }