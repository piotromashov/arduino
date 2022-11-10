#include <FastLED.h>

#define trigPin 13
#define echoPin 12
#define ledPin 7

#define LEDS_PER_STRIPE 50
#define NUM_STRIPES 1
#define DATA_PIN 8

const int leds_amount = LEDS_PER_STRIPE*NUM_STRIPES;
CRGB leds[leds_amount];
// CRGB allRed[LEDS_PER_STRIPE] = CRGB::Red;
CRGB COLORS[149] = { CRGB::Amethyst, CRGB::AliceBlue, CRGB::AntiqueWhite, CRGB::Aqua, CRGB::Aquamarine, CRGB::Azure, CRGB::Beige, CRGB::Bisque, CRGB::BlanchedAlmond, CRGB::Blue, CRGB::BlueViolet, CRGB::Brown, CRGB::BurlyWood, CRGB::CadetBlue, CRGB::Chartreuse, CRGB::Chocolate, CRGB::Coral, CRGB::CornflowerBlue, CRGB::Cornsilk, CRGB::Crimson, CRGB::Cyan, CRGB::DarkBlue, CRGB::DarkCyan, CRGB::DarkGoldenrod, CRGB::DarkGray, CRGB::DarkGrey, CRGB::DarkGreen, CRGB::DarkKhaki, CRGB::DarkMagenta, CRGB::DarkOliveGreen, CRGB::DarkOrange, CRGB::DarkOrchid, CRGB::DarkRed, CRGB::DarkSalmon, CRGB::DarkSeaGreen, CRGB::DarkSlateBlue, CRGB::DarkSlateGray, CRGB::DarkSlateGrey, CRGB::DarkTurquoise, CRGB::DarkViolet, CRGB::DeepPink, CRGB::DeepSkyBlue, CRGB::DimGray, CRGB::DimGrey, CRGB::DodgerBlue, CRGB::FireBrick, CRGB::FloralWhite, CRGB::ForestGreen, CRGB::Fuchsia, CRGB::Gainsboro, CRGB::GhostWhite, CRGB::Gold, CRGB::Goldenrod, CRGB::Gray, CRGB::Grey, CRGB::Green, CRGB::GreenYellow, CRGB::Honeydew, CRGB::HotPink, CRGB::IndianRed, CRGB::Indigo, CRGB::Ivory, CRGB::Khaki, CRGB::Lavender, CRGB::LavenderBlush, CRGB::LawnGreen, CRGB::LemonChiffon, CRGB::LightBlue, CRGB::LightCoral, CRGB::LightCyan, CRGB::LightGoldenrodYellow, CRGB::LightGreen, CRGB::LightGrey, CRGB::LightPink, CRGB::LightSalmon, CRGB::LightSeaGreen, CRGB::LightSkyBlue, CRGB::LightSlateGray, CRGB::LightSlateGrey, CRGB::LightSteelBlue, CRGB::LightYellow, CRGB::Lime, CRGB::LimeGreen, CRGB::Linen, CRGB::Magenta, CRGB::Maroon, CRGB::MediumAquamarine, CRGB::MediumBlue, CRGB::MediumOrchid, CRGB::MediumPurple, CRGB::MediumSeaGreen, CRGB::MediumSlateBlue, CRGB::MediumSpringGreen, CRGB::MediumTurquoise, CRGB::MediumVioletRed, CRGB::MidnightBlue, CRGB::MintCream, CRGB::MistyRose, CRGB::Moccasin, CRGB::NavajoWhite, CRGB::Navy, CRGB::OldLace, CRGB::Olive, CRGB::OliveDrab, CRGB::Orange, CRGB::OrangeRed, CRGB::Orchid, CRGB::PaleGoldenrod, CRGB::PaleGreen, CRGB::PaleTurquoise, CRGB::PaleVioletRed, CRGB::PapayaWhip, CRGB::PeachPuff, CRGB::Peru, CRGB::Pink, CRGB::Plaid, CRGB::Plum, CRGB::PowderBlue, CRGB::Purple, CRGB::Red, CRGB::RosyBrown, CRGB::RoyalBlue, CRGB::SaddleBrown, CRGB::Salmon, CRGB::SandyBrown, CRGB::SeaGreen, CRGB::Seashell, CRGB::Sienna, CRGB::Silver, CRGB::SkyBlue, CRGB::SlateBlue, CRGB::SlateGray, CRGB::SlateGrey, CRGB::Snow, CRGB::SpringGreen, CRGB::SteelBlue, CRGB::Tan, CRGB::Teal, CRGB::Thistle, CRGB::Tomato, CRGB::Turquoise, CRGB::Violet, CRGB::Wheat, CRGB::White, CRGB::WhiteSmoke, CRGB::Yellow, CRGB::YellowGreen, CRGB::FairyLight };

