
all:
	make run

build:
	set CGO_CFLAGS_ALLOW=-Xpreprocessor & go build .

run:
	make build 
	golibvips

test:
	set CGO_CFLAGS_ALLOW=-Xpreprocessor & go test -v ./...