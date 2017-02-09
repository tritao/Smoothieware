#ifndef _AHBMALLOC_H
#define _AHBMALLOC_H

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    AHB_BANK_0,
    AHB_BANK_1,
    AHB_NUM_BANKS
} BANK;

#if defined(__GNUC__)
#define ATTR_WARNING(w) __attribute__ ((warning(w)))
#else
#define ATTR_WARNING(w)
#endif

void* ahbmalloc(size_t size, BANK bank) ATTR_WARNING("deprecated, please use new (AHB0) blah(); or blah = AHB0.alloc(size);");
void ahbfree(void* ptr, size_t size);

#endif /* _AHBMALLOC_H */
