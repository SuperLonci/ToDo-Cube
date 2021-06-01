#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LEDPIN 27
#define NUMPIXELS 32

const int SWITCH1PIN = 5;
const int SWITCH2PIN = 35;
const int SWITCH3PIN = 34;
const int SWITCH4PIN = 4;
const int TOPBTNPIN = 15;

void todoChecked(int);
void setlayercolor(int layer, int brightness);
void bootupanimation();
void colorbuttonanimation();
void successanimation();

bool switch1 = false;
bool switch2 = false;
bool switch3 = false;
bool switch4 = false;
bool alldone = false;

Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

const int rotpos[] = {2,1,0,0,1,2,3,3,6,5,4,4,5,6,7,7,10,9,8,8,9,10,11,11,14,13,12,12,13,14,15,15};

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

  bootupanimation();
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
    colorbuttonanimation();
  }

  if ((switch1 == switch2) && (switch2 == switch3) && (switch3 == switch4) && alldone){
    alldone = false;
    successanimation();
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

void setlayercolor(int layer, int brightness)
{
    switch (layer)
    {
        case 0:
        {
            strip.setPixelColor(0, strip.Color(brightness, 0, 0));
            strip.setPixelColor(1, strip.Color(brightness, 0, 0));
            strip.setPixelColor(8, strip.Color(0, brightness, 0));
            strip.setPixelColor(9, strip.Color(0, brightness, 0));
            strip.setPixelColor(16, strip.Color(0, 0, brightness));
            strip.setPixelColor(17, strip.Color(0, 0, brightness));
            strip.setPixelColor(24, strip.Color(brightness, 0, brightness));
            strip.setPixelColor(25, strip.Color(brightness, 0, brightness));
            break;
        }
        case 1:
        {
            strip.setPixelColor(2, strip.Color(brightness, 0, 0));
            strip.setPixelColor(7, strip.Color(brightness, 0, 0));
            strip.setPixelColor(10, strip.Color(0, brightness, 0));
            strip.setPixelColor(15, strip.Color(0, brightness, 0));
            strip.setPixelColor(18, strip.Color(0, 0, brightness));
            strip.setPixelColor(23, strip.Color(0, 0, brightness));
            strip.setPixelColor(26, strip.Color(brightness, 0, brightness));
            strip.setPixelColor(31, strip.Color(brightness, 0, brightness));
            break;
        }
        case 2:
        {
            strip.setPixelColor(3, strip.Color(brightness, 0, 0));
            strip.setPixelColor(6, strip.Color(brightness, 0, 0));
            strip.setPixelColor(11, strip.Color(0, brightness, 0));
            strip.setPixelColor(14, strip.Color(0, brightness, 0));
            strip.setPixelColor(19, strip.Color(0, 0, brightness));
            strip.setPixelColor(22, strip.Color(0, 0, brightness));
            strip.setPixelColor(27, strip.Color(brightness, 0, brightness));
            strip.setPixelColor(30, strip.Color(brightness, 0, brightness));
            break;
        }
        case 3:
        {
            strip.setPixelColor(4, strip.Color(brightness, 0, 0));
            strip.setPixelColor(5, strip.Color(brightness, 0, 0));
            strip.setPixelColor(12, strip.Color(0, brightness, 0));
            strip.setPixelColor(13, strip.Color(0, brightness, 0));
            strip.setPixelColor(20, strip.Color(0, 0, brightness));
            strip.setPixelColor(21, strip.Color(0, 0, brightness));
            strip.setPixelColor(28, strip.Color(brightness, 0, brightness));
            strip.setPixelColor(29, strip.Color(brightness, 0, brightness));
            break;
        }
    }
}

void bootupanimation() {
  strip.clear();
  strip.show();
  for (int i = 0; i < 4; ++i)
  {
      for (int j = 0; j < 17; ++j)
      {
          setlayercolor(i, j * 255 / 17);
          strip.show();
          delay(40);
      }
  }
  for (int i = 0; i < 8; ++i)
  {
      for (int j = 17 - 1; j >= 0; --j)
      {
          strip.setPixelColor((i + 1) % 8, strip.Color(j * 255 / 17, 0, 0));
          strip.setPixelColor((i + 1) % 8 + 8, strip.Color(0, j * 255 / 17, 0));
          strip.setPixelColor((i + 1) % 8 + 16, strip.Color(0, 0, j * 255 / 17));
          strip.setPixelColor((i + 1) % 8 + 24, strip.Color(j * 255 / 17, 0, j * 255 / 17));
          strip.show();
          delay(5);
      }
  }
  delay(1000);
}

void colorbuttonanimation() {
  for (int i = 4 - 1; i >= 0; --i)
  {
      for (int j = 0; j < 17; ++j)
      {
          setlayercolor(i, j * 255 / 17);
          strip.show();
          delay(5);
      }
  }
  delay(500);
  for (int i = 0; i < 4; ++i)
  {
      for (int j = 17 - 1; j >= 0; --j)
      {
          setlayercolor(i, j * 255 / 17);
          strip.show();
          delay(5);
      }
  }
}

void successanimation() {
  // Rainbow circle
  for(int i = 0; i < 40; ++i)
  {
      for (int j = 0; j < 32; ++j)
      {
          strip.setPixelColor(j, strip.ColorHSV((i * 5000 + (j % 8 * (65535 / 8))) % 65535));
      }
      strip.show();
      delay(50);
  }

  // Yellow blinks
  for (int i = 0; i < 10; ++i)
  {
      for (int j = 0; j < 32; ++j)
      {
          strip.setPixelColor(j, strip.Color(i % 2 * 255, i % 2 * 255, 0));
      }
      strip.show();
      delay(100);
  }

  // Rainbow around
  for (int i = 0; i < 40; ++i)
  {
      for (int j = 0; j < 32; ++j)
      {
          strip.setPixelColor(j, strip.ColorHSV((i * 3000 + (rotpos[j] * (65535 / 16))) % 65535));
      }
      strip.show();
      delay(50);
  }

  // Line Around
  for (int i = 0; i < 40; ++i)
  {
      strip.clear();
      for (int j = 0; j < 32; ++j)
      {
          int rotindex = i % 16 + 16;
          if (rotpos[j] + 16 - rotindex == 0)
              strip.setPixelColor(j, strip.Color(0, 255, 0));
          if (rotpos[j] + 16 - rotindex == 1 || rotpos[j] + 16 - rotindex == -1)
              strip.setPixelColor(j, strip.Color(0, 127, 0));
      }
      strip.show();
      delay(50);
  }

  for (int i = 0; i < 100; ++i)
  {
      for (int j = 0; j < 32; ++j)
      {
          strip.setPixelColor(j, strip.ColorHSV((i * 3000) % 65535, 255, 255 - i * 255 / 100));
      }
      strip.show();
      delay(50);
  }
}