const int maximum = 149;
const int minimum = 0;
int selected_color;
int program = 0;
const int total_programs = 3;

// breath program
const int max_brightness = 255;
const int min_brightness = 25;

int measure_distance() {
  int duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

bool change_program(int &program) {
  int distance = measure_distance();
  int max_distance = 60;
  if (distance < max_distance && distance >= 0) {
    //debug purposes
    // Serial.print(distance);
    // Serial.println(" cm");
    //change to next program on activation
    program = (program + 1) % total_programs;
    delay(1000);
    FastLED.setBrightness(max_brightness);
    return true;
  }
  return false;
}

void new_colour(int &selected_color) {
  selected_color = random(minimum, maximum);
}

void trail(int &selected_color) {
  const int trail_size = 5;

  for (int i = 0; i < leds_amount; i++){
    leds[i] = COLORS[selected_color];
    if (i >= trail_size){
        leds[i-trail_size] = CRGB::Black;
    }
    FastLED.show();
    if (change_program(program)) {
      return;
    }
  }
  for (int i = 0; i < leds_amount; i++){
    leds[leds_amount - 1 - i] = COLORS[selected_color];
    // leave a trail and fade it out
    if (i >= trail_size){
        leds[leds_amount-1-i+trail_size] = CRGB::Black;
    }
    FastLED.show();     
    delay(25);
    if (change_program(program)) {
      return;
    }
  }
}

//breath program
void breath(int &selected_color){  
  for (int i = 0; i < leds_amount; i++){
    leds[i] = COLORS[selected_color];
  }

  for (int i = min_brightness; i < max_brightness; i++){    
    FastLED.setBrightness(i);
    FastLED.show();
    if (change_program(program)) {
      return;
    }
  }
  for (int i = min_brightness; i < max_brightness; i++){    
    FastLED.setBrightness(max_brightness + min_brightness - 1 - i);
    FastLED.show();
    if (change_program(program)) {
      return;
    }
  }
  new_colour(selected_color);
}

void spread_color(CRGB color, CRGB leds[]){
  int center = leds_amount/2;
  for (int i = 0; i < center; i++){
    leds[center + i] = color;
    leds[center - i - 1] = color;
    FastLED.show();
    delay(25);
    if (change_program(program)) {
      return;
    }
  }
}

//Fire program
void fire(int &selected_color){
  spread_color(0xFDCF58, leds);
  spread_color(0xf27d0c, leds);
  spread_color(0x800909, leds);
  spread_color(0xf07f13, leds);
}

void run_dot_direction(int &selected_color, int &step, bool &direction){
  leds[step] = CRGB::Black;
  if (direction){
    step++;
    if (step == leds_amount - 1){
        direction = false;
    }
  } else {
    step--;
    if (step == 0){
        direction = true;
        new_colour(selected_color);
    }
  }
  leds[step] = COLORS[selected_color];
}

void dots(int &selected_color){
  static int dot1_step = 0;
  static bool dot1_direction = true;
  static int dot2_step = leds_amount;
  static bool dot2_direction = false;

  run_dot_direction(selected_color, dot1_step, dot1_direction);
  run_dot_direction(selected_color, dot2_step, dot2_direction);

  FastLED.show();
  delay(25);
  if (change_program(program)) {
    return;
  }
}

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  LEDS.addLeds<WS2812B,DATA_PIN, RGB>(leds, leds_amount);
  // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, leds_amount);
}
void loop() {
  //debug purposes
  Serial.print("Program ");
  Serial.print(program);
  Serial.print(". Selected color ");
  Serial.println(selected_color);
  switch (program) {
    case 0:
      dots(selected_color);
      break;
    case 1:
      breath(selected_color);
      break;
    case 2:
      fire(selected_color);
      break;
    case 3:
      trail(selected_color);
      break;
    default:
      break;
  }
}