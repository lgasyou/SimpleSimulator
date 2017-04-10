#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H


// This class controls the time of this game.
class TimeManager {
public:
	// Use singleton pattern.
	static TimeManager &instance();

	void init();

    void setDeltaTime(double deltaTime) { this->deltaTime_ = deltaTime; }
    double deltaTime() const { return deltaTime_; }

	void increaseTime() { this->currentTime_ += frequence_; }
    double currentTime() const { return currentTime_; }

	void setFrequence(double frequence) { this->frequence_ = frequence; }
	double frequence() const { return frequence_; }

private:
	// Hide constructor and destructor.
	TimeManager();

	~TimeManager() { }

private:
    double deltaTime_ = 0.0;

    double currentTime_ = 1.0;

	double frequence_ = 1.0;
};

#endif // TIMEMANAGER_H
