package main

import (
	"fmt"
	"log"

	"github.com/impleotv/gomisbcore/pkg/gomisbcore"
)

func main() {
	// Initialize the library
	err := gomisbcore.Init("")
	if err != nil {
		log.Fatalf("Failed to initialize MisbCore: %v", err)
	}
	defer gomisbcore.Close()

	// Encode a KLV packet
	fmt.Println("Encoding KLV...")
	id := uint64(1234)
	jsonStr := `{"key": "value"}`
	klv, err := gomisbcore.EncodeKlv(id, jsonStr)
	if err != nil {
		log.Fatalf("Encoding failed: %v", err)
	}
	fmt.Printf("Encoded KLV: %x\n", klv)

	// Decode the KLV packet
	fmt.Println("Decoding KLV...")
	decodedJson, err := gomisbcore.DecodeKlv(id, klv)
	if err != nil {
		log.Fatalf("Decoding failed: %v", err)
	}
	fmt.Printf("Decoded JSON: %s\n", decodedJson)
}
