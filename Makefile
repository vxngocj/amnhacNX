export VERSION := 0.1.0

# The sysmodule target is intentionally not built yet: the current sysmodule
# directory is only a placeholder and does not provide background playback.
all: overlay

overlay:
	$(MAKE) -C overlay

clean:
	$(MAKE) -C overlay clean

.PHONY: all overlay clean
