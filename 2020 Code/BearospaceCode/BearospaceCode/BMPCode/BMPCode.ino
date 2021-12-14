///////////BMP180//////////
#include <Adafruit_BMP085.h>       
Adafruit_BMP085 bmp;                



/////////////GLOBAL VARIABLES///////////////////
bool gotGroundPressure = false; //changed to false once a ground pressure is obtained
double groundPressure = 0;



////////////////////FUNCTION DECLARATIONS////////////////////////////////
double getGroundPressure();   //calculates the ground pressure by averaging pressure readings
                              //taken while rocket is on the launch pad
void getBmpReadings(double &T, double &P, double &A, double&groundPressure);



////////////////RUN PROGRAM//////////////////////////
void setup() 
{
  Serial.begin(9600);   // BMP180 Initialization //
  bmp.begin();          //Serial.println("REBOOT");
  //bmp.readTemperature();
}

void loop() 
{
  double T,P,A;          // variables to Store Temp, Pressure and Altitude values

  if (gotGroundPressure == false)   
  {
    Serial.print("  Initial Temp (C)="); Serial.print(bmp.readTemperature());
    Serial.print("\t");
  
    //averages over sample size set to 1000 to determine pressure at 0 altitude
    //this function is performed only on the first iteration of the loop() function
    groundPressure = getGroundPressure();
    Serial.print("  Ground Pressure (Pa)="); 
    Serial.print(groundPressure);
    Serial.print("\n");
    gotGroundPressure = true;
  }
  else
  {
    getBmpReadings(T, P, A, groundPressure);
  }
  
  delay(50);
}





/////////////////////FUNCTIONS////////////////////////
double getGroundPressure()
{
  int sampleSize = 300;
  double pressureValues[sampleSize];
  double sum = 0;
  
  for (int i=0; i<sampleSize; i++)
  {
    pressureValues[i] = bmp.readPressure();
    sum = sum + pressureValues[i];
  }

  return sum / sampleSize;
}


void getBmpReadings(double &T, double &P, double &A, double &groundPressure)
{
  T = bmp.readTemperature();
  Serial.print("  Temp (C)="); Serial.print(T);         //Print temperature values in Celsius
  Serial.print("\t");

  P = bmp.readPressure();
  Serial.print("  Pressure (Pa)="); Serial.print(P);    //Print pressure values in Pascal
  Serial.print("\t");

  A = bmp.readAltitude(groundPressure)/3.28084;
  Serial.print("  Altitude (ft)="); Serial.print(A);     //Print altitude values in Meters
  Serial.print("\t");
  Serial.print("  Time (s)="); Serial.println(millis()/1000.0);
  
}  
