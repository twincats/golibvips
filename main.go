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
	"io/ioutil"
	"os"

	"github.com/twincats/golibvips/libvips"
)

func checkError(err error) {
	if err != nil {
		fmt.Println("error:", err)
		os.Exit(1)
	}
}

// this main is only to show example
func main() {
	// starting library
	libvips.Startup(nil)
	defer libvips.Shutdown()

	// load image from file
	image1, err := libvips.NewImageFromFile("input.png")
	checkError(err)

	// resize by with pixel, keep aspect ratio
	err = image1.ResizeWidthPixel(1000, libvips.KernelAuto)
	checkError(err)

	// create web export param to export webp
	ep := libvips.NewWebpExportParams()
	ep.Quality = 60

	// export to webp
	image1bytes, _, err := image1.ExportWebp(ep)
	checkError(err)

	// save to file
	err = ioutil.WriteFile("output.webp", image1bytes, 0644)
	checkError(err)
}
