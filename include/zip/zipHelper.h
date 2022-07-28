#ifndef _ZIPHELPER_H_
#define _ZIPHELPER_H_

#include <sys/types.h>
#include "zip.h"

namespace shiny {

bool compressMem(void *dest, size_t* destLen, const void * src, size_t srcLen);

bool decompressMem(void *dest, size_t* destsize, const void *source, size_t sourcelen);

}

#endif