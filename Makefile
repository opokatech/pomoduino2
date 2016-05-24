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
	@BOARD_TAG=$(MODEL) make -C src clean

clean-test:
	@rm -rf build

lcd: clean
	@rm -f src/UI.*
	@ln -s ../src-alternative/ui/lcd/UI.hpp src/UI.hpp
	@ln -s ../src-alternative/ui/lcd/UI.cpp src/UI.cpp
	@make __build

lcd-debug: clean
	@rm -f src/UI.*
	@ln -s ../src-alternative/ui/lcd/UI.hpp src/UI.hpp
	@ln -s ../src-alternative/ui/lcd/UI.cpp src/UI.cpp
	@make BUILD_FLAGS="-DMO_DEBUG" __build

serial-debug: clean
	@rm -f src/UI.*
	@ln -s ../src-alternative/ui/serial/UI.hpp src/UI.hpp
	@ln -s ../src-alternative/ui/serial/UI.cpp src/UI.cpp
	@make BUILD_FLAGS="-DMO_DEBUG" __build

leds: clean
	@rm -f src/UI.*
	@ln -s ../src-alternative/ui/leds/UI.hpp src/UI.hpp
	@ln -s ../src-alternative/ui/leds/UI.cpp src/UI.cpp
	@make __build

leds-debug: clean
	@rm -f src/UI.*
	@ln -s ../src-alternative/ui/leds/UI.hpp src/UI.hpp
	@ln -s ../src-alternative/ui/leds/UI.cpp src/UI.cpp
	@make BUILD_FLAGS="-DMO_DEBUG" __build

__build:
	@echo "\033[1;32;40m";
	@echo MODEL=$(MODEL)
	@echo FLAGS=$(BUILD_FLAGS)
	@echo "\033[0m"
	@sleep 1
	BOARD_TAG=$(MODEL) BUILD_FLAGS="$(BUILD_FLAGS)" make -C src

upload:
	@echo "\033[1;32;40m";
	@echo MODEL=$(MODEL)
	@echo "\033[0m"
	@sleep 1
	BOARD_TAG=$(MODEL) make -C src upload

test_dir:
	[ -d build ] || mkdir build

build/Makefile: test_dir .git
	cd build && cmake ..

test: build/Makefile
	cd build && make && ./pomoduino2test
