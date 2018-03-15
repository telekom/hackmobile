# Tuino 1 Board

TUINO 1 is an Arduino Uno compatible board which has been developed for IoT applications, it has the form factor of the Arduino/Genuino Uno but with a series of additional features:<br/>
<br/>
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master/docs/tuino_revE.jpg"/>

* ATMega1284P processor - which has **128K** of FLASH and **16Kb** of RAM. You can now build much more complex sketches.
* 5/3.3V switch - use 3.3V sensors without any problem.
* 4 [GROVE](http://wiki.seeed.cc/Grove_System/) connectors - no need for external shields to add sensors.
* [RTC](http://www.st.com/en/clocks-and-timers/m41t62.html) with battery back up - always useful in an IoT application.
* [NFC](http://www.st.com/en/nfc/m24sr04-y.html) chip - leverage NFC for enhanced connectivity with smart phones.
* LiPO charging section with [power gauge](https://www.maximintegrated.com/en/products/power/battery-management/MAX17048.html) - you can check the battery level from your sketches.<br/>
* ON/OFF/RESET [Power Control](http://www.linear.com/product/LTC2955). You can switch on, switch off and reset the Tuino 1 all from 1 single button.
* SD Card slot - fully compatinle with the [Arduino SD](https://www.arduino.cc/en/reference/SD) library. Store your sensor data on SD card 

## TUINO 1 PINOUT
Here is the pinout of the Tuino 1<br/>

### TOP 
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master/docs/top_layer.png"/>

### HEADERS
* J4 - connection for external on/off/reset pushbutton
* J12 - fitted with header - NFC antenna connection 
* J13 - connection for external +5V power supply
* J14 - fitted with header - automatic power on. If jumper is fitted the board turns on automatically as soon as power is supplied.
* J15 - connection for external LiPO battery

### BOTTOM 
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master/docs/bottom_layer.png"/>


## DIFFERENCES WITH ARDUINO UNO
While the Tuino 1 is 100% software compatible with the Arduino Uno, there are two differences in the hardware pinout on the expansion shield connectors, and this could lead with some compatibility problems with some existing shields.<br/>

1. We only have 4 Analog Lines
  * A0
  * A1
  * A2
  * A3
  
  To maintain compatibility with the Arduino Uno shield pinout we added the I2C **SDA** and **SCL** on the **A4** and **A5** pins, but on the ATMega1284P these pins are not analog but only digital, thus we loose two analog inputs and gain two additional digital ones, **D14** and **D15**.<br/>
<br/>
2. Pins **D2/INT0** and **D3/INT1**, again due to the pinout of the AtMega1284P, are shared with the second serial. 
   The second serial is used for the **GMX** bus, and in case you are using a **GMX** module that is interfaced via UART, you cannot use these two pins.

   But if you aren't using the **GMX** bus you have a second serial on the expansion shield pinout and this could be convenient for many project!

## ATMega1284P Schematic
Here is the ATMega1284P connection on the Tuino 1 board. For reference and for better understanding of its functionalities.

<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master/docs/schematic_cpu_tuino.png"/>


## RTC
The RTC clock is based on the M41T62 chip.<br/>
Check the [Tuino HW](https://github.com/gimasi/TUINO_ONE/tree/master/tuino_libs/tuino_hw) section for software drivers.
<br/>

## NFC
The Tuino 1 one has an onboard NFC chip and a header to install an NFC antenna. The NFC chip is the M24SR04.<br/>
Check the [Tuino HW](https://github.com/gimasi/TUINO_ONE/tree/master/tuino_libs/tuino_hw) section for software drivers.
<br/>

## LiPO AND POWER GAUGE
The LiPO charging is driven by the MCP73831. A power gauge chip MAX17048 is present on the I2C bus so that you can always keep under control the charge level of the battery.<br/>
Check the [Tuino HW](https://github.com/gimasi/TUINO_ONE/tree/master/tuino_libs/tuino_hw) section for software drivers.
<br/> 

## microSD Card Slot
The Tuino 1 is compatible with the [Arduino SD](https://www.arduino.cc/en/reference/SD) library.
