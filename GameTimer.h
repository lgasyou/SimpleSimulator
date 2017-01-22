#ifndef GAMETIMER_H
#define GAMETIMER_H


class GameTimer {
public:
    GameTimer();

    static void setDeltaTime(double deltaTime) { deltaTime_ = deltaTime; }
    static const double deltaTime() { return deltaTime_; }

	static void increaseTime() { currentTime_ += frequence_; }
    static const double currentTime() { return currentTime_; }

	static void setFrequence(double frequence) { frequence_ = frequence; }
	static const double frequence() { return frequence_; }

private:
    static double deltaTime_;
    static double currentTime_;
	static double frequence_;
};

#endif // GAMETIMER_H
