#include "TimeManager.h"

TimeManager &TimeManager::instance() {
	static TimeManager gameTimer;
	return gameTimer;
}

double TimeManager::currentTime_ = 1;
double TimeManager::deltaTime_ = 0;
double TimeManager::frequence_ = 1;
