/*
This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#include "SystemConsole.h"
#include "libs/Kernel.h"
#include "libs/SerialMessage.h"
#include "libs/StreamOutputPool.h"
#include "linenoise/linenoise.h"

SystemConsole::SystemConsole() {
}

// Called when the module has just been loaded
void SystemConsole::on_module_loaded() {
    // Add to the pack of streams kernel can call to, for example for broadcasting
    THEKERNEL->streams->append_stream(this);

    // We only call the command dispatcher in the main loop, nowhere else
    this->register_for_event(ON_MAIN_LOOP);
    this->register_for_event(ON_IDLE);

    console_thread = new std::thread(&SystemConsole::thread_main, this);
}

void SystemConsole::on_main_loop(void * argument) {
    std::lock_guard<std::mutex> lk(lines_mutex);
    for (auto line : lines) {
        struct SerialMessage message;
        message.message = line;
        message.stream = this;
        THEKERNEL->call_event(ON_CONSOLE_LINE_RECEIVED, &message);
    }
    lines.clear();
}

void SystemConsole::thread_main() {
    char *line;
    while ((line = linenoise("")) != NULL) {
        std::lock_guard<std::mutex> lk(lines_mutex);
        lines.push_back(std::string(line));
        free(line);
    }
}

int SystemConsole::puts(const char* s)
{
    return ::printf("%s", s);
}

int SystemConsole::_putc(int c)
{
    return ::putchar(c);
}

int SystemConsole::_getc()
{
    return getchar();
}

