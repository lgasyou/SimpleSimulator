#include "GameTimer.h"

GameTimer &GameTimer::instance() {
	static GameTimer gameTimer;
	return gameTimer;
}

double GameTimer::currentTime_ = 1;
double GameTimer::deltaTime_ = 0;
double GameTimer::frequence_ = 1;
