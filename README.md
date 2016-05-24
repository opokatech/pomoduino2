# Pomoduino2

This project is a simple [pomodoro] hardware timer using [arduino] uno with 16x2
lcd display, 2 buttons and a buzzer.

It keeps track of finished pomodoros (saves them to non-volatile memory) and
counts them up. The logic is described below.

A prototype with Arduino looks like this:

![pomoduino2 arduino proto](/doc/images/arduino_proto.jpg?raw=true "Pomoduino2 prototype with arduino").

... and using nano - like this:

![pomoduino2 nano proto](/doc/images/nano_proto.jpg?raw=true "Pomoduino2 prototype with nano").


# Logic - description

There are 3 timers:
- 25 minutes (aka pomodoro),
- 5 minutes (aka short break),
- 15 minutes (aka long break)

Pressing (and releasing) button 1 (B1) cycles through them.

Pressing (and releasing) button 2 (B2) starts a timer.

When timer elapses it goes automatically to a next one, as described in
[pomodoro] method, i.e. 25 - 5 - 25 - 5 - 25 - 5 - 25 - 15 - 25 - 5 ...

Number of finished pomodoros is visible in the top right corner and also
visualized as a progress bar in the bottom line.

Pressing B2 while running pauses the state. Pressing (and releasing) again makes
it continue.

Holding B2 longer (3s) during pause cancels the timer - it goes back to `ready`
state.

Holding B2 longer (3s) in ready state clears the number of pomodoros done so
far.

The pomodoros are stored in eeprom and thus survive power off.

On a diagram it looks like so:

![state diagram of pomoduino2 timer](/doc/images/pomoduino2_state_diagram.png?raw=true "State diagram").

The drawing was made with [draw.io](https://www.draw.io/).

# Schematic

The components were connected as depicted below:

![sketch of pomoduino2 timer](/doc/images/arduino_sketch_small.png?raw=true "Sketch diagram").


# Building

## Hardware

- [arduino] - I used uno and nano328 but should work with others too. As you can
  see it just uses input from 2 buttons and several outputs (LCD, buzzer) so it
  could be adapted to any device having digital I/Os
- 16x2 LCD display - although the software is made so that the UI class, which
  now uses LCD, can be easily replaced by literally anything. As an example
  there is src-alternative/ui/serial/UI, which spits out something on Serial
  console depending on current state. Yet another example (included) is a
  variant using 5 LEDs as "user interface".
- 10k potentiometer (optional) - for controlling contrast. If you don't want
  that just use some resistor placed between V0 pin of the LCD and ground. For
  me 3.3k Ohm worked well, however using a capacitor (100uF) as you can see here:
  [here](/doc/images/nano_sketch_big.png) worked best (forming simple RC
  filter with D5 as PWM).

- 2 buttons
- buzzer - although, again, it can be replaced by any device controller by
  digital output, for example a LED.



## Software

### Quickstart

I'm using [debian] so I could do just this:
```sh
$ apt-get install arduino virtualenvwrapper cmake g++
$ mkvirtualenv pomodoro2
$ pip install ino
```

Then in the directory where this repository was cloned:
```sh
$ make release # to build a ready to use version
$ make upload # to upload compiled binary to the arduino
```

If you want to play a bit with it there are few more commands, like:

```sh
$ git submodules update --init # to fetch google tests/mock
$ make test # to compile and run tests

$ make debug # to build a debug version (see below)
$ make serial # to build a debug version with UI_Serial instead of UI_Full
```

### Some explanations

To compile I used [ino]. I really recommend that as an alternative to the
official IDE - especially if you would like to:
- use your favourite text editor,
- be able to easily adjust compile options
- make automated builds and testing.

That code is very likely to work using the standard [arduino] IDE, provided that
the files are put in right directories. But I neither tested that nor plan to.

The `debug` target adds some extra debug messages which are spit out on serial
interface (with `ino serial` you can watch it) AND it changes times of pomodoro
periods from minutes to seconds which is very useful for testing.

For testing the code I used [google test] which also includes google mock. I
used both as submodules (they are in `/modules` directory). It matters of
course only if you need/want to run tests.

# License

[MIT](LICENSE)

----
Documentation was tested using [dillinger.io](http://dillinger.io/).

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

[arduino]: <https://www.arduino.cc/>
[debian]: <https://www.debian.org/>
[ino]: <http://inotool.org/>.
[googletest]: <https://github.com/google/googletest>
[pomodoro]: <https://en.wikipedia.org/wiki/Pomodoro_Technique>
