package gomisbcore

import (
	"embed"
	"errors"
	"os"
	"path/filepath"
	"runtime"
)

//go:embed MisbCoreNativeLib.so
var embeddedLibs embed.FS

/* should be go:embed MisbCoreNativeLib.so MisbCoreNativeLib.dll */

// ExtractLibrary extracts the appropriate shared library for the current platform
// and returns the path to the extracted library.
func ExtractLibrary() (string, error) {
	var libName string
	switch runtime.GOOS {
	case "linux":
		libName = "MisbCoreNativeLib.so"
	// case "windows":
	// 	libName = "MisbCoreNativeLib.dll"
	default:
		return "", errors.New("unsupported platform: " + runtime.GOOS)
	}

	// Read the embedded library file
	data, err := embeddedLibs.ReadFile(libName)
	if err != nil {
		return "", errors.New("failed to read embedded library: " + err.Error())
	}

	// Write the library to a temporary file
	tempDir := os.TempDir()
	libPath := filepath.Join(tempDir, libName)
	err = os.WriteFile(libPath, data, 0755)
	if err != nil {
		return "", errors.New("failed to write library to temp file: " + err.Error())
	}

	return libPath, nil
}
