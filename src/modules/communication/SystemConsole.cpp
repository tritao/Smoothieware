/*
This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <stdarg.h>
using std::string;
#include "libs/Module.h"
#include "libs/Kernel.h"
#include "libs/nuts_bolts.h"
#include "SystemConsole.h"
#include "libs/StreamOutput.h"
#include "libs/StreamOutputPool.h"

SystemConsole::SystemConsole() {
}

// Called when the module has just been loaded
void SystemConsole::on_module_loaded() {
    // Add to the pack of streams kernel can call to, for example for broadcasting
    THEKERNEL->streams->append_stream(this);
}


int SystemConsole::puts(const char* s)
{
    return ::puts(s);
}

int SystemConsole::_putc(int c)
{
    return ::putchar(c);
}

int SystemConsole::_getc()
{
    return getchar();
}

