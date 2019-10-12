#include "Conceptinetics.h"

//
// CTC-DRA-13-1 ISOLATED DMX-RDM SHIELD JUMPER INSTRUCTIONS
//
// If you are using the above mentioned shield you should 
// place the RXEN jumper towards G (Ground), This will turn
// the shield into read mode without using up an IO pin
//
// The !EN Jumper should be either placed in the G (GROUND) 
// position to enable the shield circuitry 
//   OR
// if one of the pins is selected the selected pin should be
// set to OUTPUT mode and set to LOGIC LOW in order for the 
// shield to work
//

//
// The slave device will use a block of 10 channels counting from
// its start address.
//
// If the start address is for example 56, then the channels kept
// by the dmx_slave object is channel 56-66
//
#define DMX_SLAVE_CHANNELS   10 

//
// Pin number to change read or write mode on the shield
// Uncomment the following line if you choose to control 
// read and write via a pin
//
// On the CTC-DRA-13-1 shield this will always be pin 2,
// if you are using other shields you should look it up 
// yourself
//
///// #define RXEN_PIN                2


// Configure a DMX slave controller
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

// If you are using an IO pin to control the shields RXEN
// the use the following line instead
///// DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS , RXEN_PIN );

const int ledPin = LED_BUILTIN;

int RedPin = 10;      //Arduino driving pin for Red
int GreenPin = 11;    //Arduino driving pin for Green
int BluePin = 9;      //Arduino driving pin for Blue


int relay1 = 4;
int relay2 = 5;
int relay3 = 6;


void setColor(int red, int green, int blue)
{
  analogWrite(RedPin, red);
  analogWrite(GreenPin, green);
  analogWrite(BluePin, blue);

}

// the setup routine runs once when you press reset:
void setup() {             
  
  // Enable DMX slave interface and start recording
  // DMX data
  dmx_slave.enable ();  
  
  // Set start address to 1, this is also the default setting
  // You can change this address at any time during the program
  dmx_slave.setStartAddress (1);
  
  // Set led pin as output pin
  pinMode ( ledPin, OUTPUT );
  
  pinMode(RedPin, OUTPUT);    //Init Arduino driving pins
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
  //
  // EXAMPLE DESCRIPTION
  //
  // If the first channel comes above 50% the led will switch on
  // and below 50% the led will be turned off
  
  // NOTE:
  // getChannelValue is relative to the configured startaddress
  if ( dmx_slave.getChannelValue (1) > 127 )
    digitalWrite ( ledPin, HIGH );
  else
    digitalWrite ( ledPin, LOW );
    

  if ( dmx_slave.getChannelValue (4) > 127 )
    digitalWrite ( relay1, HIGH );
  else
    digitalWrite ( relay1, LOW );

  if ( dmx_slave.getChannelValue (5) > 127 )
    digitalWrite ( relay2, HIGH );
  else
    digitalWrite ( relay2, LOW );

  if ( dmx_slave.getChannelValue (6) > 127 )
    digitalWrite ( relay3, HIGH );
  else
    digitalWrite ( relay3, LOW );

  setColor(dmx_slave.getChannelValue (1), dmx_slave.getChannelValue (2), dmx_slave.getChannelValue (3));

}
