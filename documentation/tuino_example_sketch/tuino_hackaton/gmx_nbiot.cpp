/* _____  _____  __  __             _____  _____ 
  / ____||_   _||  \/  |    /\     / ____||_   _|
 | |  __   | |  | \  / |   /  \   | (___    | |  
 | | |_ |  | |  | |\/| |  / /\ \   \___ \   | |  
 | |__| | _| |_ | |  | | / ____ \  ____) | _| |_ 
  \_____||_____||_|  |_|/_/    \_\|_____/ |_____|
  (c) 2018 GIMASI SA                                               

 * gmx_nbiot.cpp
 *
 *  Created on: March 15th, 2018
 *      Author: Massimo Santoli
 *      Brief: GMX NBIoT driver with configuration for T-Mobile Austria NBIoT Network
 *      Version: 1.0
 *
 *      License: it's free - do whatever you want! ( provided you leave the credits)
 *
 */
#include "Arduino.h"
#include "gmx_nbiot.h"
#include "Regexp.h"

#define DEBUG 0

String gmxSerialString;

// RegExp Engine
MatchState ms;
char buf[1024]; 

//
String dummyResponse;

byte gmxNB_interface = GMX_UART_INTERFACE;

void(*_NBRing)();

String _udp_socket_ip;
String _udp_port;

//
// ISR 
//
ISR(PCINT1_vect) {     
  if (digitalRead(GMX_INT)==0) {
    if (_NBRing)
      _NBRing();
  }
}

void _resetGMX(){

  pinMode(GMX_RESET,OUTPUT);
  // Reset 
  digitalWrite(GMX_RESET,HIGH);
  delay(100);
  digitalWrite(GMX_RESET,LOW);
  delay(100);
  digitalWrite(GMX_RESET,HIGH);
}


void _log(String data )
{
  #ifdef DEBUG
    Serial.println(data);
  #endif
}

void _sendCmd(String in) {
  int len = in.length();
  long int start_timeout;

/*
 Serial.println("----->");
 Serial.print("SENDING: ");
 Serial.println(in);
 Serial.println("----->");
*/
     
  //  send data
  for (int i=0; i<len; i++) {
    if ( gmxNB_interface == GMX_UART_INTERFACE )
    {
      Serial1.write(in.charAt(i));
    }
    delay(1);
  }
  
  delay(100);

  
  if ( gmxNB_interface == GMX_UART_INTERFACE )
  {
     start_timeout = millis();
     while(Serial1.available()==0){
      if (( millis() - start_timeout ) > GMX_UART_TIMEOUT  )
      {
        Serial.println("TIMEOUT on :"+in);
        break;
      }
     }
  }
}

byte _parseResponse(String& response) {
  
  char cmd[1024];
  
  gmxSerialString="";
  
  // Read Serial
  while (Serial1.available()>0) 
  {
      while (Serial1.available()>0) 
      {
        char c = Serial1.read(); 
        gmxSerialString += c;
      }
      
      delay(10);
  }

  gmxSerialString.toCharArray(cmd,gmxSerialString.length());


     Serial.println("<-----");
     Serial.print("RESPONSE: ");
     Serial.println(gmxSerialString);
     Serial.println("<-----");
     
  // Parse Response
  ms.Target(cmd);
  char result = ms.Match ("(.*)\r\nOK", 0);
  if ( result == REGEXP_MATCHED )
  { 
    ms.GetCapture (buf, 0);
  
    response = String(buf);
     
    // remove second \r\n => Not very elegant to optimize
    response.toCharArray(cmd,response.length());
    response = String(cmd);
     
    return (GMXNB_OK);
  }

  // Check for Errors
  result = ms.Match ("(.*)\r\nERROR", 0);
  if ( result == REGEXP_MATCHED )
  {
    return(GMXNB_AT_ERROR);
  }
    
  return(GMXNB_AT_GENERIC_ERROR);
}


/* GMXLR Commands Interface */

byte gmxNB_init(String upd_addre, String udp_port ) 
{
    String response;
    byte init_status = GMXNB_KO;

    _udp_socket_ip = upd_addre;
    _udp_port = udp_port;
    
    _log("GMXNB Init");

    pinMode(GMX_GPIO1,OUTPUT);
    pinMode(GMX_GPIO2,OUTPUT);
    pinMode(GMX_GPIO3,OUTPUT);
    digitalWrite(GMX_GPIO1,LOW);
    digitalWrite(GMX_GPIO2,LOW);
    digitalWrite(GMX_GPIO3,LOW);

    _resetGMX();

    // Init Interface
    if ( gmxNB_interface == GMX_UART_INTERFACE )
    {
        // Setup Serial
        if(Serial1) {
            Serial1.begin(GMX_UART_SPEED);
           _log("GMX Serial Interface");
            init_status = GMXNB_OK;
        } 
        else 
        {
          return(GMXNB_NO_SERIAL);
        }
    }

    // Setup Interrupt PIN for Rx
    *digitalPinToPCICR(GMX_INT) |= (1<<digitalPinToPCICRbit(GMX_INT));
    *digitalPinToPCMSK(GMX_INT) |= (1 << digitalPinToPCMSKbit(GMX_INT));


    // delay to wait BootUp of GMX-LR
    delay(GMX_BOOT_DELAY);
    
    _sendCmd( "AT\r" );
    _parseResponse(response);
    _sendCmd( "AT\r" );
    _parseResponse(response);
    
    
}

