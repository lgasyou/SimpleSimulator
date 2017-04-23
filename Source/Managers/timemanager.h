/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

// This class controls the time of this game.
class TimeManager {
public:
    // Uses singleton pattern.
    static TimeManager &instance();

    void init();

    void setDeltaTime(double deltaTime) { this->deltaTime_ = deltaTime; }
    double deltaTime() const { return deltaTime_; }

    void increaseTime() { this->currentTime_ += frequence_; }

    double currentTime() const { return currentTime_; }

    void setFrequence(double frequence) { this->frequence_ = frequence; }
    double frequence() const { return frequence_; }

private:
    // Hides constructor and destructor.
    TimeManager();

    ~TimeManager() { }

private:
    double deltaTime_ = 0.0;

    double currentTime_ = 1.0;

    double frequence_ = 1.0;
};

#endif // TIMEMANAGER_H
