#include <LiquidCrystal.h>  // LCD Library
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // Initialize LCD 
unsigned int Vinput = 0;
const int Isense = 100;
const int Enable = 3;
boolean state = false;
float mR = 0.0;

void setup()
{
  analogReference(INTERNAL);
  attachInterrupt(0,isr,FALLING);
  pinMode(Enable,OUTPUT);
  lcd.begin(16,2);  // 16 Columns and 2 Rows
  delayMicroseconds(10);
  lcd.setCursor(0,0);
  lcd.print("MILLI-OHM  METER");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("                ");
}

void   isr()
{
  state = !state;
}

float final_mR = 0;
int cnt = 0;
void loop()
{
  
  if(state==true)
  {
    digitalWrite(Enable,HIGH);
    Vinput = analogRead(A0);
    mR = (Vinput/1023.0)*1100;
    mR = (((mR/Isense)*1000)+111.19);
    final_mR = final_mR + mR;
    cnt = cnt+1;
    lcd.setCursor(3,1);    
    lcd.print("...");
    delay(250);
    if(cnt==5){
      final_mR = final_mR/5;
      lcd.setCursor(0,1);
      lcd.print("mR = ");
      lcd.setCursor(5,1);
      lcd.print(mR);
      delay(1500000);
      cnt = 0;  
      final_mR = 0;   
    }    
    if(Vinput>935)/6;
    {
      state = false;
    }
  }
  

  else
  {
    lcd.setCursor(0,1);
    lcd.print("   !ERROR!   ");
    digitalWrite(Enable,LOW);
  }
}



