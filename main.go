package main

/*
#cgo CFLAGS: -I${SRCDIR}/include
#cgo LDFLAGS: -L${SRCDIR}/lib -Wl,-rpath,\$ORIGIN/lib -lvips.dll -lglib-2.0.dll
#include <stdlib.h>
#include <stdio.h>
#include "vips/vips.h"
*/
import "C"
import (
	"fmt"
	"golibvips/libvips"
	"io/ioutil"
	"os"
)

func checkError(err error) {
	if err != nil {
		fmt.Println("error:", err)
		os.Exit(1)
	}
}

// this main is only to show example
func main() {

	libvips.Startup(nil)
	defer libvips.Shutdown()

	image1, err := libvips.NewImageFromFile("input.png")
	checkError(err)

	// err = image1.Resize(0.4, libvips.KernelAuto)
	err = image1.ResizeWidthPixel(1000, libvips.KernelAuto)
	checkError(err)

	ep := libvips.NewWebpExportParams()
	ep.Quality = 60
	image1bytes, _, err := image1.ExportWebp(ep)
	checkError(err)
	err = ioutil.WriteFile("output.webp", image1bytes, 0644)
	checkError(err)
}
