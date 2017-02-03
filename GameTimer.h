#ifndef GAMETIMER_H
#define GAMETIMER_H


class GameTimer {
public:
	static GameTimer &instance();

    void setDeltaTime(double deltaTime) { deltaTime_ = deltaTime; }
    const double deltaTime() { return deltaTime_; }

	void increaseTime() { currentTime_ += frequence_; }
    const double currentTime() { return currentTime_; }

	void setFrequence(double frequence) { frequence_ = frequence; }
	const double frequence() { return frequence_; }

private:
	GameTimer() { }
	~GameTimer() { }
	GameTimer(const GameTimer &) = delete;
	GameTimer &operator=(const GameTimer &) = delete;

    static double deltaTime_;
    static double currentTime_;
	static double frequence_;
};

#endif // GAMETIMER_H
