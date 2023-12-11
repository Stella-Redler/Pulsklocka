/*
  Fil: Pulsklockan
  Namn: Stella Redler
  Datum: 2023-10-09
  Beskrivning: Detta program visar en persons puls per minut på en Oled skärm, och updaterar den varje sekund, för att få en så exakt puls som möjligt.
*/

/*Inkluderar alla bibliotek och definierar oled skärmen*/
#include <PulseSensorPlayground.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

/* Initierar OLED-skärmen */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Initierar pulssensorn */
const int PulseWire = 0;
int Threshold = 50;
int PulseSensor = 0;
const int inputPin = 0;

PulseSensorPlayground pulseSensor;

/*Definierar en logotyp i minnet*/
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

void setup() {
  Serial.begin(9600); // Skriver ut värdena i seriell monitor
  pulseSensor.analogInput(PulseWire); // Ange vilken pinne pulssensorn är ansluten till
  pulseSensor.setThreshold(Threshold); // Ange tröskelvärdet för pulssensorn
  pinMode(inputPin, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed")); // Skriv ut felmeddelande om OLED-skärmen inte kan initialiseras
    for (;;); // Stanna koden här om OLED-skärmen inte kan initialiseras korrekt
  }

  /* Visar det initiala innehållet i displaybufferten på skärmen - biblioteket initialiserar detta med en Adafruit-splashskärm*/
  display.display();
  delay(2000); // Väntar i 2 sekunder

  /*Rensar displaybufferten*/
  display.clearDisplay();

  /* Rita en enskild pixel i vitt*/
  display.drawPixel(10, 10, WHITE);

  /* Visar displaybufferten på skärmen*/
  display.display();
  delay(2000);
}

void loop() {
  int sensorValue = analogRead(inputPin); // Läser av sensorns värde från analoga pin 0
  display.clearDisplay(); // Rensar displayen
  /*Bestämmer hur texten som skrivs ut på skärmen kommer se ut*/
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  /*Skriver ut texten "Heartbeat: " och ger ut värderna som kommer in från pulssensorn dividerat med 10, för att få ett rimligt värde*/
  display.print("Heartbeat: ");
  display.println(sensorValue/10);
  display.display(); 
  delay(1000); // Vänta i 1 sekund innan nästa uppdatering
}
