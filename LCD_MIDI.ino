#include <LiquidCrystal.h>

#define POT1_PIN           A0 
#define LEFT_BUTTON_PIN    10
#define RIGHT_BUTTON_PIN    9
#define UP_BUTTON_PIN       8
#define DOWN_BUTTON_PIN     7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// buttons and controls
int pot1_val = 0;
int prev_pot1_val = 0;
int button_left, button_right, button_up, button_down;
int last_state_left = HIGH;
int last_state_right = HIGH;
int last_state_up = HIGH;
int last_state_down = HIGH;



// midi
int channel =   1;
int cc =        7;
int mode =      0; // 0 = cc, 1 = nrpn

// cursor
const int cursor_positions[2] = {7, 12};
int cursor_position = 0;


void setup() 
{
  initPins();
  initLCD();

  // begin midi communication
  Serial.begin(31250);
}


void loop() 
{
  // init all sensors
  button_left =   digitalRead(LEFT_BUTTON_PIN);
  button_right =  digitalRead(RIGHT_BUTTON_PIN);
  button_up =     digitalRead(UP_BUTTON_PIN);
  button_down =   digitalRead(DOWN_BUTTON_PIN);
  pot1_val =      map(analogRead(POT1_PIN), 0, 1023, 0, 127);

  // check all sensors in the loop
  // check potentiometer
  if(pot1_val != prev_pot1_val)
  {
    sendMidiCC(pot1_val);
    prev_pot1_val = pot1_val;
  }

  // check left button
  if(button_left == LOW && last_state_left == HIGH)
  {
    moveLeft();
    last_state_left = LOW;
  }
  if(button_left == HIGH && last_state_left == LOW)
    last_state_left = HIGH;

  // check right button
  if(button_right == LOW && last_state_right == HIGH)
  {
    moveRight();
    last_state_right = LOW;
  }
  if(button_right == HIGH && last_state_right == LOW)
    last_state_right = HIGH;

  // check up button
  if(button_up == LOW && last_state_up == HIGH)
  {
    valueUp();
    last_state_up = LOW;
  }
  if(button_up == HIGH && last_state_up == LOW)
    last_state_up = HIGH;

  // check down button
  if(button_down == LOW && last_state_down == HIGH)
  {
    valueDown();
    last_state_down = LOW;
  }
  if(button_down == HIGH && last_state_down == LOW)
    last_state_down = HIGH;

  delay(10);
}

void moveLeft()
{
  cursor_position = !cursor_position;
  lcd.setCursor(cursor_positions[cursor_position], 1);
}

void moveRight()
{
  cursor_position = !cursor_position;
  lcd.setCursor(cursor_positions[cursor_position], 1);
}

void valueUp()
{
  switch (cursor_position)
  {
  case 0:
    channelUp();
    break;
  
  case 1:
    ccUp();
    break;
  }
}

void valueDown()
{
  switch (cursor_position)
  {
  case 0:
    channelDown();
    break;
  
  case 1:
    ccDown();
    break;
  }
}

void ccUp()
{
  lcd.setCursor(12, 1);
  lcd.print("   ");
  cc = (cc == 127) ? 0 : cc + 1;
  lcd.setCursor(12, 1);
  lcd.print(cc);
  lcd.setCursor(cursor_positions[cursor_position], 1);
}

void ccDown()
{
  lcd.setCursor(12, 1);
  lcd.print("   ");
  cc = (cc == 0) ? 127 : cc - 1;
  lcd.setCursor(12, 1);
  lcd.print(cc);
  lcd.setCursor(cursor_positions[cursor_position], 1);
}

void channelUp()
{
  lcd.setCursor(7, 1);
  lcd.print("  ");
  channel = (channel == 16) ? 1 : channel + 1;
  lcd.setCursor(7, 1);
  lcd.print(channel);
  lcd.setCursor(cursor_positions[cursor_position], 1);
}

void channelDown()
{
  lcd.setCursor(7, 1);
  lcd.print("  ");
  channel = (channel == 1) ? 16 : channel - 1;
  lcd.setCursor(7, 1);
  lcd.print(channel);
  lcd.setCursor(cursor_positions[cursor_position], 1);
}

void sendMidiCC(int val)
{
  Serial.write(176 + (channel - 1));
  Serial.write(cc);
  Serial.write(val);

  lcd.setCursor(12, 0);
  lcd.print("   ");
  lcd.setCursor(12, 0);
  lcd.print(pot1_val);
}

void initPins()
{
  pinMode(POT1_PIN, INPUT);
  pinMode(LEFT_BUTTON_PIN, INPUT);
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  pinMode(UP_BUTTON_PIN, INPUT);
  pinMode(DOWN_BUTTON_PIN, INPUT);
}

void initLCD()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Src: Pot1 V:");
  lcd.setCursor(0, 1);
  lcd.print("Dst: ch13 cc123");
  lcd.setCursor(7, 1);
  lcd.cursor();
}
