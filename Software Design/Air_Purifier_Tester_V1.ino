#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Adafruit_CCS811.h"
//OLED Configuration
#define OLED_CLK 13
#define OLED_MOSI 11
#define OLED_CS 10
#define OLED_DC 8
#define OLED_RESET 9

// software SPI
Adafruit_SSD1305 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_BME680 bme;
Adafruit_CCS811 ccs;
void setup() {
  Serial.begin(9600);
   if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

   if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); 
  display.begin();
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Air Purifier Project");
  display.println("Danny Han");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("AQ TESTER");
  display.display();
  delay(3000);
}

void loop() {
  display.setCursor(0,0);
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
   
  }
  ccs.readData();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Air Purifier Tester");
  display.print("Humidity = ");
  display.print(bme.humidity);
  display.println(" %");
  display.print("VOC: "); 
  display.print(ccs.getTVOC()); 
  display.println(" ppb");
  display.print("CO2: ");
  display.print(ccs.geteCO2());
  display.println(" ppm");
  display.display();
  
  Serial.print("Humidity = "); 
  Serial.print(bme.humidity); 
  Serial.println(" %");
  Serial.print("VOC = "); 
  Serial.print(ccs.getTVOC()); 
  Serial.println(" ppb");
  Serial.print("CO2: ");
  Serial.print(ccs.geteCO2());
  Serial.println(" ppm");

  
  delay(1000);
  
  

}
