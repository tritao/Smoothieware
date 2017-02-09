/* mbed Microcontroller Library - FATFileHandle
* Copyright (c) 2008, sford
*/

#include "FATFileHandle.h"

#include <stdio.h>
#include <stdlib.h>
#include "ff.h"
#include "FATFileSystem.h"

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

    FATFileHandle::FATFileHandle(FIL_t fh) {
        _fh = fh;
    }

    int FATFileHandle::close() {
        delete this;
        return 0;
    }

    ssize_t FATFileHandle::write(const void* buffer, size_t length) {
        return 0;
    }

    ssize_t FATFileHandle::read(void* buffer, size_t length) {
        return 0;
    }

    int FATFileHandle::isatty() {
        return 0;
    }

    off_t FATFileHandle::lseek(off_t position, int whence) {
        return 0;
    }

    int FATFileHandle::fsync() {
        return 0;
    }

    off_t FATFileHandle::flen() {
        return 0;
    }

} // namespace mbed
