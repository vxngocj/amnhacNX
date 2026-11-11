export GITHASH := $(shell git rev-parse --short HEAD)
export VERSION := 0.1.0

all: overlay sysmodule

overlay:
	$(MAKE) -C overlay

sysmodule:
	$(MAKE) -C sysmodule

clean:
	$(MAKE) -C overlay clean
	$(MAKE) -C sysmodule clean
	-rm -rf dist

.PHONY: all overlay sysmodule clean