/* Version */
byte gmxNB_getVersion(String& version)
{
   _sendCmd( "AT+CGMR\r" );
   return( _parseResponse(version) );
}

/* IMEI */
byte gmxNB_getIMEI(String& imei)
{
  byte status;
   _sendCmd( "AT+CGSN=1\r" );


  if ( (status = _parseResponse(dummyResponse)) == GMXNB_OK ) 
  {

      byte index = dummyResponse.indexOf(":");
      if ( index != -1 )
      {
        imei = dummyResponse.substring(index+1,dummyResponse.length());
      }
      
  }   

   return( status );
}


byte gmxNB_getCSQ(String& csq)
{
   _sendCmd( "AT+CSQ\r" );
   return( _parseResponse(csq) );
}

void gmxNB_start() 
{

    _sendCmd( "AT+NCONFIG=CR_0354_0338_SCRAMBLING,TRUE\r" );
    _parseResponse(dummyResponse);
   
   _sendCmd( "AT+NCONFIG=CR_0859_SI_AVOID,TRUE\r" );
   _parseResponse(dummyResponse);
   
   _sendCmd( "AT+CFUN=0\r" );
   _parseResponse(dummyResponse);

   _sendCmd( "AT+CGDCONT=1,\"IP\",\"m2m.nbiot.t-mobile.at\"\r" );
   _parseResponse(dummyResponse);
   
   _sendCmd( "AT+CFUN=1\r" );
   _parseResponse(dummyResponse);

   _sendCmd( "AT+NBAND=8\r" );
   _parseResponse(dummyResponse);
  
   _sendCmd( "AT+COPS=1,2,\"23203\"\r" );
   _parseResponse(dummyResponse);
     
}

/* Radio */
byte gmxNB_radioON(String& param)
{
   _sendCmd( "AT+CFUN=1\r" );
   return( _parseResponse(param) );
}


/* APN */

byte gmxNB_setAPN(String APN)
{
   _sendCmd( "at+cgdcont=1,\"IP\",\""+APN+"\"\r" );
   return( _parseResponse(dummyResponse) );
}


/* Check Network */

byte gmxNB_isNetworkJoined(void)
{
  byte status;
  char cmd[16];
  String tmp;
  
   _sendCmd( "at+cgatt?\r" );

   if ( (status = _parseResponse(dummyResponse)) == GMXNB_OK ) 
  {

      byte index = dummyResponse.indexOf(":");
      if ( index != -1 )
      {
        tmp = dummyResponse.substring(index+1,dummyResponse.length());

        tmp.toCharArray(cmd,tmp.length());
        
        if (cmd[0] == '0'){
          return NB_NETWORK_NOT_JOINED;
        }
        if (cmd[0] == '1'){
          return NB_NETWORK_JOINED;
        }
      }
      
  }   

  return (status); 
}




// TX & RX Data

byte gmxNB_TXData(String data) {

  int num_bytes;
Serial.println( data );
   num_bytes = data.length()/2;
   
   _sendCmd("at+nsocr=DGRAM,17,"+_udp_port+"\r");
   _parseResponse(dummyResponse);
 
   _sendCmd("at+nsost=0,"+_udp_socket_ip+","+_udp_port+","+String(num_bytes)+","+data+"\r" ); 
   _parseResponse(dummyResponse);
   _sendCmd("at+nsocl=0\r");
   return( _parseResponse(dummyResponse) );
  
}


byte gmxLR_RXData(String& data, int *port)
{
  byte status;
  String str1,str2;
  
    // need a delay because the interrupt arrives too fast
    delay(100);
   _sendCmd( "AT+RECVB=?\r" );
   status = _parseResponse(dummyResponse);

   if (status == GMXNB_OK )
   {
      byte index = dummyResponse.indexOf(":");
      if ( index != -1 )
      {
        str1 = dummyResponse.substring(0,index);
        str2 = dummyResponse.substring(index+1,dummyResponse.length());
        data = String(str2);
        *port = str1.toInt();
      }   
   }
}


void gmxNB_Reset(void){
  String command = String("AT+NRB\r");
  int len = command.length();
  
  //  send data
  for (int i=0; i<len; i++) {
    if ( gmxNB_interface == GMX_UART_INTERFACE )
    {
      Serial1.write(command.charAt(i));
    }
    delay(1);
  }
  
  delay(GMX_BOOT_DELAY);
 
}

void gmxNB_StringToHex(String string, char *data, int *len )
{
  char tmp[255];
  char temp[2];
  int j=0;
  
  string.toCharArray(tmp,255);

  for (int i = 0; i < strlen(tmp); i += 2)
  {
    strncpy(temp, &tmp[i], 2);

    temp[0] = toupper(temp[0]);    // Convert to upper case
    temp[1] = toupper(temp[1]);
    
    // Convert hex string to numeric:
    data[j] = (temp[0] <= '9') ? (temp[0] - '0') : (temp[0] - 'A' + 10);
    data[j] *= 16;
    data[j] += (temp[1] <= '9') ? (temp[1] - '0') : (temp[1] - 'A' +10);

    j++;
  }

    *len = j;
}

byte gmxNB_Led1(byte led_state) 
{
   digitalWrite(GMX_GPIO1,led_state);
   
}
byte gmxNB_Led2(byte led_state)
{
   digitalWrite(GMX_GPIO2,led_state);

}
byte gmxNB_Led3(byte led_state)
{
   digitalWrite(GMX_GPIO3,led_state);
}

