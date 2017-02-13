/*
This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <chrono>
#include <thread>

template <typename T = std::chrono::microseconds>
class Timer {
    typedef std::chrono::high_resolution_clock clock;
public:
    Timer() : start(clock::now()) {}

    inline void reset() { start = clock::now(); }

    inline void sleep(int n) const { std::this_thread::sleep_for(T(n)); }

    inline double elapsed() const {
        return std::chrono::duration_cast<T>(clock::now() - start).count();
    }
private:
    std::chrono::time_point<clock> start;
};