#include "Conceptinetics.h"

#define DMX_SLAVE_CHANNELS   10

// Configure a DMX slave controller
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

const int ledPin = LED_BUILTIN;

int RedPin = 10;      // Arduino driving pin for Red
int GreenPin = 11;    // Arduino driving pin for Green
int BluePin = 9;      // Arduino driving pin for Blue

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
  dmx_slave.enable();

  // Set start address to 1, this is also the default setting
  // You can change this address at any time during the program
  dmx_slave.setStartAddress(1);

  // Set led pin as output pin
  pinMode(ledPin, OUTPUT);

  pinMode(RedPin, OUTPUT); // Init Arduino driving pins
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop()
{
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

  setColor(dmx_slave.getChannelValue(1), dmx_slave.getChannelValue(2), dmx_slave.getChannelValue(3));
}
