FLAGS=-ffunction-sections -fdata-sections -Os -Isrc
MODEL?=uno

help:
	@echo "\033[1;32;40m";
	@echo "Hardware model: $(MODEL)"
	@echo "Use variable MODEL to change it, e.g. make release MODEL=nano328"
	@echo "\033[0m"
	@echo "Targets:"
	@echo "lcd          - lcd UI + no debug - ready to use"
	@echo "lcd-debug    - lcd UI + serial debug + times in seconds instead of minutes"
	@echo "serial-debug - serial UI + serial debug + times in seconds instead of minutes"
	@echo "leds         - leds UI + serial debug + times in seconds instead of minutes"
	@echo "leds-debug   - leds UI + serial debug + times in seconds instead of minutes"
	@echo "clean        - clean compiled stuff"
	@echo "upload       - call upload"
	@echo "test         - build and run tests"
	@echo "clean-test   - remove build directory with tests"

clean:
	@ino clean
clean-test:
	@rm -rf build

lcd: clean
	@rm -f src/ui/UI.*
	@ln -s ../../src-alternative/ui/lcd/UI.hpp src/ui/UI.hpp
	@ln -s ../../src-alternative/ui/lcd/UI.cpp src/ui/UI.cpp
	@make BUILD_FLAGS="$(FLAGS)" __build

lcd-debug: clean
	@rm -f src/ui/UI.*
	@ln -s ../../src-alternative/ui/lcd/UI.hpp src/ui/UI.hpp
	@ln -s ../../src-alternative/ui/lcd/UI.cpp src/ui/UI.cpp
	@make BUILD_FLAGS="$(FLAGS) -DMO_DEBUG" __build

serial-debug: clean
	@rm -f src/ui/UI.*
	@ln -s ../../src-alternative/ui/serial/UI.hpp src/ui/UI.hpp
	@ln -s ../../src-alternative/ui/serial/UI.cpp src/ui/UI.cpp
	@make BUILD_FLAGS="$(FLAGS) -DMO_DEBUG" __build

leds: clean
	@rm -f src/ui/UI.*
	@ln -s ../../src-alternative/ui/leds/UI.hpp src/ui/UI.hpp
	@ln -s ../../src-alternative/ui/leds/UI.cpp src/ui/UI.cpp
	@make BUILD_FLAGS="$(FLAGS)" __build

leds-debug: clean
	@rm -f src/ui/UI.*
	@ln -s ../../src-alternative/ui/leds/UI.hpp src/ui/UI.hpp
	@ln -s ../../src-alternative/ui/leds/UI.cpp src/ui/UI.cpp
	@make BUILD_FLAGS="$(FLAGS) -DMO_DEBUG" __build

__build:
	@echo "\033[1;32;40m";
	@echo MODEL=$(MODEL)
	@echo FLAGS=$(BUILD_FLAGS)
	@echo "\033[0m"
	@sleep 1
	ino build -f="$(BUILD_FLAGS)" -m $(MODEL)

upload:
	@echo "\033[1;32;40m";
	@echo MODEL=$(MODEL)
	@echo "\033[0m"
	@sleep 1
	ino upload -m $(MODEL)

test_dir:
	[ -d build ] || mkdir build

build/Makefile: test_dir .git
	cd build && cmake ..

test: build/Makefile
	cd build && make && ./pomoduino2test
