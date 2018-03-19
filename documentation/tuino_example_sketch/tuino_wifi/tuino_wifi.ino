#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

WiFiUDP Udp;

char devAddress[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

// UBIRCH UDP IP and PORT
// IP: 34.248.246.47
// Port: 7070

IPAddress ubirch_ip(34, 248, 246, 47);   
int ubirch_port = 7070;



char ssid[] = "___WIFI_SSID____";     //  your network SSID (name)
char pass[] = "___PASSWORD___";  // your network password

int status = WL_IDLE_STATUS;     // the WiFi radio's status

// Ubirch packet Functions

void sendUbirchPacket(char *data_to_send)
{
    unsigned char ubirch_packet[512];
    char payload[500];
    int payload_len;
    
    String debug_payload;
    char string_byte[3];
    
    ubirch_packet[0] = 0x00;
    ubirch_packet[1] = 0xCE;
    
    
    ubirch_packet[2] = devAddress[4];
    ubirch_packet[3] = devAddress[5];
    ubirch_packet[4] = devAddress[6];
    ubirch_packet[5] = devAddress[7];
    
    ubirch_packet[6] = 0xD9;

    Serial.println("Sending Data to Ubirch");
    strcpy(payload,data_to_send);
    Serial.println(payload);
    payload_len = strlen( payload );

    Serial.print("Payload Len:");
    Serial.println(payload_len);
    
    ubirch_packet[7] = payload_len;

    for(int i=0;i<payload_len;i++ )
      ubirch_packet[8+i] = payload[i];

  /* 
   *  Debug
   */

 for (int i=0;i<payload_len+8;i++)
  {  
    sprintf(string_byte,"%02x",ubirch_packet[i]);
    Serial.print((char)ubirch_packet[i]);
    Serial.print("=");
    Serial.print(ubirch_packet[i],HEX);
    Serial.print("/");
    Serial.println(string_byte);
    
    
    
    debug_payload = debug_payload + string_byte;
  } 

  Serial.print("DEBUG:");
  Serial.println(debug_payload);
  
  /*
   * End Debug
   */

    Serial.println("Sending to:");
    Serial.println(ubirch_ip);
    Serial.println(ubirch_port);
    
    if ( Udp.beginPacket(ubirch_ip, ubirch_port) == 1 )
      Serial.println("UDP Open: OK");

    Serial.print("Num Bytes:");
    Serial.println(payload_len+8);
    
    Udp.write(ubirch_packet,payload_len+8);

    
    if ( Udp.endPacket() == 1 )
      Serial.println("UDP Sent: Ok");
}


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



void setup() {
   WiFi.setPins(GMX_GPIO7,GMX_INT,GMX_RESET,GMX_GPIO4);
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

 Serial.println( devAddress );
 
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("GMX-WiFi  not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWiFiData();

  Serial.print("starting UDP");
  Udp.begin(ubirch_port);


   // setup device address
  byte mac[6];
  WiFi.macAddress(mac);

  // Mac Address is 6 bytes 
  // Our Standard Device Adress is 8 bytes
 
  devAddress[0]=0x00;
  devAddress[1]=0x00;
  devAddress[2]=mac[5];
  devAddress[3]=mac[4];
  devAddress[4]=mac[3];
  devAddress[5]=mac[2];
  devAddress[6]=mac[1];
  devAddress[7]=mac[0];
}

void loop() {
  // put your main code here, to run repeatedly:
  int current_temperature;
  
   current_temperature = random(15,27);
  
   sendUbirchInt("temperature",current_temperature);

   delay(30000);
}

/*
 * Wifi Utilities
 */
 
void printWiFiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
