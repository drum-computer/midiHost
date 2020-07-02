#ifndef LCD_h
#define LCD_h
#include "Arduino.h"
#include "LiquidCrystal.h"

class LCD : public LiquidCrystal
{
private:
  /* data */
public:
  LCD(int p1, int p2, int p3, int p4, int p5, int p6)
  : LiquidCrystal(p1, p2, p3, p4, p5, p6)
  {
  }
  
  void printInputVal(int val)
  {
    LiquidCrystal::setCursor(12, 0);
    if(val < 10)
      LiquidCrystal::print("00");
    else if(val < 100)
      LiquidCrystal::print("0");
 
    LiquidCrystal::print(val);
  }

  void printOutputVal(int val)
  {
    LiquidCrystal::setCursor(12, 1);
    if(val < 10)
      LiquidCrystal::print("00");
    else if(val < 100)
      LiquidCrystal::print("0");
 
    LiquidCrystal::print(val);
  }

};


#endif