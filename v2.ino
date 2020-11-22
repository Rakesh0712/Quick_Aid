//collision
int analogpin = 1;
int front=2;
int back=3;
int right=4;
int anagval=0;
int anagfrnt=0;
int anagbak=0;
int anagrgt=0

//hb
#include  <Wire.h> // include wire
//#include <LiquidCrystal_I2C.h> // include liquidcrystal i2c libary 
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 16x2 LCD address 0x27
   double alpha=0.75;
   int period=20;
   double refreshhb=0.0;
   int temphb;

   //rpm

const int dataIN =3; //IR sensor INPUT

unsigned long prevmillis; // To store time
unsigned long duration; // To store time difference
unsigned long refresh; // To store time for refresh of reading

int rpm; // RPM value

boolean currentstate; // Current state of IR input scan
boolean prevstate; // State of IR sensor in previous scan

   

void setup()
{
  pinMode(A0,INPUT);
  Serial.begin(9600);
}


void loop()
{
  //cras
  anagval= analogRead(analogpin);
  anagfrnt= analogRead(front);
  //Serial.println(anagval);
  if (anagval > 500 && anagfrnt >500 && anagbak>500 && anagrgt>500)
  {
    Serial.println("No Problem");
  }
  else
  {
    Serial.println("collided");
  delay(2000 );
  }
  delay(1000);


//hb

static double oldValue=0;
   static double oldrefresh=0; 
   int beat=analogRead(A0);  //define sensor pin to AO
   double value=alpha*oldValue+(0-alpha)*beat;
   refreshhb=value-oldValue;     
   /*lcd.setCursor(0,0); //we start writing from the first row first column
   lcd.print(" Heart Monitor "); // text to be displayed on the LCD when boot up
   lcd.setCursor(0,1);
   lcd.print("          ");
   lcd.setCursor(0,1); 
   print(beat/10);*/
   temphb = (beat/10)-10;
   if (temphb >0){
   Serial.println(temphb);}
   else
   {
    Serial.println("3");
    }
   oldValue=value;
   oldrefresh=refresh;
   delay(period*10);



//rpm
// RPM Measurement
  currentstate = digitalRead(dataIN); // Read IR sensor state
 if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from LOW to HIGH
       {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         rpm = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         prevmillis = micros(); // store time for nect revolution calculation
       }
   }
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  // LCD Display
  if( ( millis()-refresh ) >= 100 )
    {
       Serial.println(rpm);  
    }


}
