//go:build linux
// +build linux

package gomisbcore

/*
#cgo LDFLAGS: -L${SRCDIR} -l:MisbCoreNativeLib.so
#include "gomisbcore.h"
*/
import "C"
