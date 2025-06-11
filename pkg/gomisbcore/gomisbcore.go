package gomisbcore

/*
#include "gomisbcore.h"
*/
import "C"
import (
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"sync"
	"unsafe"
)

var (
	mu          sync.Mutex
	mue         sync.Mutex
	mud         sync.Mutex
	initialized bool
)

// Init loads the native library from libDir. It’s safe to call multiple times.
func Init(libDir string) error {
	mu.Lock()
	defer mu.Unlock()

	if initialized {
		return nil
	}

	// If libDir is empty, use the executable's directory
	if libDir == "" {
		exePath, err := os.Executable()
		if err != nil {
			return fmt.Errorf("gomisbcore: failed to get executable path: %v", err)
		}
		libDir = filepath.Dir(exePath)
	}

	// Allocate an error buffer
	errBufSize := 512
	errBuf := make([]byte, errBufSize)
	cErrBuf := (*C.char)(unsafe.Pointer(&errBuf[0]))

	cLibDir := C.CString(libDir)
	defer C.free(unsafe.Pointer(cLibDir))

	if C.initMisbCore(cLibDir, cErrBuf, C.size_t(errBufSize)) == 0 {
		return fmt.Errorf("gomisbcore: init failed while loading from %s (%s)", libDir, C.GoString(cErrBuf))
	}
	initialized = true
	return nil
}

// Close tears down the native library. After a successful Close,
// you can call Init again.
func Close() error {
	mu.Lock()
	defer mu.Unlock()

	if !initialized {
		return errors.New("gomisbcore: not initialized")
	}

	if C.closeMisbCore() == 0 {
		return errors.New("gomisbcore: close failed")
	}
	initialized = false
	return nil
}

func EncodeKlv(id uint64, jsonPcktStr string) ([]byte, error) {
	mue.Lock()
	defer mue.Unlock()

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
	mud.Lock()
	defer mud.Unlock()

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
	//	C.free(unsafe.Pointer(cJsonStr))

	return jsonStr, nil
}

// ReadBinaryFile reads a binary file and returns its contents as a byte slice.
func ReadBinaryFile(path string) ([]byte, error) {
	return os.ReadFile(path)
}
