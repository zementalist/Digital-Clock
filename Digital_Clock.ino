
int hrs1_pins[] = {26, 27, 28, 29, 30, 31, 32};
int hrs2_pins[] = {18, 19, 20, 21, 22, 23, 24};
int mins1_pins[] = {10, 11, 12, 13, 14, 15, 16};
int mins2_pins[] = {2, 3, 4, 5, 6, 7, 8};
int mapper[10][7] = {
  {1,2,3,4,5,6},
  {2,3},
  {1,2,4,5,7},
  {1,2,3,4,7},
  {2,3,6,7},
  {1, 3, 4, 6, 7},
  {1, 3, 4, 5, 6, 7},
  {1, 2, 3},
  {1, 2, 3, 4, 5, 6, 7},
  {1, 2, 3, 4, 6, 7}
  };

int current_hour = 22;
int current_minute = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 7; i++) {
    pinMode(hrs1_pins[i], OUTPUT);
    pinMode(hrs2_pins[i], OUTPUT);
    pinMode(mins1_pins[i], OUTPUT);
    pinMode(mins2_pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

// Function to turn of a LED
void reset(int leds[7]) {
  for(int i = 0;  i< 7; i++) {
    digitalWrite(leds[i], LOW);
  }
}

// Function to display a single digit on a single LED
void set_digit(int segments[7], int number) {
  for(int i = 0; i < 7; i++) {
    if(mapper[number][i] == 0)
      break;
    digitalWrite(segments[mapper[number][i]-1], HIGH);
  }
}

// Function to forward time (24 hours system)
void increment_time_step(int &minute, int &hour){
  if (hour > 22 && minute > 58){
      hour = 0;
      minute = 0;
  }
  else if(minute > 58){
      hour += 1;
      minute = 0;
  }
  else {
      minute = minute + 1;
  }
}

// Function to display number (two digits) on two LEDs
void digit_to_leds(int digit, int led1, int led2) {
  reset(led1);
  reset(led2);
  int left_side = digit / 10;
  int right_side = digit % 10;
  set_digit(led1, left_side);
  set_digit(led2, right_side);
}

void loop() {
  digit_to_leds(current_hour, hrs1_pins, hrs2_pins);
  digit_to_leds(current_minute, mins1_pins, mins2_pins);
  delay(1000);
  increment_time_step(current_minute, current_hour);
}
