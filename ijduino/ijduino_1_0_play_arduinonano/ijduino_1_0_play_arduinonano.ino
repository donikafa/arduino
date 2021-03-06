/*                            IJduino 1.0
Requires:
 * 8X8 LED grid MAX7219
 * Mini Breadboard
 * Atmega328
 * Button
 * 2 Wires
 * 4.5 Volt
 (c) IJhack 2014 GNU GPL
http://ijhack.org/
 */
#include "LedControl.h"

#define	MAX_DEVICES	1
#define	CLK_PIN		10  // or SCK
#define	CS_PIN		11  // or SS
#define	DATA_PIN	12  // or MOSI

/* using VCC, GND, DIN 21, CS 21, CLK 5 for the MAX7219 */
// Create a new LedControl for 1 device...
LedControl lc = LedControl(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

//int lowPin = 11;           /* ground pin for the buton ;-) */
int buttonPin = 13;          /* choose the input pin for the pushbutton */

int animations = 19;         /* the number of animations we have */
int lastButtonState = LOW;   /* the previous reading from the input pin */
int anicount = 0;            /* Set animationcounter to zero */
int buttonState = LOW;       /* Set buttonstate to low */
int brightness = 3;          /* Set brightneslevel to 5 (0 to 15 valid */
int lastDebounceTime = 0;   /* the last time the output pin was toggled */
int debounceDelay = 50;     /* the debounce time; increase if the output flickers */

void setup() {
  /*
     The MAX72XX is in power-saving mode on startup,
     we have to do a wakeup call
   */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  /*
  * Set the brightness of the display.
  * Params:
  * int addr      the address of the display to control
  * int intensity the brightness of the display.
  *               Only values between 0(darkest) and 15(brightest) are valid.
  */
  lc.setIntensity(0, brightness);
  /*
   * Switch all Leds on the display off.
   * Params:
   * int addr The address of the display to control
   */
  lc.clearDisplay(0);
  /* setup pins */
  //pinMode(buttonPin, INPUT_PULLUP);
  //pinMode(lowPin, OUTPUT);
  //digitalWrite(lowPin, LOW);
}
void loop() {
  switch (anicount) {
    case 0:
      ijhacklogo();
      break;
    case 1:
      ghost();
      break;
    case 2:
      invade();
      break;
    case 3:
      heart();
      break;
    case 4:
      invadesquid();
      break;
    case 5:
      jumper();
      break;
    case 6:
      ijlogowink();
      break;
    case 7:
      heartbeat();
      break;
    case 8:
      eq();
      break;
    case 9:
      invaderagain();
      break;
    case 10:
      pong();
      break;
    case 11:
      snake();
      break;
    case 12:
      arrows();
      break;
    case 13:
      directions();
      break;
    case 14:
      packman();
      break;
    case 15:
      diagonals();
      break;
    case 16:
      waterdrip();
      break;
    case 17:
      aliens();
      break;
    case 18:
      blockanim();
      break;
    case 19:
      pulse();
      break;
    case 20:
      screenclear();
      break;

  }
}
bool render(byte* animation, int delaytime) {
  lc.setColumn(0, 0, animation[7]);
  lc.setColumn(0, 1, animation[6]);
  lc.setColumn(0, 2, animation[5]);
  lc.setColumn(0, 3, animation[4]);
  lc.setColumn(0, 4, animation[3]);
  lc.setColumn(0, 5, animation[2]);
  lc.setColumn(0, 6, animation[1]);
  lc.setColumn(0, 7, animation[0]);

  long startTime = millis();
  while ((startTime + delaytime) > millis()) {

    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonPin);

    // check to see if you just pressed the button
    // (i.e. the input went from HIGH to LOW),  and you've waited
    // long enough since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading != buttonState) {
        buttonState = reading;

        // only toggle the animation if the new button state is HIGH
        if (buttonState == LOW) {
          anicount++;
          if (anicount > animations) {
            anicount = 0;
          }
          return true;
        }
      }
    }

    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState = reading;
  }
  return false;  /* don't skip the rest */
}

void screenclear() {
  lc.clearDisplay(0);
}

void invade() {
  byte invade[8] = {
    B00100100,
    B00100100,
    B01111110,
    B11011011,
    B11111111,
    B11111111,
    B10100101,
    B00100100
  };

  byte devade[8] = {
    B00100100,
    B10100101,
    B11111111,
    B11011011,
    B11111111,
    B01111110,
    B00100100,
    B00100100
  };

  bool skip = render(invade, 500);
  if (skip) {
    return;
  }
  render(devade, 500);
}

void invadesquid() {
  byte invadesquid[8] = {
    B00011000,
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B01011010,
    B10000001,
    B01000010
  };

  byte devadesquid[8] = {
    B00011000,
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B10100101
  };

  bool skip = render(invadesquid, 500);
  if (skip) {
    return;
  }
  render(devadesquid, 500);
}

