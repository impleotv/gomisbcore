package tests

import (
	"bytes"
	"os"
	"testing"

	"github.com/impleotv/gomisbcore/pkg/gomisbcore"
)

func TestInitFailure(t *testing.T) {
	if err := gomisbcore.Init("/non/existent/path"); err == nil {
		t.Fatalf("expected error when initializing with bad path")
	}
	if err := gomisbcore.Close(); err == nil {
		t.Fatalf("expected close error when not initialized")
	}
}

func TestReadBinaryFile(t *testing.T) {
	tmp := "test.bin"
	data := []byte{1, 2, 3}
	if err := os.WriteFile(tmp, data, 0644); err != nil {
		t.Fatalf("failed to write temp file: %v", err)
	}
	defer os.Remove(tmp)

	read, err := gomisbcore.ReadBinaryFile(tmp)
	if err != nil {
		t.Fatalf("ReadBinaryFile returned error: %v", err)
	}
	if !bytes.Equal(read, data) {
		t.Fatalf("ReadBinaryFile returned %v, want %v", read, data)
	}
}

func TestExtractLibrary(t *testing.T) {
	path, err := gomisbcore.ExtractLibrary()
	if err != nil {
		t.Fatalf("ExtractLibrary returned error: %v", err)
	}
	defer os.Remove(path)

	if _, err := os.Stat(path); err != nil {
		t.Fatalf("expected library file at %s", path)
	}
}
