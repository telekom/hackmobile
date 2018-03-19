# Tuino 1 Example Sketch

Here you can find some example sketches to connect via NBIoT or Wifi to the Ubirch backend.<br/>
<br/>
## Tuino Hackton Sketch 
This example sketch will use both the temperature and Oled screen present in the Tuino Kit and via NBIoT will send data to the Ubirch backend.<br/>
In the project you will find the gmx_nbiot.cpp and gmx_nbiot.h libraries that will enable you to connect to the NBIoT network.<br/>The libraries are already configured to work with T-Mobile Austria network.
The usage is very simple, essentially you need only 3 functions:<br/>

  * gmxNB_init(String udp_ip,String up_port);
  Setup the NBIoT library with the IP and PORT endpoint where data has to be transmitted.

  * gmxNB_start();
  Start the NBIoT stack - in the library you will find the configuration for the T-Mobile Austria network ( if you want to connect to another network you need to change the configuration in the source: APN and OPS number).

  * gmxNB_TXData(String payload);
  Transmit the hexdecimal string in payload to the UDP endpoint.

In the sketch you will also find some example of function that send an <b>int</b> or <b>text</b> payload to Ubirch.

```c
void sendUbirchInt(char *key, int value)
{
   char payload[500];
   sprintf(payload,"{\"%s\":%d}",key,value);

   sendUbirchPacket(payload);
}


void sendUbirchText(char *key, char *string)
{
   char payload[500];
   sprintf(payload,"{\"%s\":\"%s\"}",key,string);

   sendUbirchPacket(payload);

}
```

<br/>
As you can we are passing a key/value pair to the function and then building a JSON payload that will be sent to Ubirch.

## Tuino Wifi Sketch

The Wifi sketch simulates a random temperature and trasmits it to the Ubirch Backend.<br/>
It behaves essentially in the same way as the NBIoT example.<br/>
You simply need to configure your SSID and Passowrd at the beginning of the code, and then call the sendUbirchInt or sendUbirchText to send data to the backend.
<br/>
