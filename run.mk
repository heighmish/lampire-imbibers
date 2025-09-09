include Makefile

run-debug: lampire-imbibers
	./bin/Debug/lampire-imbibers

run-release:
	$(MAKE) config=release
	./bin/Release/lampire-imbibers

run: run-debug

.PHONY: run run-debug run-release
