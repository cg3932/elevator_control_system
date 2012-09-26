#include <Scheduler.h>

int  counter;
String incomingString="0";
Scheduler obj;

const int buttonPin = 12;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int input[]= {2,3,4,5,6,7,8,9,10,11}; //input pins
const int pinSize= 10;                 //number of input pins 
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int inputState  = 0;         // variable for reading the pushbutton status

void setup()
{
  Serial.begin(9600);
  counter =0;
  
  // initialize the LED pin as an output:
  
  pinMode(ledPin, OUTPUT);      
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  int i;
  for(i=0;i<pinSize;++i)
  {
     pinMode(input[i],INPUT);
  }
} 

void loop()
{
  

  
//  //This section for simulation
//  if (Serial.available() > 0) 
//  {
//        int i;
//	// read the incoming string
//        for(i=0;i<11;++i)
//        {
//         char x = Serial.read();
//         delay(1);
//	 incomingString+=String(x);
//        }
//        
//        obj.Invoke(incomingString);
//        incomingString="";
//        Serial.flush();
//  }
  //Simulation Section ends here
  
    // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) 
  {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    int i;
    for(i=0;i<pinSize;++i)
     {
      // read the state of the pushbutton value:
      inputState = digitalRead(input[i]);
      if (inputState == HIGH)
      incomingString+="1";
      else
      incomingString+="0";
     }
     //Serial.println(incomingString);
     obj.Invoke(incomingString);
     incomingString="0";
    delay(500);
  } 
  else
  {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
  
  
  
  if(counter==0)
   obj.Update();
  
  if(counter==1000)
   counter=0;
  else
   counter++;
   
  delay(2);

}
