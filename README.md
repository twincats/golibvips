## Golibvips is golang libvips wrapper for windows

Golibvips is alternative libvips wrapper that work with windows by using vips Windows binary

### Installation

#### Step 1 : Download Vips windows binary

Download vips windows binary from here [vips-dev-w64-all-8.13.3.zip](https://github.com/libvips/build-win64-mxe/releases/download/v8.13.3/vips-dev-w64-all-8.13.3.zip)

#### Step 2 : Setting Environtment Variable

extract `vips-dev-w64-all-8.13.3.zip` to folder, for example C:\vips-dev-8.13
windows search Edit the system environtment variable > Environtment Variables > Path > edit > new > type `C:\vips-dev-8.13\bin`.

#### Step 3 : Install Golibvips golang package

``` 
go get -u github.com/twincats/golibvips/libvips 
```

### Example usage

```go
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
```

### Note

Golibvips is build from govips without to build libvips directly. Some feature is disabled because windows binary not supported by default `heif and avif` format because its depend on hevc. if need to use that format build vips directly from [https://github.com/libvips/build-win64-mxe](https://github.com/libvips/build-win64-mxe) with `./build.sh all --with-hevc` . and try enable some commented feature.

test resource is not included in repository, you cant download from govips repository, or use your own.
