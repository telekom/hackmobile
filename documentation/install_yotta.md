# Calliope for Pro's: Installation and more guide

Before you can start to hack directly on the calliope with `C / C++` you need to install some build tools and software. Everything we need is available from GitHub or other public sites, and best of all its ***open source***.

## yotta
[yotta](https://github.com/ARMmbed/yotta) is a tool provided by [ARM](http://www.arm.com/products/processors/cortex-m), that makes its easier to deploy and build software with dependencies for the [ARM mbed platform](https://www.mbed.com/en/). It's comparable to [maven](https://www.mbed.com/en/), [gradle](gradle), and [cocoapods](cocoapods), but for embedded ARM chips like the [NRF51822](NRF51822) that are soldered on the calliope board.

## Install python and pip
At first you need to install `python` and `pip` to work with yotta, since it is written in python and distributed with pip. If you already installed python and pip on your system make sure you have at least `python 2.7.9` or later (not python 3) and `pip 9` or later installed.

`python` can be installed and downloaded from the [official source](https://www.python.org/downloads/release/python-2713/). (Please install python 2.x and not python 3.x)
`pip` will be also installed with python 2.7.9 or higher but you need to upgrade pip manually with the following commands:
* Mac OS X / Linux: `pip install -U pip`
* Windows: `python -m pip install -U pip`

If `pip` wasn't installed during the python installation you can manually install `pip`. Just follow the instructions from the [official site](https://pip.pypa.io/en/stable/installing/#installing-with-get-pip-py). If you get a permission error on your mac or linux machine just execute the command with `sudo` (e.g `sudo python get-pip.py`).

After installation you can check the versions with the following commands:
* `pip --version` the output should be similar to or a higher version: `pip 9.0.1 from /usr/local/lib/python2.7/site-packages (python 2.7)`
* `python --version` the output should be similar to or a higher version: `Python 2.7.13`

## Install yotta
To install yotta on your mac, windows, or linux machine please follow the official [yotta installation guide](http://docs.yottabuild.org/#installing) for your system:
* [Mac OS X](http://docs.yottabuild.org/#osx-manual-install) ***Note***: Don't use the Mac OS X yotta app, because its outdated. Install yotta manually.
* [Windows](http://docs.yottabuild.org/#installing-on-windows)
* [Linux](http://docs.yottabuild.org/#installing-on-linux)

After installation you should have at least `yotta 0.18.2` installed. (Verify the version using the command: `yotta --version` or `yt --version`.

Also please check if the path for `pip` and `python` are also correct
* `which pip`: `/usr/local/bin/pip`
* `which python`: `/usr/local/bin/python`

If the path arent the one above just add the following to your `~.bash_profile`:
```
export PATH="/usr/local/opt/python/libexec/bin:$PATH"
```

If you get some permission denied errors during the brew installation make sure you have the correct access rights for the `/usr/local/bin` folder:
```
sudo chown -R $(whoami):admin /usr/local
```

## Install srecord
[srecord](http://srecord.sourceforge.net) is used to create the final binaries for the calliope board, so its an essential dependency
* `Windows`, download from [sourceforge](https://sourceforge.net/projects/srecord/files/srecord-win32/1.64/).
* `Mac OS X`, download from [sourceforge](https://sourceforge.net/projects/srecord/files/srecord/1.64/) or install it with brew `brew install srecord`
* `Linux` download from [sourceforge](https://sourceforge.net/projects/srecord/files/srecord/1.64/) or install it with apt `sudo apt-get install srecord`

***Thats all.*** Now you can start hacking directly on the board.

## Examples
To familiarize yourself with the development process, start by downloading the samples, build one on your machine, and deploy the binary to you personal calliope board.

All source code related to the board can be found on the official [calliope GitHub page](https://github.com/calliope-mini/). There are several opensource projects, even for the core itself, you only need to focus on the examples in the [calliope playground](https://github.com/calliope-mini/calliope-playground) repo.

Simply clone the playground repo and build the sources:
```
git clone https://github.com/calliope-mini/calliope-playground.git
cd calliope-playground
yt build
```

You can find the generated binary in the following folder:
```
build/calliope-mini-classic-gcc/source/calliope-playground-combined.hex
```

To deploy the binary to your calliope board, copy and paste the hex file to the calliope usb drive. By default the RGB in the middle of the board should be blinking. Other examples can be found in the ```source``` folder.


## Documentation
Maybe you already noticed that the calliope board is based on [Micro:bit](http://microbit.org/de/) and there isn't much  documentation for the calliope board. [For the Micro:bit there is detailed documentation for all available components and runtime](https://lancaster-university.github.io/microbit-docs/). If you prefer to look directly at the source files (`.h` and `.cpp`), you will find them in the following folders from the playground example that you checked out earlier:

***General board singleton where all components are initialized***
* `yotta_modules/microbit/inc`
* `yotta_modules/microbit/source`

***Header and source files for the specific components***
* `yotta_modules/microbit-dal/inc/core`
* `yotta_modules/microbit-dal/inc/drivers`
* `yotta_modules/microbit-dal/inc/types`
* `yotta_modules/microbit-dal/source/core`
* `yotta_modules/microbit-dal/source/drivers`
* `yotta_modules/microbit-dal/source/types`


## Where to start from here
* Check out the C++ project template, to compile a programm by yourself:
  https://github.com/ubirch/telekom-nbiot-hackathon-2017/tree/master/nbiot-cpp-template
* More information about the BC95 NB-IoT Module can be found in the [NB-IoT documentation page](nb-iot.md)
* Take a look at the guide from the calliope team: https://github.com/ubirch/telekom-nbiot-hackathon-2017/blob/master/de-cpp-development.md#installation

## How to debug
The calliope provides are serial interface via the usb port. To read the out of the serial interface you can connect to the board with the following settings (Please note that the name of the serial device can be different from platform to platform but it should start with ```cu.usbmodem***```):

* Mac / Linux: ```screen /dev/cu.usbmodem14232 115200```
* Windows: We recommend [putty](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html) or [termite](https://www.compuphase.com/software_termite.htm) to access the data from the serial interface. A detailed description can be found [here](debug_windows.md).
