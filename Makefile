
all:
	make run

build:
	CGO_CFLAGS_ALLOW=-Xpreprocessor go build .

run:
	golibvips

test:
	set CGO_CFLAGS_ALLOW=-Xpreprocessor & go test -v ./libvips