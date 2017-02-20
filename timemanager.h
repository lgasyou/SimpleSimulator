#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H


// This class controls the time of this game.
class TimeManager {
public:
	// Use singleton pattern.
	static TimeManager &instance();

    inline void setDeltaTime(double deltaTime) { this->deltaTime_ = deltaTime; }
    inline double deltaTime() const { return this->deltaTime_; }

	inline void increaseTime() { this->currentTime_ += frequence_; }
    inline double currentTime() const { return this->currentTime_; }

	inline void setFrequence(double frequence) { this->frequence_ = frequence; }
	inline double frequence() const { return this->frequence_; }

private:
	// Hide constructor and destructor.
	TimeManager();

	~TimeManager() { }

	TimeManager(const TimeManager &) = delete;

	TimeManager &operator=(const TimeManager &) = delete;

private:
    double deltaTime_;

    double currentTime_;

	double frequence_;
};

#endif // TIMEMANAGER_H
