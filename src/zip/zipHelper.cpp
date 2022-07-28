#include "zip/zipHelper.h"

namespace shiny {

bool compressMem(void *dest, size_t* destLen, const void *src, size_t srcLen) {
    // dest 转 Bytef
	Bytef *dest_ = reinterpret_cast<Bytef *>(dest);

	Bytef *source_ = reinterpret_cast<Bytef *>(const_cast<void *>(src));

	// size_t to uLongf
	uLongf destlen = *destLen;

	int ret = compress(dest_, &destlen, source_, srcLen);
	
	*destLen = destlen;

    return ret == Z_OK;
}


bool decompressMem(void *dest, size_t* destsize, const void *source, size_t sourcelen) {
    //dest 转 Bytef
	Bytef *dest_ = reinterpret_cast<Bytef *>(dest);

	Bytef *source_ = reinterpret_cast<Bytef *>(const_cast<void *>(source));

	// size_t to uLongf
    uLongf destlen = *destsize;

    int ret = uncompress(dest_, &destlen, source_, sourcelen);

    *destsize = destlen;

	return ret == Z_OK;
}

}