void ghost() {

  byte ghost1[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte ghost2[8] = {
    B00000000,
    B00000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000
  };

  byte ghost3[8] = {
    B00000000,
    B10000000,
    B11000000,
    B01000000,
    B11000000,
    B11000000,
    B11000000,
    B01000000
  };

  byte ghost4[8] = {
    B10000000,
    B11000000,
    B01100000,
    B00100000,
    B11100000,
    B01100000,
    B11100000,
    B00100000
  };

  byte ghost5[8] = {
    B11000000,
    B11100000,
    B10110000,
    B10010000,
    B11110000,
    B00110000,
    B11110000,
    B01010000
  };

  byte ghost6[8] = {
    B11100000,
    B11110000,
    B01011000,
    B01001000,
    B11111000,
    B00011000,
    B11111000,
    B10101000
  };

  byte ghost7[8] = {
    B01110000,
    B11111000,
    B10101100,
    B00100100,
    B11111100,
    B10001100,
    B11111100,
    B01010100
  };

  byte ghost8[8] = {
    B00111000,
    B01111100,
    B11010110,
    B10010010,
    B11111110,
    B11000110,
    B11111110,
    B10101010
  };

  byte ghost9[8] = {
    B00011100,
    B00111110,
    B01101011,
    B01001001,
    B01111111,
    B01100011,
    B01111111,
    B01010101
  };

  byte ghost9a[8] = {
    B00011100,
    B00111110,
    B01101101,
    B01001001,
    B01111111,
    B01100011,
    B01111111,
    B01010101
  };

  byte ghost9b[8] = {
    B00011100,
    B00111110,
    B01011011,
    B01001001,
    B01111111,
    B01100011,
    B01111111,
    B01010101
  };

  byte ghost9c[8] = {
    B00011100,
    B00111110,
    B01001001,
    B01011011,
    B01111111,
    B01100011,
    B01111111,
    B01010101
  };

  byte ghost9d[8] = {
    B00011100,
    B00111110,
    B01001001,
    B01101101,
    B01111111,
    B01100011,
    B01111111,
    B01010101
  };

  byte ghost9e[8] = {
    B00011100,
    B00111110,
    B01101101,
    B01001001,
    B01111111,
    B01100011,
    B01111111,
    B01010101
  };

  byte ghost10[8] = {
    B00001110,
    B00011111,
    B00110101,
    B00100100,
    B00111111,
    B00110001,
    B00111111,
    B00101010
  };

  byte ghost11[8] = {
    B00000111,
    B00001111,
    B00011010,
    B00010010,
    B00011111,
    B00011000,
    B00011111,
    B00010101
  };

  byte ghost12[8] = {
    B00000011,
    B00000111,
    B00001101,
    B00001001,
    B00001111,
    B00001100,
    B00001111,
    B00001010
  };

  byte ghost13[8] = {
    B00000001,
    B00000011,
    B00000110,
    B00000100,
    B00000111,
    B00000110,
    B00000111,
    B00000101
  };

  byte ghost14[8] = {
    B00000000,
    B00000001,
    B00000011,
    B00000010,
    B00000011,
    B00000011,
    B00000011,
    B00000010
  };

  byte ghost15[8] = {
    B00000000,
    B00000000,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001
  };


  byte ghost16[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  bool skip;
  skip = render(ghost1, 200);
  if (skip) {
    return;
  }
  skip = render(ghost2, 200);
  if (skip) {
    return;
  }
  skip = render(ghost3, 200);
  if (skip) {
    return;
  }
  skip = render(ghost4, 200);
  if (skip) {
    return;
  }
  skip = render(ghost5, 200);
  if (skip) {
    return;
  }
  skip = render(ghost6, 200);
  if (skip) {
    return;
  }
  skip = render(ghost7, 200);
  if (skip) {
    return;
  }
  skip = render(ghost8, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9a, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9b, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9c, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9d, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9e, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9a, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9b, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9c, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9d, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9e, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9a, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9b, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9c, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9d, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9e, 200);
  if (skip) {
    return;
  }
  skip = render(ghost9, 200);
  if (skip) {
    return;
  }
  skip = render(ghost10, 200);
  if (skip) {
    return;
  }
  skip = render(ghost11, 200);
  if (skip) {
    return;
  }
  skip = render(ghost12, 200);
  if (skip) {
    return;
  }
  skip = render(ghost13, 200);
  if (skip) {
    return;
  }
  skip = render(ghost14, 200);
  if (skip) {
    return;
  }
  skip = render(ghost15, 200);
  if (skip) {
    return;
  }
  render(ghost16, 200);
}

void ijlogowink() {
  byte logowink0[8] = {
    B11000011,
    B11000011,
    B00000000,
    B00000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  };

  byte logowink1[8] = {
    B00000011,
    B00000011,
    B00000000,
    B00000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  };

  byte logowink2[8] = {
    B11000000,
    B11000000,
    B00000000,
    B00000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  };

  byte logowink3[8] = {
    B11000011,
    B11000011,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  bool skip;
  skip = render(logowink0, 500);
  if (skip) {
    return;
  }
  skip = render(logowink1, 500);
  if (skip) {
    return;
  }
  skip = render(logowink0, 500);
  if (skip) {
    return;
  }
  skip = render(logowink2, 500);
  if (skip) {
    return;
  }
  skip = render(logowink0, 500);
  if (skip) {
    return;
  }
  skip = render(logowink3, 500);
}
void ijhacklogo() {
  /* here is the data for the characters */
  byte ij[8] = {
    B11000011,
    B11000011,
    B00000000,
    B00000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  };

  byte h[8] = {
    B11000011,
    B11000011,
    B11000011,
    B11111111,
    B11111111,
    B11000011,
    B11000011,
    B11000011
  };

  byte a[8] = {
    B00011000,
    B00111100,
    B01100110,
    B11000011,
    B11111111,
    B11111111,
    B11000011,
    B11000011
  };

  byte c[8] = {
    B01111110,
    B11111111,
    B11000011,
    B11000000,
    B11000000,
    B11000011,
    B11111111,
    B01111110
  };

  byte k[8] = {
    B11000111,
    B11011110,
    B11111100,
    B11110000,
    B11110000,
    B11111100,
    B11011110,
    B11000111
  };

  bool skip;
  skip = render(ij, 500);
  if (skip) {
    return;
  }
  skip = render(h, 500);
  if (skip) {
    return;
  }
  skip = render(a, 500);
  if (skip) {
    return;
  }
  skip = render(c, 500);
  if (skip) {
    return;
  }
  render(k, 500);
}

void heart() {

  /* here is the data for the characters */
  byte heart2[8] = {
    B00000000,
    B01100110,
    B10011001,
    B10000001,
    B10000001,
    B01000010,
    B00100100,
    B00011000
  };

  /* here is the data for the characters */
  byte heart1[8] = {
    B00000000,
    B01100110,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00011000
  };

  bool skip = render(heart1, 500);
  if (skip) {
    return;
  }
  render(heart2, 500);
}

void jumper() {
  byte jumpdown[8] = {
    B00111100,
    B00111100,
    B00011000,
    B01111110,
    B00011000,
    B00011000,
    B00100100,
    B00100100
  };

  byte jumpup[8] = {
    B00111100,
    B01011010,
    B00111100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B00000000
  };

  bool skip = render(jumpdown, 500);
  if (skip) {
    return;
  }
  render(jumpup, 500);
}

void heartbeat() {
  byte heart1[8] = {
    B00000000,
    B00000100,
    B00000110,
    B00000101,
    B11100100,
    B00010100,
    B00001100,
    B00000100
  };

  byte heart2[8] = {
    B00000000,
    B00000010,
    B00000011,
    B00000010,
    B11110010,
    B00001010,
    B00000110,
    B00000010
  };

  byte heart3[8] = {
    B00000000,
    B00000001,
    B00000001,
    B00000001,
    B11111001,
    B00000101,
    B00000011,
    B00000001
  };

  byte heart4[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111100,
    B00000010,
    B00000001,
    B00000000
  };

  byte heart5[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111110,
    B00000001,
    B00000000,
    B00000000
  };

  byte heart6[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B00000000,
    B00000000,
    B00000000
  };

  byte heart7[8] = {
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B01111111,
    B00000000,
    B00000000,
    B00000000
  };

  byte heart8[8] = {
    B00000000,
    B00000000,
    B10000000,
    B01000000,
    B00111111,
    B00000000,
    B00000000,
    B00000000
  };

  byte heart9[8] = {
    B00000000,
    B10000000,
    B11000000,
    B10100000,
    B10011111,
    B10000000,
    B10000000,
    B10000000
  };

  byte heart10[8] = {
    B00000000,
    B01000000,
    B01100000,
    B01010000,
    B01001111,
    B01000000,
    B11000000,
    B01000000
  };

  byte heart11[8] = {
    B00000000,
    B00100000,
    B00110000,
    B00101000,
    B00100111,
    B10100000,
    B01100000,
    B00100000
  };

  byte heart12[8] = {
    B00000000,
    B00010000,
    B00011000,
    B00010100,
    B10010011,
    B01010000,
    B00110000,
    B00010000
  };

  byte heart13[8] = {
    B00000000,
    B00001000,
    B00001100,
    B00001010,
    B11001001,
    B00101000,
    B00011000,
    B00001000
  };

  bool skip;
  skip = render(heart6, 100);
  if (skip) {
    return;
  }
  skip = render(heart6, 100);
  if (skip) {
    return;
  }
  skip = render(heart7, 100);
  if (skip) {
    return;
  }
  skip = render(heart8, 100);
  if (skip) {
    return;
  }
  skip = render(heart9, 100);
  if (skip) {
    return;
  }
  skip = render(heart10, 100);
  if (skip) {
    return;
  }
  skip = render(heart11, 100);
  if (skip) {
    return;
  }
  skip = render(heart12, 100);
  if (skip) {
    return;
  }
  skip = render(heart13, 100);
  if (skip) {
    return;
  }
  skip = render(heart1, 100);
  if (skip) {
    return;
  }
  skip = render(heart2, 100);
  if (skip) {
    return;
  }
  skip = render(heart3, 100);
  if (skip) {
    return;
  }
  skip = render(heart4, 100);
  if (skip) {
    return;
  }
  skip = render(heart5, 100);
  if (skip) {
    return;
  }
  render(heart6, 100);
}

void eq() {
  byte eq1[8] = {
    B00000000,
    B00001100,
    B11001100,
    B11001100,
    B11111100,
    B11111100,
    B11111111,
    B11111111
  };

  byte eq2[8] = {
    B00000000,
    B00001100,
    B11001100,
    B11001100,
    B11111100,
    B11111100,
    B11111111,
    B11111111
  };

  byte eq3[8] = {
    B00000000,
    B00001100,
    B11001100,
    B11001100,
    B11111100,
    B11111100,
    B11111111,
    B11111111
  };

  byte eq4[8] = {
    B00000000,
    B00000000,
    B00001100,
    B11001100,
    B11001100,
    B11111111,
    B11111111,
    B11111111
  };

  byte eq5[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00001100,
    B11001111,
    B11001111,
    B11111111,
    B11111111
  };

  byte eq6[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000011,
    B00001111,
    B11001111,
    B11001111,
    B11111111
  };

  byte eq7[8] = {
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00001111,
    B00001111,
    B11001111,
    B11001111
  };

  byte eq8[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00001111,
    B00001111,
    B11111111
  };

  byte eq9[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00111111,
    B11111111
  };

  byte eq10[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00111111,
    B11111111
  };

  byte eq11[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000011,
    B00001111,
    B11001111,
    B11111111
  };

  byte eq12[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001100,
    B11001111,
    B11111111,
    B11111111
  };

  byte eq13[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00001100,
    B11001100,
    B11111111,
    B11111111,
    B11111111
  };

  byte eq14[8] = {
    B00000000,
    B00000000,
    B00001100,
    B11001100,
    B11001100,
    B11111111,
    B11111111,
    B11111111
  };

  byte eq15[8] = {
    B00000000,
    B00001100,
    B11001100,
    B11001100,
    B11001100,
    B11111100,
    B11111111,
    B11111111
  };

  bool skip;
  skip = render(eq1, 50);
  if (skip) {
    return;
  }
  skip = render(eq2, 50);
  if (skip) {
    return;
  }
  skip = render(eq3, 50);
  if (skip) {
    return;
  }
  skip = render(eq4, 50);
  if (skip) {
    return;
  }
  skip = render(eq5, 50);
  if (skip) {
    return;
  }
  skip = render(eq6, 50);
  if (skip) {
    return;
  }
  skip = render(eq7, 50);
  if (skip) {
    return;
  }
  skip = render(eq8, 50);
  if (skip) {
    return;
  }
  skip = render(eq9, 50);
  if (skip) {
    return;
  }
  skip = render(eq10, 50);
  if (skip) {
    return;
  }
  skip = render(eq11, 50);
  if (skip) {
    return;
  }
  skip = render(eq12, 50);
  if (skip) {
    return;
  }
  skip = render(eq13, 50);
  if (skip) {
    return;
  }
  skip = render(eq14, 50);
  if (skip) {
    return;
  }
  render(eq15, 50);
}



void invaderagain() {
  byte invader1[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte invader2[8] = {
    B00000000,
    B00000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000
  };

  byte invader3[8] = {
    B00000000,
    B10000000,
    B11000000,
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B11000000
  };

  byte invader4[8] = {
    B10000000,
    B11000000,
    B01100000,
    B11100000,
    B10100000,
    B00100000,
    B00100000,
    B01100000
  };

  byte invader5[8] = {
    B01000000,
    B11100000,
    B10110000,
    B11110000,
    B01010000,
    B10010000,
    B00010000,
    B00110000
  };

  byte invader6[8] = {
    B00100000,
    B11110000,
    B11011000,
    B11111000,
    B00101000,
    B11001000,
    B00001000,
    B00011000
  };

  byte invader7[8] = {
    B10010000,
    B11111000,
    B01101100,
    B11111100,
    B10010100,
    B01100100,
    B00000100,
    B00001100
  };

  byte invader8[8] = {
    B01001000,
    B11111100,
    B10110110,
    B11111110,
    B01001010,
    B00110010,
    B00000010,
    B10000110
  };

  byte invader9[8] = {
    B00100100,
    B01111110,
    B11011011,
    B11111111,
    B10100101,
    B10011001,
    B10000001,
    B11000011
  };

  byte invader9a[8] = {
    B00100100,
    B00011000,
    B01111110,
    B11011011,
    B11111111,
    B11011011,
    B10011001,
    B11000011
  };

  byte invader10[8] = {
    B00010010,
    B00111111,
    B01101101,
    B01111111,
    B01010010,
    B01001100,
    B01000000,
    B01100001
  };


  byte invader11[8] = {
    B00001001,
    B00011111,
    B00110110,
    B00111111,
    B00101001,
    B00100110,
    B00100000,
    B00110000
  };



  byte invader12[8] = {
    B00000100,
    B00001111,
    B00011011,
    B00011111,
    B00010100,
    B00010011,
    B00010000,
    B00011000
  };

  byte invader13[8] = {
    B00000010,
    B00000111,
    B00001101,
    B00001111,
    B00001010,
    B00001001,
    B00001000,
    B00001100
  };


  byte invader14[8] = {
    B00000001,
    B00000011,
    B00000110,
    B00000111,
    B00000101,
    B00000100,
    B00000100,
    B00000110
  };

  byte invader15[8] = {
    B00000000,
    B00000001,
    B00000011,
    B00000011,
    B00000010,
    B00000010,
    B00000010,
    B00000011
  };

  byte invader16[8] = {
    B00000000,
    B00000000,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001
  };

  bool skip;
  skip = render(invader1, 200);
  if (skip) {
    return;
  }
  skip = render(invader2, 200);
  if (skip) {
    return;
  }
  skip = render(invader3, 200);
  if (skip) {
    return;
  }
  skip = render(invader4, 200);
  if (skip) {
    return;
  }
  skip = render(invader5, 200);
  if (skip) {
    return;
  }
  skip = render(invader6, 200);
  if (skip) {
    return;
  }
  skip = render(invader7, 200);
  if (skip) {
    return;
  }
  skip = render(invader8, 200);
  if (skip) {
    return;
  }
  skip = render(invader9, 200);
  if (skip) {
    return;
  }
  skip = render(invader9a, 200);
  if (skip) {
    return;
  }
  skip = render(invader9, 200);
  if (skip) {
    return;
  }
  skip = render(invader9a, 200);
  if (skip) {
    return;
  }
  skip = render(invader9, 200);
  if (skip) {
    return;
  }
  skip = render(invader9a, 200);
  if (skip) {
    return;
  }
  skip = render(invader9, 200);
  if (skip) {
    return;
  }
  skip = render(invader10, 200);
  if (skip) {
    return;
  }
  skip = render(invader11, 200);
  if (skip) {
    return;
  }
  skip = render(invader12, 200);
  if (skip) {
    return;
  }
  skip = render(invader13, 200);
  if (skip) {
    return;
  }
  skip = render(invader14, 200);
  if (skip) {
    return;
  }
  skip = render(invader15, 200);
  if (skip) {
    return;
  }
  skip = render(invader16, 200);
  if (skip) {
    return;
  }
  render(invader1, 200);
}


void pong() {
  byte pong1[8] = {
    B00111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011100
  };

  byte pong2[8] = {
    B00111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000000,
    B00001110
  };

  byte pong3[8] = {
    B00111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000010,
    B00000111
  };


  byte pong4[8] = {
    B00111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000100,
    B00000000,
    B00000111
  };

  byte pong5[8] = {
    B00111000,
    B00000000,
    B00000000,
    B00000000,
    B00001000,
    B00000000,
    B00000000,
    B00000111
  };

  byte pong6[8] = {
    B00111000,
    B00000000,
    B00000000,
    B00010000,
    B00000000,
    B00000000,
    B00000000,
    B00001110
  };

  byte pong7[8] = {
    B01110000,
    B00000000,
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001110
  };

  byte pong8[8] = {
    B11100000,
    B01000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011100
  };

  byte pong9[8] = {
    B11100000,
    B00000000,
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011100
  };

  byte pong10[8] = {
    B11100000,
    B00000000,
    B00000000,
    B00010000,
    B00000000,
    B00000000,
    B00000000,
    B00111000
  };

  byte pong11[8] = {
    B01110000,
    B00000000,
    B00000000,
    B00000000,
    B00001000,
    B00000000,
    B00000000,
    B01110000
  };

  byte pong12[8] = {
    B01110000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000100,
    B00000000,
    B00111000
  };

  byte pong13[8] = {
    B01110000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000010,
    B00011100
  };

  byte pong14[8] = {
    B00111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011101
  };

  bool skip;
  skip = render(pong1, 200);
  if (skip) {
    return;
  }
  skip = render(pong2, 200);
  if (skip) {
    return;
  }
  skip = render(pong3, 200);
  if (skip) {
    return;
  }
  skip = render(pong4, 200);
  if (skip) {
    return;
  }
  skip = render(pong5, 200);
  if (skip) {
    return;
  }
  skip = render(pong6, 200);
  if (skip) {
    return;
  }
  skip = render(pong7, 200);
  if (skip) {
    return;
  }
  skip = render(pong8, 200);
  if (skip) {
    return;
  }
  skip = render(pong9, 200);
  if (skip) {
    return;
  }
  skip = render(pong10, 200);
  if (skip) {
    return;
  }
  skip = render(pong11, 200);
  if (skip) {
    return;
  }
  skip = render(pong12, 200);
  if (skip) {
    return;
  }
  skip = render(pong13, 200);
  if (skip) {
    return;
  }
  skip = render(pong14, 200);
}


void snake() {
  byte snake1[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake2[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000000
  };

  byte snake3[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000011,
    B00000000
  };

  byte snake4[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000111,
    B00000000
  };

  byte snake5[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001110,
    B00000000
  };

  byte snake6[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011100,
    B00000000
  };

  byte snake7[8] = {
    B00000000,
    B00000000,
    B01000000,
    B00000000,
    B00000000,
    B00000000,
    B00111000,
    B00000000
  };

  byte snake8[8] = {
    B00000000,
    B00000000,
    B01000000,
    B00000000,
    B00000000,
    B00100000,
    B00110000,
    B00000000
  };

  byte snake9[8] = {
    B00000000,
    B00000000,
    B01000000,
    B00000000,
    B00100000,
    B00100000,
    B00100000,
    B00000000
  };

  byte snake10[8] = {
    B00000000,
    B00000000,
    B01000000,
    B00100000,
    B00100000,
    B00100000,
    B00000000,
    B00000000
  };

  byte snake11[8] = {
    B00000000,
    B00000000,
    B01100000,
    B00100000,
    B00100000,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake12[8] = {
    B00000000,
    B01000000,
    B01100000,
    B00100000,
    B00100000,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake13[8] = {
    B01000000,
    B01000000,
    B01100000,
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake14[8] = {
    B01100000,
    B01000000,
    B01100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake15[8] = {
    B01110000,
    B01000000,
    B01000000,
    B00000000,
    B00000100,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake16[8] = {
    B01111000,
    B01000000,
    B00000000,
    B00000000,
    B00000100,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake17[8] = {
    B01111100,
    B00000000,
    B00000000,
    B00000000,
    B00000100,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake18[8] = {
    B00111100,
    B00000100,
    B00000000,
    B00000000,
    B00000100,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake19[8] = {
    B00011100,
    B00000100,
    B00000100,
    B00000000,
    B00000100,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake20[8] = {
    B00001100,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000000,
    B00000000,
    B00000000
  };

  byte snake21[8] = {
    B00001100,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000000,
    B00000000
  };

  byte snake22[8] = {
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000000
  };

  byte snake23[8] = {
    B00000000,
    B00000100,
    B00000100,
    B00100100,
    B00000100,
    B00000100,
    B00001100,
    B00000000
  };

  byte snake24[8] = {
    B00000000,
    B00000000,
    B00000100,
    B00100100,
    B00000100,
    B00000100,
    B00011100,
    B00000000
  };

  byte snake25[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00100100,
    B00000100,
    B00010100,
    B00011100,
    B00000000
  };

  byte snake26[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00100000,
    B00010100,
    B00010100,
    B00011100,
    B00000000
  };

  byte snake27[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00100000,
    B00110000,
    B00010100,
    B00011100,
    B00000000
  };

  byte snake28[8] = {
    B00000000,
    B00000000,
    B00000000,
    B01100000,
    B00110000,
    B00010100,
    B00011100,
    B00000000
  };

  byte snake29[8] = {
    B00000000,
    B00000000,
    B00000000,
    B11100000,
    B00110000,
    B00010100,
    B00011100,
    B00000000
  };


  byte snake30[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  bool skip;
  skip = render(snake1, 200);
  if (skip) {
    return;
  }
  skip = render(snake2, 200);
  if (skip) {
    return;
  }
  skip = render(snake3, 200);
  if (skip) {
    return;
  }
  skip = render(snake4, 200);
  if (skip) {
    return;
  }
  skip = render(snake5, 200);
  if (skip) {
    return;
  }
  skip = render(snake6, 200);
  if (skip) {
    return;
  }
  skip = render(snake7, 200);
  if (skip) {
    return;
  }
  skip = render(snake8, 200);
  if (skip) {
    return;
  }
  skip = render(snake9, 200);
  if (skip) {
    return;
  }
  skip = render(snake10, 200);
  if (skip) {
    return;
  }
  skip = render(snake11, 200);
  if (skip) {
    return;
  }
  skip = render(snake12, 200);
  if (skip) {
    return;
  }
  skip = render(snake13, 200);
  if (skip) {
    return;
  }
  skip = render(snake14, 200);
  if (skip) {
    return;
  }
  skip = render(snake15, 200);
  if (skip) {
    return;
  }
  skip = render(snake16, 200);
  if (skip) {
    return;
  }
  skip = render(snake17, 200);
  if (skip) {
    return;
  }
  skip = render(snake18, 200);
  if (skip) {
    return;
  }
  skip = render(snake19, 200);
  if (skip) {
    return;
  }
  skip = render(snake20, 200);
  if (skip) {
    return;
  }
  skip = render(snake21, 200);
  if (skip) {
    return;
  }
  skip = render(snake22, 200);
  if (skip) {
    return;
  }
  skip = render(snake23, 200);
  if (skip) {
    return;
  }
  skip = render(snake24, 200);
  if (skip) {
    return;
  }
  skip = render(snake25, 200);
  if (skip) {
    return;
  }
  skip = render(snake26, 200);
  if (skip) {
    return;
  }
  skip = render(snake27, 200);
  if (skip) {
    return;
  }
  skip = render(snake28, 200);
  if (skip) {
    return;
  }
  skip = render(snake29, 200);
  if (skip) {
    return;
  }
  skip = render(snake30, 200);
  if (skip) {
    return;
  }
  skip = render(snake29, 200);
  if (skip) {
    return;
  }
  skip = render(snake30, 200);
  if (skip) {
    return;
  }
  skip = render(snake29, 200);
  if (skip) {
    return;
  }
  skip = render(snake30, 200);
}





void arrows() {
  byte arrowup[8] = {
    B00000000,
    B00011000,
    B00111100,
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00000000
  };

  byte arrowdown[8] = {
    B00000000,
    B00011000,
    B00011000,
    B00011000,
    B01111110,
    B00111100,
    B00011000,
    B00000000
  };

  byte arrowright[8] = {
    B00000000,
    B00001000,
    B00001100,
    B01111110,
    B01111110,
    B00001100,
    B00001000,
    B00000000
  };


  byte arrowleft[8] = {
    B00000000,
    B00010000,
    B00110000,
    B01111110,
    B01111110,
    B00110000,
    B00010000,
    B00000000
  };

  bool skip;
  skip = render(arrowup, 200);
  if (skip) {
    return;
  }
  skip = render(arrowright, 200);
  if (skip) {
    return;
  }
  skip = render(arrowdown, 200);
  if (skip) {
    return;
  }
  skip = render(arrowleft, 200);
}


void directions() {
  byte directions1[8] = {
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte directions2[8] = {
    B00000000,
    B00000000,
    B10000000,
    B01000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte directions3[8] = {
    B00000000,
    B10000000,
    B01000000,
    B00100000,
    B01000000,
    B10000000,
    B00000000,
    B00000000
  };

  byte directions4[8] = {
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B00000000
  };

  byte directions5[8] = {
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B00000000
  };

  byte directions6[8] = {
    B00100000,
    B00010000,
    B00001000,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B00000000
  };

  byte directions7[8] = {
    B00010000,
    B00001000,
    B00000100,
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00000000
  };

  byte directions8[8] = {
    B00001000,
    B00000100,
    B00000010,
    B00000001,
    B00000010,
    B00000100,
    B00001000,
    B00000000
  };

  byte directions9[8] = {
    B00000100,
    B00000010,
    B00000001,
    B00000000,
    B00000001,
    B00000010,
    B00000100,
    B00000000
  };

  byte directions10[8] = {
    B00000010,
    B00000001,
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000010,
    B00000000
  };

  byte directions11[8] = {
    B00000001,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000000
  };

  byte directions12[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  bool skip;
  skip = render(directions1, 200);
  if (skip) {
    return;
  }
  skip = render(directions2, 200);
  if (skip) {
    return;
  }
  skip = render(directions3, 200);
  if (skip) {
    return;
  }
  skip = render(directions4, 200);
  if (skip) {
    return;
  }
  skip = render(directions5, 200);
  if (skip) {
    return;
  }
  skip = render(directions6, 200);
  if (skip) {
    return;
  }
  skip = render(directions7, 200);
  if (skip) {
    return;
  }
  skip = render(directions8, 200);
  if (skip) {
    return;
  }
  skip = render(directions9, 200);
  if (skip) {
    return;
  }
  skip = render(directions10, 200);
  if (skip) {
    return;
  }
  skip = render(directions11, 200);
  if (skip) {
    return;
  }
  skip = render(directions12, 200);
}
void packman() {


  byte packman1[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };


  byte packman2[8] = {
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B00000000,
    B00000000,
    B10000000,
    B00000000
  };


  byte packman3[8] = {
    B00000000,
    B00000000,
    B10000000,
    B11000000,
    B00000000,
    B00000000,
    B11000000,
    B10000000
  };



  byte packman4[8] = {
    B00000000,
    B10000000,
    B11000000,
    B11100000,
    B00000000,
    B00000000,
    B11100000,
    B11000000
  };



  byte packman5[8] = {
    B00000000,
    B11000000,
    B01100000,
    B11110000,
    B10000000,
    B10000000,
    B11110000,
    B11100000
  };

  byte packman6[8] = {
    B00000000,
    B11100000,
    B11110000,
    B01111000,
    B11000000,
    B11000000,
    B11111000,
    B11110000
  };


  byte packman7[8] = {
    B00000000,
    B01110000,
    B11111000,
    B10111100,
    B11100000,
    B11100000,
    B11111100,
    B01111000
  };


  byte packman8[8] = {
    B00000000,
    B00111000,
    B01111100,
    B11011110,
    B11110000,
    B11110000,
    B01111110,
    B00111100
  };

  byte packman9[8] = {
    B00000000,
    B00011100,
    B00111110,
    B01101111,
    B01111000,
    B01111000,
    B00111111,
    B00011110
  };


  byte packman10[8] = {
    B00000000,
    B00001110,
    B00011111,
    B00110111,
    B00111100,
    B00111100,
    B00011111,
    B00001111
  };


  byte packman11[8] = {
    B00000000,
    B00000111,
    B00001111,
    B00011011,
    B00011110,
    B00011110,
    B00001111,
    B00000111
  };


  byte packman12[8] = {
    B00000000,
    B00000011,
    B00000111,
    B00001101,
    B00001111,
    B00001111,
    B00000111,
    B00000011
  };



  byte packman13[8] = {
    B00000000,
    B00000001,
    B00000011,
    B00000110,
    B00000111,
    B00000111,
    B00000011,
    B00000001
  };


  byte packman14[8] = {
    B00000000,
    B00000000,
    B00000001,
    B00000011,
    B00000011,
    B00000011,
    B00000001,
    B00000000
  };



  byte packman15[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000001,
    B00000001,
    B00000000,
    B00000000
  };


  byte packman16[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };


  bool skip;
  skip = render(packman1, 200);
  if (skip) {
    return;
  }
  skip = render(packman2, 200);
  if (skip) {
    return;
  }
  skip = render(packman3, 200);
  if (skip) {
    return;
  }
  skip = render(packman4, 200);
  if (skip) {
    return;
  }
  skip = render(packman5, 200);
  if (skip) {
    return;
  }
  skip = render(packman6, 200);
  if (skip) {
    return;
  }
  skip = render(packman7, 200);
  if (skip) {
    return;
  }
  skip = render(packman8, 200);
  if (skip) {
    return;
  }
  skip = render(packman9, 200);
  if (skip) {
    return;
  }
  skip = render(packman10, 200);
  if (skip) {
    return;
  }
  skip = render(packman11, 200);
  if (skip) {
    return;
  }
  skip = render(packman12, 200);
  if (skip) {
    return;
  }
  skip = render(packman13, 200);
  if (skip) {
    return;
  }
  skip = render(packman14, 200);
  if (skip) {
    return;
  }
  skip = render(packman15, 200);
  if (skip) {
    return;
  }  skip = render(packman16, 200);
}

void diagonals() {
  byte diagonal1[8] = {
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010
  };

  byte diagonal2[8] = {
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101
  };

  bool skip = render(diagonal1, 500);
  if (skip) {
    return;
  }
  render(diagonal2, 500);
}

void waterdrip() {
  byte drip1[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111
  };


  byte drip2[8] = {
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111
  };

  byte drip3[8] = {
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111
  };

  byte drip4[8] = {
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111
  };

  byte drip5[8] = {
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B11111111,
    B11111111
  };

  byte drip6[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B11111111,
    B11111111
  };
  byte drip7[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B11111111,
    B11111111
  };

  byte drip8[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11100111,
    B11111111
  };

  byte drip9[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00100100,
    B11011011,
    B11111111
  };

  byte drip10[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01011010,
    B10100001,
    B11111111
  };

  byte drip11[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01111110,
    B11111111

  };

  bool skip;
  skip = render(drip1, 100);
  if (skip) {
    return;
  }
  skip = render(drip2, 100);
  if (skip) {
    return;
  }
  skip = render(drip3, 100);
  if (skip) {
    return;
  }
  skip = render(drip4, 100);
  if (skip) {
    return;
  }
  skip = render(drip5, 100);
  if (skip) {
    return;
  }
  skip = render(drip6, 100);
  if (skip) {
    return;
  }
  skip = render(drip7, 100);
  if (skip) {
    return;
  }
  skip = render(drip8, 100);
  if (skip) {
    return;
  }
  skip = render(drip9, 100);
  if (skip) {
    return;
  }
  skip = render(drip10, 100);
  if (skip) {
    return;
  }
  render(drip11, 100);

}

void aliens() {

  byte alien1[8] = {

    // Animation bitmaps. Each frame of animation MUST contain
    // 8 lines of graphics data (there is no error checking for
    // length). Each line should be prefixed with the letter 'B',
    // followed by exactly 8 binary digits (0 or 1), no more,
    // no less (again, no error checking). '0' represents an
    // 'off' pixel, '1' an 'on' pixel. End line with a comma.
    B00011000, // This is the first frame for alien #1
    B00111100, // If you squint you can kind of see the
    B01111110, // image in the 0's and 1's.
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B10100101
    // The 9th line (required) is the time to display this frame,
    // in 1/100ths of a second (e.g. 100 = 1 sec, 25 = 1/4 sec,
    // etc.). Range is 0 (no delay) to 255 (2.55 seconds). If
    // longer delays are needed, make duplicate frames.
    //25, // 0.25 seconds
  };

  byte alien2[8] = {
    B00011000, // This is the second frame for alien #1
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B01000010
    //25, // 0.25 second delay
  };

  byte alien3[8] = {
    // Frames 3 & 4 for alien #1 are duplicates of frames 1 & 2.
    // Rather than list them 'the tall way' again, the lines are merged here...
    B00011000,
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B10100101
  };

  byte alien4[8] = {
    B00011000,
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B01000010
  };

  byte alien5[8] = {

    B00000000, // First frame for alien #2
    B00111100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B11000011
    //25, // 0.25 second delay
  };

  byte alien6[8] = {
    B00111100, // Second frame for alien #2
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B00100100,
    B00100100
    //25,
  };

  byte alien7[8] = {
    // Frames 3 & 4 for alien #2 are duplicates of frames 1 & 2
    B00000000,
    B00111100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B11000011
  };

  byte alien8[8] = {
    B00111100,
    B01111110,
    B11011011,
    B11011011,
    B01111110,
    B00100100,
    B00100100,
    B00100100
  };

  byte alien9[8] = {

    B00100100, // First frame for alien #3
    B00100100,
    B01111110,
    B11011011,
    B11111111,
    B11111111,
    B10100101,
    B00100100
    //25,
  };

  byte alien10[8] = {
    B00100100, // Second frame for alien #3
    B10100101,
    B11111111,
    B11011011,
    B11111111,
    B01111110,
    B00100100,
    B01000010
    //25,
  };

  byte alien11[8] = {
    // Frames are duplicated as with prior aliens
    B00100100,
    B00100100,
    B01111110,
    B11011011,
    B11111111,
    B11111111,
    B10100101,
    B00100100
  };

  byte alien12[8] = {
    B00100100,
    B10100101,
    B11111111,
    B11011011,
    B11111111,
    B01111110,
    B00100100,
    B01000010
  };

  byte alien13[8] = {
    B00111100, // First frame for alien #4
    B01111110,
    B10110011,
    B01111110,
    B00111100,
    B00000000,
    B00001000,
    B00000000
    //12, // ~1/8 second delay
  };

  byte alien14[8] = {
    B00111100, // Second frame for alien #4
    B01111110,
    B10011001,
    B01111110,
    B00111100,
    B00000000,
    B00001000,
    B00001000
    //12,
  };

  byte alien15[8] = {
    B00111100, // Third frame for alien #4 (NOT a repeat of frame 1)
    B01111110,
    B11001101,
    B01111110,
    B00111100,
    B00000000,
    B00000000,
    B00001000
    //12,
  };

  byte alien16[8] = {
    B00111100, // Fourth frame for alien #4 (NOT a repeat of frame 2)
    B01111110,
    B11100111,
    B01111110,
    B00111100,
    B00000000,
    B00000000,
    B00000000
    //12,
  };

  byte alien17[8] = {
    // Frames 5-8 are duplicates of 1-4, lines merged for brevity
    B00111100,
    B01111110,
    B10110011,
    B01111110,
    B00111100,
    B00000000,
    B00001000,
    B00000000
  };

  byte alien18[8] = {
    B00111100,
    B01111110,
    B10011001,
    B01111110,
    B00111100,
    B00000000,
    B00001000,
    B00001000
  };

  byte alien19[8] = {
    B00111100,
    B01111110,
    B11001101,
    B01111110,
    B00111100,
    B00000000,
    B00000000,
    B00001000
  };

  byte alien20[8] = {
    B00111100,
    B01111110,
    B11100111,
    B01111110,
    B00111100,
    B00000000,
    B00000000,
    B00000000
  };

  bool skip;
  skip = render(alien1, 200);
  if (skip) {
    return;
  }
  skip = render(alien2, 200);
  if (skip) {
    return;
  } skip = render(alien3, 200);
  if (skip) {
    return;
  } skip = render(alien4, 200);
  if (skip) {
    return;
  } skip = render(alien5, 200);
  if (skip) {
    return;
  } skip = render(alien6, 200);
  if (skip) {
    return;
  } skip = render(alien7, 200);
  if (skip) {
    return;
  } skip = render(alien8, 200);
  if (skip) {
    return;
  } skip = render(alien9, 200);
  if (skip) {
    return;
  }
  skip = render(alien10, 200);
  if (skip) {
    return;
  }
  skip = render(alien11, 200);
  if (skip) {
    return;
  }
  skip = render(alien12, 200);
  if (skip) {
    return;
  }
  skip = render(alien13, 200);
  if (skip) {
    return;
  }
  skip = render(alien14, 200);
  if (skip) {
    return;
  }
  skip = render(alien15, 200);
  if (skip) {
    return;
  }
  skip = render(alien16, 200);
  if (skip) {
    return;
  }
  skip = render(alien17, 200);
  if (skip) {
    return;
  }
  skip = render(alien18, 200);
  if (skip) {
    return;
  }
  skip = render(alien19, 200);
  if (skip) {
    return;
  }

  render(alien20, 200);

}

void blockanim() {

  byte ba1[8] = {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111
  };

  byte ba2[8] = {
    B00000000,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B00000000
  };

  byte ba3[8] = {
    B00000000,
    B00000000,
    B00111100,
    B00111100,
    B00111100,
    B00111100,
    B00000000,
    B00000000
  };

  byte ba4[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000
  };

  byte ba5[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  byte ba6[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000
  };

  byte ba7[8] = {
    B00000000,
    B00000000,
    B00111100,
    B00111100,
    B00111100,
    B00111100,
    B00000000,
    B00000000
  };

  byte ba8[8] = {

    B00000000,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B00000000
  };

  byte ba9[8] = {

    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111
  };

  byte ba10[8] = {

    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111

  };
  bool skip;
  skip = render(ba1, 200);
  if (skip) {
    return;
  }
  skip = render(ba2, 200);
  if (skip) {
    return;
  } skip = render(ba3, 200);
  if (skip) {
    return;
  } skip = render(ba4, 200);
  if (skip) {
    return;
  } skip = render(ba5, 200);
  if (skip) {
    return;
  } skip = render(ba6, 200);
  if (skip) {
    return;
  } skip = render(ba7, 200);
  if (skip) {
    return;
  } skip = render(ba8, 200);
  if (skip) {
    return;
  } skip = render(ba9, 200);
  if (skip) {
    return;
  }
  render(ba10, 200);

}
void pulse() {
  byte bigHeart[] = {
    B01100110,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00011000,
    B00000000
  };

  byte smallHeart[] = {
    B00000000,
    B00000000,
    B00010100,
    B00111110,
    B00111110,
    B00011100,
    B00001000,
    B00000000
  };

  bool skip = render(bigHeart, 750);
  if (skip) {
    return;
  }
  render(smallHeart, 750);
}
