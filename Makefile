FLAGS=-ffunction-sections -fdata-sections -Os -Isrc

help:
	@echo "Targets:"
	@echo "debug      - with serial debug + times in seconds instead of minutes"
	@echo "serial     - as above + serial UI"
	@echo "release    - ready to use, no debug"
	@echo "clean      - clean compiled stuff"
	@echo "upload     - call upload"
	@echo "test       - build and run tests"
	@echo "clean-test - remove build directory with tests"

clean:
	@ino clean
clean-test:
	@rm -rf build

debug: clean
	ino build -f="$(FLAGS) -DMO_DEBUG"

serial: clean
	ino build -f="$(FLAGS) -DMO_DEBUG -DUI_SERIAL"

release: clean
	ino build -f="$(FLAGS)"

upload:
	ino upload

test_dir:
	[ -d build ] || mkdir build

build/Makefile: test_dir .git
	cd build && cmake ..

test: build/Makefile
	cd build && make && ./pomoduino2test
