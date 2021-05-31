#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LEDPIN 27
#define NUMPIXELS 32

const int SWITCH1PIN = 5;
const int SWITCH2PIN = 35;
const int SWITCH3PIN = 34;
const int SWITCH4PIN = 4;
const int TOPBTNPIN = 15;

void rainbow(int);
void rainbowchaseExit();
void colorWipe();
void changeColor(uint32_t);
void todoChecked(int);
void theaterChase(uint32_t, int);

bool switch1 = false;
bool switch2 = false;
bool switch3 = false;
bool switch4 = false;
bool alldone = false;

Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// Colour of individual sides
const uint32_t side_colors[] = { 
  strip.Color(255, 0, 0),   // red
  strip.Color(0, 255, 0),   // green
  strip.Color(0, 0, 255),   // blue
  strip.Color(255, 0, 255)  // turqouise
};

void setup() {
  pinMode(SWITCH1PIN, INPUT);
  pinMode(SWITCH2PIN, INPUT);
  pinMode(SWITCH3PIN, INPUT);
  pinMode(SWITCH4PIN, INPUT);

  strip.begin();            // INITIALIZE strip object
  strip.show();             // Turn OFF all pixels
  strip.setBrightness(50);  // Set BRIGHTNESS (max = 255)
  strip.clear();            // Set all pixel colors to 'off'

  Serial.begin(9600);
}

void loop() {
  
  if (digitalRead(SWITCH1PIN) != switch1) {
    switch1 = !switch1;
    todoChecked(1);
  }

  if (digitalRead(SWITCH2PIN) != switch2) {
    switch2 = !switch2;
    todoChecked(2);
  }

  if (digitalRead(SWITCH3PIN) != switch3) {
    switch3 = !switch3;
    todoChecked(3);
  }

  if (digitalRead(SWITCH4PIN) != switch4) {
    switch4 = !switch4;
    todoChecked(4);
  }

  if (digitalRead(TOPBTNPIN)){
    strip.clear();
    for(int s=0; s < 4; s++){
      for(int i=s*8; i<8*(s+1); i++) {
        strip.setPixelColor(i, side_colors[s]);
      }
    }
    strip.show();
    delay(5000);
  }

  if ((switch1 == switch2) && (switch2 == switch3) && (switch3 == switch4) && alldone){
    alldone = false;

    for(int a=0; a<5; a++) {
      for(int b=0; b<2; b++) {
        strip.clear();
        for(int c=b; c<strip.numPixels(); c += 3) {
          strip.setPixelColor(c, strip.Color(0, 200, 100));
        }
        strip.show();
        delay(500);
      }
    }
  }
  
  strip.clear();
  strip.show();

}

// show color at selected side
void todoChecked(int side) {
  alldone = true;

  // Single Color
  // strip.clear();
  // for(int i=(side-1)*8; i<8*side; i++) {
  //   strip.setPixelColor(i, strip.Color(50,0,200));
  //   strip.show();
  // }

  // Theater chase
  // for(int a=0; a<5; a++) {
  // strip.clear();
  //   for(int i=(side-1)*8; i<8*side; i++) { 
  //     strip.setPixelColor(i, strip.Color(50,0,200));
  //     strip.show();
  //     delay(70);
  //   }
  // }

  // Regenbogen
  strip.clear();
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 1028) {
    for(int  i=(side-1)*8; i<8*side; i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / 8);
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(10); 
  }

}