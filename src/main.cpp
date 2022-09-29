#include <Arduino.h>

/*
Arduino - Blink
*/


// void setup() {
//   // put your setup code here, to run once:
//   pinMode(LED_BUILTIN, OUTPUT);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   digitalWrite(LED_BUILTIN, HIGH);
//   delay(250);
//   digitalWrite(LED_BUILTIN, LOW);
//   delay(250);
// }

/*
Arduino - RGB
*/

// // Define pins on the board
// #define BLUE 4
// #define GREEN 5
// #define RED 7
// #define color_range 255

// void RGB_color(int, int, int);

// void setup() {
//   pinMode(RED, OUTPUT);
//   pinMode(GREEN, OUTPUT);
//   pinMode(BLUE, OUTPUT);
// }

// void loop() {
  
//   for (int i=0; i<color_range; i++){
//     for (int j=0; j<color_range; j++){
//       for (int k=0; k<color_range; k++){
//         RGB_color(i, j, k); // Green
//         delay(5);
//       }
//     }
//   }
// }
// void RGB_color(int red_light_value, int green_light_value, int blue_light_value) {
//   analogWrite(RED, red_light_value);
//   analogWrite(GREEN, green_light_value);
//   analogWrite(BLUE, blue_light_value);
// }

/*
Arduino -  Inputs
*/

int ledPin = 7;
int buttonApin = 5;
int buttonBpin = 4;

byte leds = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}

void loop() 
{
  if (digitalRead(buttonApin) == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
}