  
 #include <DDS.h>  
 #include <stdio.h>
#include <LiquidCrystal.h>
 // AD9850 Module is connected to the following  
 // arduino pins  
 const int W_CLK = A5;  
 const int FQ_UD = A4;   
 const int DATA = A3;  
 const int RESET = A1;  
 
 #define buttonPin A0 
  // Instantiate the DDS PIN FUNCTIONS...  
  DDS dds(W_CLK, FQ_UD, DATA, RESET); 
   
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);// Initialised the lcd pin connections

// some variables to use in the program
long toFrequency = 0;
long currentFrequency;
long maxFrequency = 40000000;
long minFrequency = 0;
int incrementNumber = 6;
int maxprogramnumber = 6;  
int programnumber = 1;   
 void setup() {  
  // start up the DDS...    
  dds.init();   
  // (Optional) change value if the clock crystal does not resonate at 125MHz...  
  dds.trim(125000000); // enter actual oscillation frequency   
  // start the oscillator...  
  dds.setFrequency(toFrequency); 
  Serial.begin(9600);
  Serial.println("Beginning Setup");
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NUST    V0.1b  ");   
  lcd.setCursor(0, 1);
  lcd.print("  DDS Sine wave  ");
  delay(2000);
  // setup pins
  pinMode(RESET, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UD, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); 
  
    // this is a value  changed to calibrate to particular chip more accurately
  dds.setFrequency(toFrequency);
  lcd.clear();
   
 }  
 void loop() {  if(toFrequency >= maxFrequency){(toFrequency = maxFrequency);}
  if(toFrequency <= minFrequency){(toFrequency = minFrequency);}
  dds.setFrequency(toFrequency);
  currentFrequency = toFrequency;
 

switch(incrementNumber){
        
        case 0:
          Serial.println("increment amount is 1hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By    1hz");  
          break;
         
        case 1:
          Serial.println("increment amount is 10hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By   10hz ");  
          break;
        
        case 2:
          Serial.println("increment amount is 100hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By  100hz ");  
          break;
        
        case 3:
          Serial.println("increment amount is 1 000hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By   1khz"); 
          break;
 
        case 4:
          Serial.println("increment amount is 10 000hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By  10khz");  
          break;
 
        case 5:
          Serial.println("increment amount is 100 000hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By 100khz");  
          break;
      
        case 6:
          Serial.println("increment amount is 1 000 000hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By   1Mhz");  
          break;
      
        default:  
          Serial.println("increment amount is 100hz");
          lcd.setCursor(0, 0);
          lcd.print("Change By  100hz ");  
          break;
      }

  lcd.setCursor(0, 1);
  lcd.print("Freq is ");    //Print to lcd
  lcd.setCursor(8, 1);
  lcd.print(currentFrequency);
  
  Serial.println(incrementNumber);  // temporary for debuggin delete me
  
  Serial.print("Current Frequency is set to :");
  Serial.println(currentFrequency);

 while((analogRead(buttonPin))>=1000){}   // do nothing while no buttons pressed to chill out
 delay(5);


  if(analogRead(buttonPin)>=100 && analogRead(buttonPin)<=200){  //  pushed up
  upFrequency();
  delay(300);
  } 

  if(analogRead(buttonPin)>=200 && analogRead(buttonPin)<=400){  //  pushed down
  downFrequency();
  delay(300);
  }
 
  if((analogRead(buttonPin))<=50){ // pushed right
  incrementNumber++;
  delay(300);
  }   
  
  if(analogRead(buttonPin)>=400 && analogRead(buttonPin)<=600){pushed left
  incrementNumber--;
  delay(300);
  } 

  if(incrementNumber > 6){incrementNumber = 0;}          // this is the menu loop around
  if(incrementNumber < 0){incrementNumber = 6;}

  delay(100);
  lcd.clear();

}


void upFrequency()
{
  Serial.println("Going UP Frequency");
  switch(incrementNumber){
  
    case 0: 
         toFrequency = (toFrequency + 1);
         break;
         
    case 1: 
         toFrequency = (toFrequency + 10);
         break;

    case 2: 
         toFrequency = (toFrequency + 100);
         break;

    case 3: 
         toFrequency = (toFrequency + 1000);
         break;

    case 4: 
         toFrequency = (toFrequency + 10000);
         break;

    case 5: 
         toFrequency = (toFrequency + 100000);
         break;

   
    case 6:
         toFrequency = (toFrequency + 1000000);
         break;
    
    default: 
         toFrequency = (toFrequency + 10);
         break;
 }

}


void downFrequency()
{
  
  Serial.println("Going DOWN Frequency");
  switch(incrementNumber){
  
    case 0: 
         toFrequency = (toFrequency - 1);
         break;
         
    case 1: 
         toFrequency = (toFrequency - 10);
         break;

    case 2: 
         toFrequency = (toFrequency - 100);
         break;

    case 3: 
         toFrequency = (toFrequency - 1000);
         break;

    case 4: 
         toFrequency = (toFrequency - 10000);
         break;

    case 5: 
         toFrequency = (toFrequency - 100000);
         break;

    case 6:
         toFrequency = (toFrequency - 1000000);
         break;
    
    default: 
         toFrequency = (toFrequency - 10);
         break;
 }
}
