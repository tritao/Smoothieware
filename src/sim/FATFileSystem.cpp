/* mbed Microcontroller Library - FATFileSystem
* Copyright (c) 2008, sford
*/

#include "FATFileSystem.h"
#include "FileSystemLike.h"
#include "FATFileHandle.h"
#include "FATDirHandle.h"
#include <cstdio>
#include <cstdlib>

namespace mbed {

#if FFSDEBUG_ENABLED
    static const char *FR_ERRORS[] = {
        "FR_OK = 0",
        "FR_NOT_READY",
        "FR_NO_FILE",
        "FR_NO_PATH",
        "FR_INVALID_NAME",
        "FR_INVALID_DRIVE",
        "FR_DENIED",
        "FR_EXIST",
        "FR_RW_ERROR",
        "FR_WRITE_PROTECTED",
        "FR_NOT_ENABLED",
        "FR_NO_FILESYSTEM",
        "FR_INVALID_OBJECT",
        "FR_MKFS_ABORTED"
    };
#endif

FATFileSystem::FATFileSystem(const char* n) : FileSystemLike(n) {
    FFSDEBUG("FATFileSystem(%s)\n", n);
}

FATFileSystem::~FATFileSystem() {

}

FileHandle *FATFileSystem::open(const char* name, int flags) {
    FFSDEBUG("open(%s) on filesystem [%s], drv [%d]\n", name, _name, _fsid);

    FIL_t fh;
    return new FATFileHandle(fh);
}

int FATFileSystem::remove(const char *filename) {
    return 0;
}

int FATFileSystem::rename(const char *filename1, const char *filename2) {
    return 0;
}

int FATFileSystem::format() {
    return 0;
}

DirHandle *FATFileSystem::opendir(const char *name) {
    DIR_t dir;
    return new FATDirHandle(dir);
}

int FATFileSystem::mkdir(const char *name, mode_t mode) {
    return 0;
}

} // namespace mbed
