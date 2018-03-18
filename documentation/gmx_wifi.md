# GMX Wifi Module

The GMX WiFi module is based on the Atmel ATWINC1500 so its compatible with the Arduino [WIFI101](https://www.arduino.cc/en/Reference/WiFi101) library.<br/><br/>
<img src="https://raw.githubusercontent.com/gimasi/GMX-WIFI/master/assets/gmx_wifi.png"/>
<br/>
<br/>
To install the Wifi101 library you need to go to the Manage Library menu option. Sketch->Include Library->Manage Libraries...
<br/><br/>
<img src="https://raw.githubusercontent.com/gimasi/GMX-WIFI/master/assets/install1.png"/>
<br/>
<br/>
Then type in the search text area 'Wifi101'
<img src="https://raw.githubusercontent.com/gimasi/GMX-WIFI/master/assets/install2.png"/>
<br/>
<br/>
And finally click install.<br/>
Once installed you are ready to go, you can try one of the examples that come with the Library.<br/><br/>
<b>Remember</b> You need to configure the Wifi module with the correct pins of the Tuino, this is what you need to execute in the setup function of your sketch:
```c

void setup() {
  WiFi.setPins(GMX_GPIO7,GMX_INT,GMX_RESET,GMX_GPIO4);
  ...
  ...
  rest of your code
}
```