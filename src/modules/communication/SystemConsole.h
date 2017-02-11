/*
This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SYSTEMCONSOLE_H
#define SYSTEMCONSOLE_H

#include "libs/Module.h"
#include "libs/StreamOutput.h"
#include <vector>
#include <string>
#include <thread>
#include <mutex>

class SystemConsole : public Module, public StreamOutput {
public:
    SystemConsole();

    void on_module_loaded();
    void on_main_loop(void * argument);

    void thread_main();
    int _putc(int c);
    int _getc(void);
    int puts(const char*);

    std::thread* console_thread;
    std::vector<std::string> lines;
    std::mutex lines_mutex;
};

#endif
