/* _____  _____  __  __             _____  _____ 
  / ____||_   _||  \/  |    /\     / ____||_   _|
 | |  __   | |  | \  / |   /  \   | (___    | |  
 | | |_ |  | |  | |\/| |  / /\ \   \___ \   | |  
 | |__| | _| |_ | |  | | / ____ \  ____) | _| |_ 
  \_____||_____||_|  |_|/_/    \_\|_____/ |_____|
  (c) 2017 GIMASI SA                                               

 * gmx_nbiot.h
 *
 *  Created on: July 27, 2017
 *      Author: Massimo Santoli
 *      Brief: Tuino 1 interface for GMX-NB module family
 *      Version: 1.0
 *
 *      License: it's free - do whatever you want! ( provided you leave the credits)
 *
 */


#define GMXNB_KO                      -1 

#define GMXNB_OK                      0 

#define GMXNB_NOT_PRESENT             10
#define GMXNB_NO_SERIAL               20

#define GMXNB_AT_ERROR                30
#define GMXNB_AT_GENERIC_ERROR        99

#define GMXNB_LED_ON                  1
#define GMXNB_LED_OFF                 0

#define GMX_UART_INTERFACE            1
#define GMX_SPI_INTERFACE             2

#define GMX_UART_SPEED                9600
#define GMX_UART_TIMEOUT              10000

#define GMX_BOOT_DELAY                4000


#define NB_NETWORK_JOINED             1
#define NB_NETWORK_NOT_JOINED         0
 
/*
 * GMX-LR1 Init function
 *  the only parameter is the function for the RxData callback
 */
 
byte gmxNB_init(String, String,void (*function)());
byte gmxNB_getVersion(String& version);
byte gmxNB_getIMEI(String& imei);

byte gmxNB_radioON(String& param);
byte gmxNB_setAPN(String APN);
byte gmxNB_isNetworkJoined(void);

byte gmxNB_getCSQ(String& csq);


void gmxNB_start();


// TX & RX Data
byte gmxNB_TXData(String data);
byte gmxNB_RXData(String& data);



/*
 * Utilities
 */
 
byte gmxNB_Led1(byte led_state);
byte gmxNB_Led2(byte led_state);
byte gmxNB_Led3(byte led_state);

void gmxNB_Reset(void);
void gmxNB_StringToHex(String string, char *data, int *len );



