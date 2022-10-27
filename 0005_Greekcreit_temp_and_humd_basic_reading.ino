/*********
  0005 Greekcreit basic temp and humid readings
  
  Created by Andy Shrimpton

I COULD NOT UNDERSTAND THE FILES ON THE BANGGOOD WEBSITE THAT I DOWNLOADED. i AM NEW TO ALL OF THIS. BUT AFTER TWO DAYS I FOUND OUT THE I HAD TO ADJUST THE SCL AND SDA PINS FOR THE OLED TO WORK

THEN I FOUND THAT TO SUPPLIED DHT11 WAS NOT WORKING WHICH ALSO WASTED A BIT OF TIME
  
 THIS CODE IS TO BE USED WITH THE ARDUINO IDE OR SOMETHING COMPATIBLE TOO
 
 WARNING - we are using the https://au.banggood.com/Geekcreit-ESP8266-IoT-Development-Board-DHT11-Temperature-and-Humidity-Yellow-Blue-OLED-Display-SDK-Programming-Wifi-Module-p-1471313.html?cur_warehouse=CN
 
 BECAREFULL - check if you use another make of OLED that the pins are the same.
 
 As the board has STRANGE SDL AND SCL PINS WE HAVE TO CHANGE THEM IN THE CODE BELOW
 
 *** WARNING ***  Some OLED have the positive and Negative reveresed THE SUPPLIED ONE IS FINE FROM LEFT TO RIGHT VCC, GND, SCL, SDA *** WARNING *** 
 * 
*********/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>                                  // look for Adafruit_Unified_Sensor
#include <DHT.h>

#define SCREEN_WIDTH 128                                      // OLED display width, in pixels
#define SCREEN_HEIGHT 64                                      // OLED display height, in pixels

int setTextSize1=1;                                           //set fontsize to 1
int setTextSize2=2;                                           // set font size to 2
int delay1=1000;                                              // delay for 1 second
int delay2=2000;                                              // delay for 2 seconds


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);           // wire -1 as the oled has no reset pin

#define DHTPIN 5                                               // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11                                      // DHT 11 - Normally blue in colour
//#define DHTTYPE    DHT22                                    // DHT 22 (AM2302) Normally white
//#define DHTTYPE    DHT21                                   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);                                     //Set up the DHT sensor

void setup() {                                              // HERE WE PUT THINGS THAT ONLY HAPPEN ONCE
  
  Serial.begin(9600);                                       // set the serial monitor baud rate
  
                                                            //  ***** IMPORTANT TO MAKE SURE THIS LINE IS ADDED TO MAKE THIS GEEKCREIT BOARD OLED WORK
  Wire.begin(2,14);                                         //scl gpio14  SDA gpio 02 here we change where the SDA and SCL pins look to get there data

  dht.begin();                                              // start the temp and humid sensor

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  //display.display();                                          // comment out this line to NOT dispaly the Arafruit Logo
  //delay(delay2);                                              // WAIT TWO SECONDS
  display.clearDisplay();
  
                                          
  display.setTextColor(WHITE);
 
}                                                             // end of void setup

void loop() {                                                 // WHERE WE PUT CODE THAT WILL CONTINUE TO LOOP AROUND AS LONG AS THE BOARD HAS POWER
  
  
  delay(delay1);                                              // UPDATE THE SCREEN ONCE PER SECOND 1000 = 1 SECOND DHT11 can be read every second the DHT22 is every 2 seconds

  //read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");        //IF NO READING CAN BE FOUND PRINT THE THE SERIAL MONITOR YOU WILL ALSO GET "nan" ON THE OLED
 
  }
  
  // clear display
  display.clearDisplay();                                   //WE NEED TO CLEAR THE DISPLAY OTHERWISE THE NEW VALUES WILL OVERWRITE THE OLD ONES
  
  
  // display temperature
  display.setTextSize(setTextSize1);                        //SMALL TEXT SIZE SELECTED
  display.setCursor(0,0);
  display.print(" Temp & Humid Sensor");                    // THIS IS IN ORANGE AS IT IN THE VERY TOP PART OF THE OLED WHICH HAS THIS COLOUR THAT CANT BE CHANGED
  display.setTextSize(setTextSize2);                        // LARGER TEXT SELECTED
  display.setCursor(0,16);                                  //POSITION WHERE TO SHOW THE TEXT X=0 (ACOSS) Y=16 (DOWN)
  display.print("T: ");
  display.print(t);                                         //PRINT THE VALUE STORED IN THE VARIABLE "t"
  display.print(" ");
  display.setTextSize(setTextSize1);
  display.cp437(true);                                      //SELECT A NEW FONT TYPE TO PRINT THE VERY SMALL "o" INFRONT OF THE "C"
  display.write(167);                                       //PRINT THE VERY SMALL "O"
  display.setTextSize(setTextSize2);
  display.print("C");
  
  // display humidity
  display.setTextSize(setTextSize2);
  display.setCursor(0, 37);
  display.print("H: ");
  display.print(h);                                         //PRINT THE VALUE STORED IN THE VARIABLE "h"
  display.print(" %"); 

//  debug if screen not working                             // COMMENT OUT ALL THE "Serial.print....." lines will prevent data going to the serial monitor
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print ("   Humid:  ");
  Serial.print(h);
  Serial.println(" ");
  
  display.display();                                        // THIS LINE IS REQUIRED TO REFRESH THE OLED
}
