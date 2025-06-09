# Native library

**MisbCoreNative Lib** is a **MisbCore** compiled as a self-contained native library (Native AOT Form Factor).  
This library allows easy integration into C/C++ cross-platform applications.

## System Requirements
OS: Windows / Linux (x64 or arm64). 

## Using MisbCoreNative Lib  

To use the library, we first have to load it:

```cpp
#ifdef _WIN32
    #define funcAddr GetProcAddress
    const char* PathToLibrary = "C:\\work\\MisbCoreNativeLib.dll";
    HINSTANCE handle = LoadLibraryA((char*)PathToLibrary);
#else
    #define funcAddr dlsym
    const char* PathToLibrary = "/home/user/work/MisbCoreNativeLib.so";
    void* handle = dlopen((char*)PathToLibrary, RTLD_LAZY);
#endif
```

### Encoding RAW KLV buffer  

Now, let's create a very simple **MISB 601** Local set packet (sample data from MISB ST 0601.16a).  

```cpp
const char* jspnPckt = R"({
    2: '2008-10-24T00:13:29.913',
    3: 'MISSION01',
    13: 60.176822966978335,
    14: 128.42675904204452,
    15: 14190.7195,
    16: 144.571298,
    65: 13
})";
```  

Next, we will define a simple structure that accommodates the resulting buffer and its length and call **Encode** method, passing the string as an argument.  


```cpp
struct PcktBuffer
{
	char* buffer;
	int length;
};

typedef PcktBuffer (*encodeFunc)(char*);

encodeFunc encode601Pckt = (encodeFunc)funcAddr(handle, (char*)"Encode");

// Encode json packet to data buffer
PcktBuffer pcktBuf = encode601Pckt((char*)(jspnPckt));
```

> Note, the **Encode** function returns a pointer to an internally allocated memory. It will be automatically de-allocated during the next **Encode** call, so you may need to copy this buffer (depending on the scenario).

The resulting buffer is a **RAW Klv** that comprises all mandatory parts of the packet:

* The UAS Local Set 16-Byte UL “Key”  
* Packet length  
* Packet data payload
* Checksum  

This buffer can be injected into STANAG4609 multiplex: 

![Encoded buffer](./images/getting-started-encodedbuf.png)

#### Timestamps  

If you don't provide a mandatory **Tag 2** timestamp, **MisbCore** will add a current time automatically.  
Time can be set as a **long** value (as specified in MISB601 standard) -  "2": 1638730169255332, or as an ISO 6601 string, for example  - "2": "2021-12-16T13:44:54")  


### Decoding RAW KLV buffer  

To decode the data buffer:  

```cpp
typedef char* (*decodeFunc)(char*, int len);

decodeFunc decodeKlvBuffer = (decodeFunc)funcAddr(handle, (char*)"Decode");

// Decode the buffer back to json. 
char* json = decodeKlvBuffer((char*)buf, len);
```

Here is the result:  

```js
{
  "2": "2008-10-24T00:13:29.913Z",
  "3": "MISSION01",
  "13": 60.176822967,
  "14": 128.426759042,
  "15": 14190.72,
  "16": 144.5713,
  "65": 13,
  "1": 53482
}
```

### Converting to a detailed human-readable format

This method may be used for presentation, when you need some additional information, like tag full name in addition to the tag number and more suitable value formatting.

```cpp
typedef char* (*toDetailedFunc)(char*);
toDetailedFunc toDetailed = (toDetailedFunc)funcAddr(handle, (char*)"ToDetailed");

char* detailedJsonStr = toDetailed((char*)jsonPckt);
printf("Convert a compact json format to human readable, detailed json: \n %s", detailedJsonStr);
```

The resulting string will be something like this:
```js
{
  "003. Mission ID": "MISSION01",
  "004. Platform Tail Number": "AF-101",
  "005. Platform Heading Angle": "159.974365°",
  "006. Platform Pitch Angle": "-0.43°",
  "007. Platform Roll Angle": "3.41°",
  "008. Platform True Airspeed": "147 m/s",
  "009. Platform Indicated Airspeed": "159 m/s",
  "010. Platform Designation": "MQ1-B",
  "011. Image Source Sensor": "EO",
  "012. Image Coordinate System": "WGS-84",
  "013. Sensor Latitude": "60° 10' 36.563'' N",
  "014. Sensor Longitude": "128° 25' 36.333'' E",
  "015. Sensor True Altitude": "14190.7195 m",
  "016. Sensor Horizontal field of View": "144.571298°",
  "017. Sensor Vertical Field of View": "152.643626°",
  "018. Sensor Relative Azimuth Angle": "160.7192°",
  "019. Sensor Relative Elevation Angle": "-168.7923°"
  ...
}
```

### Cleaning up

To free internally allocated memory, call **CleanUp** method:

```cpp
typedef void (*cleanUpFunc)();

cleanUpFunc cleanUp = (cleanUpFunc)funcAddr(handle, (char*)"CleanUp");
cleanUp();
```


### Using multiple instances
It is possible to get multiple encoder/decoder instances.  
To achieve this, use the following methods:  

```cpp
typedef PcktBuffer (*instanceEncodeFunc)(int id, char*);
typedef char* (*instanceDecodeFunc)(int id, char*, int len);
typedef void (*instanceCleanUpFunc)(int id);
```

The only difference from the default mode is that you have to provide an instance **id** as an argument.  
> Note, in non default mode, the instance is created and activated on a first call to **instanceEncodeFunc** or **instanceDecodeFunc**.

Here is an example of using instance with **id**=1.
```cpp
PcktBuffer pcktBuf = encode601Pckt(1, (char*)(jspnPckt)); 
char* json = decodeKlvBuffer(1, (char*)(pcktBuf.buffer), pcktBuf.length);
```

### Demo mode

Please note that if not activated, the library will work in demo mode processing only tags < 15 (and tag 65).  
To activate the license, call **Activate** method:  

```cpp
const char* PathToLicenseFile = "/home/user/Licenses/Impleo/MisbCoreNativeLicense.lic";
const char* LicenseKey = "AF596BF0-BBAB142B-1B905B24-8DA51BED";
typedef bool (*activateFunc)(char*, char*);

activateFunc Activate = (activateFunc)funcAddr(handle, (char*)"Activate");
bool fValid = Activate((char*)PathToLicenseFile, (char*)LicenseKey);
```

### Demo app

A simple demo app (**cmake** project) that demonstrates the basic functionality is available (**MisbCoreNativeLib-demo.zip**).

## Getting help

To get help with **MisbCoreNative Lib**, please contact us at *support@impleotv.com*.  
