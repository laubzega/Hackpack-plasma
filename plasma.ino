#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "math.h"

#define PIN 1
#define TODISPLAY(x) ((x) + 1) * 120

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(30);
}

int w = matrix.width();
int h = matrix.height();
int time = 0;
double r, g, b;


void loop() {
  matrix.fillScreen(0);
 
  for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
    {
      double cx = x / (double) 16 + 0.5 * sin(time / 10.);
      double cy = y / (double) 16 + 0.5 * cos(time / 6.);
      double v = sin(sqrt(100 * (cx*cx+cy*cy) + 1) + time / 2.);

      switch(time / 300)
      {
        case 0:
          r = 1;
          g = cos(v * PI);
          b = sin(v * PI);
          break;
          
        case 1:
          r = sin(v * PI);
          g = cos(v * PI);
          b = 0;
          break;
          
        case 2:
          r = sin(v * PI);
          g = sin(v * PI + 2 * PI / 3);
          b = sin(v * PI + 4 * PI / 3);
          break;
          
        case 4:
          time = 0;  // note no break

        case 3:
          r = g = b = sin(v * .75 * PI);
          break;
      }

      r = TODISPLAY(r);
      g = TODISPLAY(g);
      b = TODISPLAY(b);
      
      matrix.setPixelColor(x + y * 8, r, g, b);
    }
    
  matrix.show();
  delay(20);

  time++;
}
