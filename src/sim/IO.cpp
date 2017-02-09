#include "DirHandle.h"

extern "C" {

DIR *opendir(const char*)
{
    return 0;
}

struct dirent *readdir(DIR *)
{
    return 0;
}

int closedir(DIR*)
{
    return 0;
}

void rewinddir(DIR*)
{
}

long telldir(DIR*)
{
    return 0;
}

void seekdir(DIR*, long)
{
}

int mkdir(const char *name, mode_t n)
{
    return 0;
}

};