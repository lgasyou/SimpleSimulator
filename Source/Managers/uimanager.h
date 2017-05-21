/*
 *  Copyright 2017 Li Zeqing
 *
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UIMANAGER_H
#define UIMANAGER_H

template<typename Widget>
class UIManager {
public:
    static Widget *get();

private:
    UIManager() = default;

    ~UIManager();

    static UIManager &instance();

private:
    Widget *widget_ = nullptr;
};

template<typename W>
UIManager<W>::~UIManager() {
    delete widget_;
}

template<typename Widget>
Widget *UIManager<Widget>::get() {
    auto widget = instance().widget_;
    if (widget == nullptr)
        widget = new Widget;
    return widget;
}

template<typename W>
UIManager<W> &UIManager<W>::instance() {
    static UIManager<W> uiManager;
    return uiManager;
}

#endif // !UIMANAGER_H
