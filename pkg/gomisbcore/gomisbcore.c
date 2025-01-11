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
#include <unistd.h>
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
typedef char* (*instanceDecodeFunc)(int id, char*, int len);
typedef void (*cleanUpFunc)();

#ifdef _WIN32
HINSTANCE handle;
#else
void *handle;
#endif


instanceEncodeFunc encode;
instanceDecodeFunc decode;


const char* encodeKlv(int id, const char* jsonPckt, int* bufferLen)
{
    struct PcktBuffer pcktBuf = encode(id, (char *)jsonPckt);
    *bufferLen = pcktBuf.length;
    return (const char *)pcktBuf.buffer;
}

const char* decodeKlv(int id, const char* buff, int bufferLen)
{
    char* json = decode(id, (char*)(buff), bufferLen);   
    return (const char *)json;
}



int initMisbCore(const char* libDir)
{
 
	char exePath[PATH_MAX];

#ifdef _WIN32

//    DWORD count = GetModuleFileName(NULL, exePath, MAX_PATH);

//     if (count == 0) {
//         printf("Couldn't get the executable path\n");
//         return 0;
//     }

//     exePath[MAX_PATH - 1] = '\0'; // Ensure null-termination

//     // Create a copy of exePath because dirname may modify its argument
//     char exePathCopy[MAX_PATH];
//     strncpy(exePathCopy, exePath, MAX_PATH);
//     exePathCopy[MAX_PATH - 1] = '\0'; // Ensure null-termination

//     char* exeDir = dirname(exePathCopy);
  // char *exeDir = libDir;
  
    char pathToLibrary[MAX_PATH];
    snprintf(pathToLibrary, sizeof(pathToLibrary), "%s\\MisbCoreNativeLib.dll", libDir);

    printf("Path to the library: %s\n", pathToLibrary);

    if (access(pathToLibrary, F_OK) == -1)
    {
        printf("Couldn't find library at the specified path: %s\n", pathToLibrary);
        return 0;
    }
	
    handle = LoadLibraryA((char *)pathToLibrary);
#else

    // ssize_t count = readlink("/proc/self/exe", exePath, PATH_MAX);
    // if (count == -1)
    // {
    //     printf("Couldn't get the executable path\n");
    //     return 0;
    // }

    // exePath[count] = '\0'; // Null-terminate the path

    // // Create a copy of exePath because dirname may modify its argument
    // char exePathCopy[PATH_MAX];
    // strncpy(exePathCopy, exePath, PATH_MAX);

    // exePathCopy[PATH_MAX - 1] = '\0'; // Ensure null-termination

    // char *exeDir = dirname(exePathCopy);

    char pathToLibrary[PATH_MAX];
    snprintf(pathToLibrary, sizeof(pathToLibrary), "%s/MisbCoreNativeLib.so", libDir);

    handle = dlopen((char *)pathToLibrary, RTLD_NOW /*RTLD_LAZY*/);
#endif
   

    if (handle == 0)
    {
        printf("Couldn't load library");
        return 0;
    }

    getNodeInfoFunc GetNodeInfo = (getNodeInfoFunc)funcAddr(handle, (char *)"GetNodeInfo");
    char *nodeInfo = GetNodeInfo();
    printf("The NodeInfo: %s \n", nodeInfo);

	bool fValid = false;

    activateLibFunc Activate = (activateLibFunc)funcAddr(handle, (char *)"ActivateLib");
    fValid = Activate("98E3C0A4-9DD2-46BD-890B-79F036A9A67A");

    encode = (instanceEncodeFunc)funcAddr(handle, (char *)"InstanceEncode");
    decode = (instanceDecodeFunc)funcAddr(handle, (char*)"InstanceDecode");

    if (!encode || !decode)
    {
      
#ifdef _WIN32
	// Free the library
    printf("Couldn't find InstanceEncode/InstanceDecode functions");
	FreeLibrary(handle);
#else
    fprintf(stderr, "Couldn't find InstanceEncode/InstanceDecode function: %s\n", dlerror());
	dlclose(handle);
#endif

        return 0;
    }

    return 1;
}


int closeMisbCore() 
{

#ifdef _WIN32
     if (handle != 0) {
        printf("Closing misbCore\n");
        FreeLibrary(handle);
        return 0;
     } 
    else
    {
        printf("Cannot close misbCore. Zero handle\n");
    }
#else
    if (handle != 0) {
        printf("Closing misbCore\n");
        dlclose(handle);
    } 
    else
    {
        printf("Cannot close misbCore. Zero handle\n");
        return 0;
    }
#endif

 return 1;
}