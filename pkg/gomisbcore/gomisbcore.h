#ifndef GOMISBCORE_H
#define GOMISBCORE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

int initMisbCore(const char* libDir, char *errBuf, size_t errBufSize);
int closeMisbCore();
const char* encodeKlv(int id, const char* jsonPckt, int* bufferLen); 
const char* decodeKlv(int id, const char *buff, int bufferLen);

#ifdef __cplusplus
}
#endif



#endif