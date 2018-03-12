# Callipe Board

![Callipe Board](https://raw.githubusercontent.com/calliope-mini/calliope-mini.github.io/master/assets/v10/img/Calliope_mini_1.0_pinout_fin.jpg)  
Source: [Github Calliope Mini](https://github.com/calliope-mini/calliope-mini.github.io)

With the [Calliope mini](https://calliope.cc), you have countless creative possibilities in your hand. Whether you want to build a robot or send messages, you can create your own programs for the microprocessor and get things moving in no time at all with just a few clicks.

## The IoT-Board Contains The Following Components:

* **5x5 LED Matrix:** A total of 25 red LEDs which can be accessed as a group or individually
* **RGB-LED:** An almost unlimited number of colors can be created using the RGB-LED
* **Buttons:** A simple method of input are the two buttons, located on both sides of the board. The various contacts on the tips of the board can also be used as buttons.
* **Speakers and Microphone:** Using the speakers, you can play music or simple tones. The microphone can record sounds or speech
* **Sensors:** Motion, acceleration, temperature, and ambient light sensors, as well as a compass offer a number of data points enabling you to realize your ideas
* **Bluetooth:** The Bluetooth chip allows you to connect the board to a smartphone or tablet. Additionally, you can communicate with other boards
* **NB-IoT-Module:** Thanks to the [NB-IoT-Module](nb-iot.md) you can send collected data to the cloud using mobile data

## Three Ways to Program the Board
* **Visual Editor:**  
  Even if you are a newbie or are hesitant to code, using the visual editor you can simply program the board using drag & drop  
  **Link: http://pxt.calliope.cc/index.html**  
* **JavaScript:**  
  The easiest way to code for the board is using JavaScript. And you can seamlessly change between the visual editor and JavaScript  
  **Link: http://pxt.calliope.cc/index.html**  
* **C/C++:**  
  Your own functions, classes, structures, or shifting bits around: With C or C++ you have full control, and can access all the components on the board. The ARM mbed environment enables you to directly transfer compiled code to the board  
  **Documentation: [Install all dependencies](install_yotta.md), [compile your first programm](https://github.com/calliope-mini/calliope-project-template)** , **[debug your code](https://github.com/ubirch/telekom-nbiot-hackathon-2017/blob/master/de-cpp-development.md)**

## Pros still might want to know:
The Nordic [nRF51822](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF51822) chip used on the board is a Cortex M0 CPU with 16 kB RAM and 256 kB flash memory. Bluetooth is available in Version 4.0, including Low Energy. One SPI and I2C interface each are present and can be used using pins or Grove connectors. The NB-IoT Module ([BC95](http://www.quectel.com/product/gsmevb.htm)) is provided by queltec and it is connected to the board using the UART interface at 9600 Baud and transmits on Band 8 on the 900 MHz Frequency.

## Example Projects & More Information:
* https://www.hackster.io/calliope-mini/
* https://github.com/calliope-mini/
* https://github.com/calliope-mini/calliope-playground
* There is also a detailed information for the calliope and bunch of source code examples in the official repo from the callipe team: https://github.com/ubirch/telekom-nbiot-hackathon-2017
