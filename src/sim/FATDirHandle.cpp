/* mbed Microcontroller Library - FATDirHandle
* Copyright (c) 2008, sford
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ff.h"
#include "FATDirHandle.h"
#include "FATFileSystem.h"

namespace mbed {

    FATDirHandle::FATDirHandle(const DIR_t &the_dir) {
        dir = the_dir;
    }

    int FATDirHandle::closedir() {
        delete this;
        return 0;
    }

    struct dirent *FATDirHandle::readdir() {
        return 0;
    }

    void FATDirHandle::rewinddir() {
    }

    off_t FATDirHandle::telldir() {
        return 0;
    }

    void FATDirHandle::seekdir(off_t location) {
    }

}

