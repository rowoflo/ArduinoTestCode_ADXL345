/*
 -------------------------------------------------------------------------------
 main.cpp
 ADXL345 Project
 
 This is test code for the ADXL345 class. ADXL345 uses I2C.
 Pins:
    VCC to 3.3V
    CS to 3.3V
    GND to ground
    SDA to pin 4
    SCL on pin 5
 
 Initially created by Rowland O'Flaherty (rowlandoflaherty.com) on 12/18/11.
 
 Version 1.0
 -------------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
// Includes and Defines
//------------------------------------------------------------------------------
#include <Arduino.h>
#include <ADXL345.h>


//------------------------------------------------------------------------------
// Helper Function Declarations
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Global Varible Declarations
//------------------------------------------------------------------------------
ADXL345 adxl;


//------------------------------------------------------------------------------
// Setup Function - Initializes Arduino
//------------------------------------------------------------------------------
void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);
	adxl.initialize();
    
    //set activity/ inactivity thresholds (0-255)
    adxl.setActivityThreshold(75); //62.5mg per increment
    adxl.setInactivityThreshold(75); //62.5mg per increment
    adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
    
    //look of activity movement on this axes - 1 == on; 0 == off 
    adxl.setActivityX(1);
    adxl.setActivityY(1);
    adxl.setActivityZ(1);
    
    //look of inactivity movement on this axes - 1 == on; 0 == off
    adxl.setInactivityX(1);
    adxl.setInactivityY(1);
    adxl.setInactivityZ(1);

}

//------------------------------------------------------------------------------
// Loop Function - Arduino Program Loop
//------------------------------------------------------------------------------
void loop()
{
    int x, y, z;
	double xyz[3];
    double theta, phi;
    adxl.readAccel(&x, &y, &z);  // read the accl values into variables x,y,z
    adxl.get_Gxyz(xyz); // read accl value in units of g into xyz[0-2]
    adxl.rollPitch(theta, phi);
    
    Serial.print("X:");
    Serial.print(x);
    Serial.print("\t");
    Serial.print(xyz[0]);
    
    Serial.print("\tY:");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(xyz[1]);
    
    Serial.print("\tZ:");
    Serial.print(z);
    Serial.print("\t");
    Serial.print(xyz[2]);
    
    Serial.print("\tTheta:");
    Serial.print(theta *  57.2957795131);
    Serial.print("\tPhi:");
    Serial.println(phi *  57.2957795131);
    
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(100);
}

//------------------------------------------------------------------------------
// Helper Functions
//------------------------------------------------------------------------------

