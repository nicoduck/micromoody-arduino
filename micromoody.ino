//This short arduino sketch will set all attached MicroMoodys to blue.
//Written by @nicoduck, feel free to ask if you have any questiones.
//Based on latest MicroMoody firmware (as of 2013-08-01). Future revisions might change slightly. 
//Arduino normally uses A4 and A5 as I2C ports but changed that on newer ones.
//Consult Arduino documentation to find out wiring for your type.

#include <Wire.h>

void setup()
{
  Wire.begin(); // Join i2c bus as master
}

  byte opmode = 0x00; //We want to set a simple colour. 0x00 means "no fade", 0x04 would use an following speed (fading time).
  byte speed = 0x00;  //Used with opmode 0x04 to set fade speed. Do we need speed here? Nope.
  byte red = 0x00;    //Not red.
  byte green = 0x00;  //Not green.
  byte blue = 0xff;   //Just blue, nothing else.
  byte addrhigh = 0xff; //High byte of the address, starts at 0x00.
  byte addrlow = 0xff;  //Low byte of the address, 0x01 for the first MicroMoody.
  //addrhigh = addrlow = 0xff is broadcast, this will affect alle MicroMoodys.
  //addrhigh = 0x00, addrlow 0x01 would be the MicroMoody with the address 0x0001.
  //Your delievery package contains information about the initial address of your microMoody.

void loop()
{
  byte i2c_addr = 0x11; //i2c address of the MicroMoody, normally 0x11
  Wire.beginTransmission(i2c_addr); //Send the data in the brackets ;-)
  Wire.write(opmode); 
  Wire.write(speed);
  Wire.write(red);
  Wire.write(green);
  Wire.write(blue);
  Wire.write(addrhigh);
  Wire.write(addrlow); //the order of sending the data is important, as the data is send plain without any descriptors.
  //byte stufftosend[7]; //We can also put the data into an array to send it...
  //   stufftosend[0] = opmode; //...but it makes no real difference. (That's at least what I believe, feel free to correct me if I'm wrong.)
  //   stufftosend[1] = speed;
  //   stufftosend[2] = red;
  //   stufftosend[3] = green;
  //   stufftosend[4] = blue;
  //   stufftosend[5] = addhigh;
  //   stufftosend[6] = addlow;
  //Wire.write(stufftosend, 7); //if we use an array, we have to send it ;-)
  Wire.endTransmission(); //Sending data finally out, after being queued by Wire.write
  delay (9001); //Over 9000!!! 
  //Well, that delay can be as long as you want because the MicroMoody is just told to be blue.
}
