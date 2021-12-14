//////BMP180//////
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
double currentAirPressure = 100865;          //Current air pressure of the location. VERY IMPORTANT
                                             //Set to pressure in Kenosha 4/25/19
                                             //10m=120Pa difference
// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4;
//=================================================================================//
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  Serial.begin(9600);
  // BMP180 Initialization //
  //Serial.println("REBOOT");
  bmp.begin();
}
//=================================================================================//
void loop() {
  Serial.print("I am working");
  //printData();
  initialSet();
  delay(10);
}
void printData() {
  Serial.print("  Temp (C)="); Serial.print(bmp.readTemperature());                              //Print temperature values in Celsius
  Serial.print("\t");
  Serial.print("  Pressure (Pa)="); Serial.print(bmp.readPressure());                            //Print pressure values in Pascal
  Serial.print("\t");
  Serial.print("  Altitude (m)="); Serial.print(bmp.readAltitude(currentAirPressure));           //Print altitude values in Meters
  Serial.print("\t");
  Serial.print("  Time (ms)="); Serial.println(millis());                                         //Print time values in Milliseconds
}

void initialSet()
{
  const float ARMINGALT = 100;
  float groundLevel = 0;
  for(int i = 0; i < 20; i++)
  {
    groundLevel += bmp.readAltitude(currentAirPressure);
    delay(10);
  }
  groundLevel = (groundLevel / 20);
  while(bmp.readAltitude(currentAirPressure) < ARMINGALT)
  {
    Serial.print("Not arming yet");
    Serial.print("\t");
    Serial.print("Altitude: ");
    Serial.print(bmp.readAltitude(currentAirPressure));
    Serial.print("\n");
    delay(10);
  }
  while(bmp.readAltitude(currentAirPressure) > groundLevel)
  {
    Serial.print("Not at groundLevel yet");
    Serial.print("\t");
    Serial.print("Altitude: ");
    Serial.print(bmp.readAltitude(currentAirPressure));
    Serial.print("\n");
    Serial.print("Ground Level = ");
    Serial.print(groundLevel);
    delay(10);
  }
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 1000; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000); 
  }
  delay(500); // One second delay
}
