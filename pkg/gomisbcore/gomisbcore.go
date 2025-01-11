package gomisbcore

/*
#include "gomisbcore.h"
*/
import "C"
import (
	"errors"
	"fmt"
	"io"
	"os"
	"sync"
	"unsafe"
)

var misbCoreMutex = sync.Mutex{}
var misbCoreInitialized = false

func Init() error {
	misbCoreMutex.Lock()
	defer misbCoreMutex.Unlock()

	if misbCoreInitialized {
		return nil
	}

	// Extract and load the shared library
	libPath, err := ExtractLibrary()
	if err != nil {
		return fmt.Errorf("failed to extract library: %w", err)
	}

	//libPathUnsafe := C.CString("/home/alexc/Work/gomisbcore/pkg/gomisbcore/MisbCoreNativeLib.so")

	libPathUnsafe := C.CString(libPath)
	defer C.free(unsafe.Pointer(libPathUnsafe))
	defer C.free(unsafe.Pointer(libPathUnsafe))

	ret := C.initMisbCore(libPathUnsafe)

	if ret == 0 {
		return errors.New("failed to initialize MisbCore")
	}

	misbCoreInitialized = true
	return nil
}

func Close() error {

	misbCoreMutex.Lock()
	defer misbCoreMutex.Unlock()

	if misbCoreInitialized {

		ret := C.closeMisbCore()
		misbCoreInitialized = false

		if ret == 0 {
			return errors.New("failed to close MisbCore")
		}
	} else {
		return errors.New("misbCore was not initialized")
	}

	return nil
}

func EncodeKlv(id uint64, jsonPcktStr string) ([]byte, error) {

	jsonPcktUnsafe := C.CString(jsonPcktStr)
	defer C.free(unsafe.Pointer(jsonPcktUnsafe))

	var klvBufferLen C.int

	// Call the C function
	encodedData := C.encodeKlv(C.int(id), jsonPcktUnsafe, &klvBufferLen)
	encodedKlvBuff := C.GoBytes(unsafe.Pointer(encodedData), klvBufferLen)

	// TMP, for testing only
	// testJsonStr, _ := DecodeKlv(id, encodedKlvBuff)
	// fmt.Println(testJsonStr)

	return encodedKlvBuff, nil
}

func DecodeKlv(id uint64, buff []byte) (string, error) {

	cBuff := (*C.char)(unsafe.Pointer(&buff[0]))
	cBuffLen := C.int(len(buff))

	// Call the C function
	cJsonStr := C.decodeKlv(C.int(id), cBuff, cBuffLen)

	if cJsonStr == nil {
		return "", errors.New("failed to decode KLV")
	}

	// Convert the C string back to a Go string
	jsonStr := C.GoString(cJsonStr)

	// Free the memory allocated by the C function
	C.free(unsafe.Pointer(cJsonStr))

	return jsonStr, nil
}

// ReadBinaryFile reads a binary file and returns its contents as a byte slice.
func ReadBinaryFile(filePath string) ([]byte, error) {
	// Open the file
	file, err := os.Open(filePath)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	// Read the file's content into a byte slice
	data, err := io.ReadAll(file)
	if err != nil {
		return nil, err
	}

	return data, nil
}
