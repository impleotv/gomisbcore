#include "gomisbcore.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <libgen.h>
#include <limits.h>

#ifdef _WIN32
#include <windows.h>
#define funcAddr GetProcAddress
#define checkAccess _access
#else
#include <dlfcn.h>
#define funcAddr dlsym
#endif

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

#ifndef F_OK
#define F_OK 0
#endif

typedef struct PcktBuffer
{
    char *buffer;
    int length;
} PcktBuffer;

typedef char *(*getNodeInfoFunc)();
typedef bool (*activateFunc)(char *, char *);
typedef bool (*activateLibFunc)(char *);
typedef struct PcktBuffer (*instanceEncodeFunc)(int id, char *);
typedef char *(*instanceDecodeFunc)(int id, char *, int len);
typedef void (*cleanUpFunc)();

#ifdef _WIN32
HINSTANCE handle;
#else
void *handle;
#endif

instanceEncodeFunc encode;
instanceDecodeFunc decode;

const char *encodeKlv(int id, const char *jsonPckt, int *bufferLen)
{
    struct PcktBuffer pcktBuf = encode(id, (char *)jsonPckt);
    *bufferLen = pcktBuf.length;
    return (const char *)pcktBuf.buffer;
}

const char *decodeKlv(int id, const char *buff, int bufferLen)
{
    char *json = decode(id, (char *)(buff), bufferLen);
    return (const char *)json;
}

int initMisbCore(const char *libDir, char *errBuf, size_t errBufSize)
{
    char exePath[PATH_MAX];

#ifdef _WIN32

    char pathToLibrary[MAX_PATH];
    snprintf(pathToLibrary, sizeof(pathToLibrary), "%s\\MisbCoreNativeLib.dll", libDir);

    printf("Path to the library: %s\n", pathToLibrary);

    if (access(pathToLibrary, F_OK) == -1)
    {
        printf("Couldn't find library at the specified path: %s\n", pathToLibrary);
        return 0;
    }

    handle = LoadLibraryA((char *)pathToLibrary);
    if (handle == 0)
    {
        DWORD error = GetLastError();
        fprintf(stderr, "Couldn't load library '%s'. Error code: %lu\n", pathToLibrary, error);
        snprintf(errBuf, errBufSize, "Couldn't load library '%s'. Error code: %lu\n", pathToLibrary, error);
        return 0;
    }
#else

    char pathToLibrary[PATH_MAX];
    snprintf(pathToLibrary, sizeof(pathToLibrary), "%s/MisbCoreNativeLib.so", libDir);

    handle = dlopen((char *)pathToLibrary, RTLD_NOW /*RTLD_LAZY*/);
    if (handle == 0)
    {
        snprintf(errBuf, errBufSize, "Couldn't load library: %s", dlerror());
        return 0;
    }
#endif

    getNodeInfoFunc GetNodeInfo = (getNodeInfoFunc)funcAddr(handle, (char *)"GetNodeInfo");
    char *nodeInfo = GetNodeInfo();
    printf("The NodeInfo: %s \n", nodeInfo);

    bool fValid = false;

    activateLibFunc Activate = (activateLibFunc)funcAddr(handle, (char *)"ActivateLib");
    fValid = Activate("98E3C0A4-9DD2-46BD-890B-79F036A9A67A");

    encode = (instanceEncodeFunc)funcAddr(handle, (char *)"InstanceEncode");
    decode = (instanceDecodeFunc)funcAddr(handle, (char *)"InstanceDecode");

    if (!encode || !decode)
    {

#ifdef _WIN32
        // Free the library
        printf("Couldn't find InstanceEncode/InstanceDecode functions");
        snprintf(errBuf, errBufSize, "Couldn't find InstanceEncode/InstanceDecode functions");
        FreeLibrary(handle);
#else
        //fprintf(stderr, "Couldn't find InstanceEncode/InstanceDecode function: %s\n", dlerror());
        snprintf(errBuf, errBufSize, "Couldn't find InstanceEncode/InstanceDecode function: %s\n", dlerror());
        dlclose(handle);
#endif

        return 0;
    }

    return 1;
}

int closeMisbCore()
{

#ifdef _WIN32
    if (handle)
    {
        printf("Closing misbCore\n");
        FreeLibrary(handle);
        return 1; // success
    }
    return 0; // failure
#else
    if (handle)
    {
        printf("Closing misbCore\n");
        dlclose(handle);
        return 1; // success
    }
    return 0; // failure
#endif
}