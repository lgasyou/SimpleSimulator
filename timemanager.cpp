#include "timemanager.h"

TimeManager &TimeManager::instance() {
	static TimeManager gameTimer;
	return gameTimer;
}

void TimeManager::init() { }

TimeManager::TimeManager() { }
