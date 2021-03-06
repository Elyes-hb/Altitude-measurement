/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp1; // I2C
Adafruit_BMP280 bmp2; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

int P_atm = 1000; //Pressure in hPa (0,5 bar = 500 hPa)
const int Mvol= 1000; //in Kg/m3
float h = 0; //hauteur 
const float g = 9.82; //in m/s2
float Dif = 0; //pressure difference
int p = 0;


void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  if (!bmp1.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1); }

      if (!bmp2.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp1.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */                 
}

void loop() {

int p1 = 0;
int p2 = 0;

    Serial.print(F("Pressure = "));
    Serial.print(bmp1.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp1.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);

    Serial.print(F("Pressure 2 = "));
    Serial.print(bmp2.readPressure());
    Serial.println(" Pa");


h = bmp1.readPressure();
p1 = PressureCal(Mvol,g,h,P_atm);
delay(100);
h = bmp2.readPressure();
p1 = PressureCal(Mvol,g,h,P_atm);


Dif = p1 - p2;



if (Dif >= 500 ) {

//perform action 1
 
}

else if (Dif < 500 ) {

//perform action 2
}


    
}

int PressureCal(const int Mvol1, const float g1,int h1,int P_atm1){
  float P;
  P = (g1 * Mvol1 * h1 *1000)+P_atm1;
  p = (int)P;
  return p;
}
