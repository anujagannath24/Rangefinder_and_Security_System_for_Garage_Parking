#include <LiquidCrystal.h>
#include <IRremote.h>      //including infrared remote header file

//ir
int RECV_PIN = 13;        // the pin where you connect the output pin of IR sensor 
IRrecv irrecv(RECV_PIN);
decode_results results;

// ultrasonic
int trig = 7; 
int echo = 6; 
long var_echo; 
long cm;

//rgb led
int led = A2;
int led1 = A1;
int led2 = A0;

//lcd
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int arr[4];
int count = 0;
void setup() 
{ 
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  Serial.begin(9600);
    irrecv.enableIRIn();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);  
}

int find_val(int var)
{
  switch (var) 
  {
    case 0xFF6897:
      return 0;
    case 0xFF30CF:
    // statements
      return 1;
    case 0xFF18E7:
    // statements
      return 2;
    case 0xFF7A85:
    // statements
      return 3;
    case 0xFF10EF:
    // statements
      return 4;
    case 0xFF38C7:
    // statements
      return 5;
    case 0xFF5AA5:
    // statements
      return 6;
    case 0xFF42BD:
    // statements
      return 7;
    case 0xFF4AB5:
    // statements
      return 8;
    case 0xFF52AD:
    // statements
      return 9;
    default:
    // statements
      return 10;
  }
}
void loop() 
{ 
    int val;
    if(irrecv.decode(&results)) 
    {
      //Serial.print("\n inside loop"); 
      //Serial.print(results.value, HEX);
      //Serial.print("\n");
      val = find_val(results.value);
      Serial.print(val);
      Serial.print("\n");
      irrecv.resume();
      if(val == 9)
      {
        lcd.setCursor(0, 0);
        lcd.print("Enter password");
        lcd.setCursor(0, 1);
       
        while(1)//irrecv.decode(&results)) 
        {
          //Serial.print("in while\n");
          if(irrecv.decode(&results))
          {
            //Serial.print("\nreceived - ");
            //Serial.print("\nreceived\n");
            val = find_val(results.value);
            if(val != 10)
            {
              arr[count] = val;
              count++;
              lcd.print("*");
              //Serial.print("\nreceived - ");
              Serial.print(val);  
              if(count == 4)
              {
                if((arr[0] == 1) && (arr[1] == 2) 
                  && (arr[2] == 3) && (arr[3] == 4))
                {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Successful");
                  count = 0;
                }
                else
                {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Password wrong");
                  count = 0;
                }
                Serial.print("\n break\n"); 
                break;
              }
            }
            //Serial.print("\n RESUME \n"); 
            irrecv.resume();
          }
        }
      }
    }
    //Serial.print("\n outside loop"); 
    //irrecv.resume();
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  var_echo = pulseIn(echo, HIGH); 
  cm = var_echo / 58; 
  //Serial.print("Distance in cm : "); 
  //Serial.println(cm); 
  if(cm < 15)
  {
    analogWrite(led, 0);
    analogWrite(led1, 0);
    analogWrite(led2, 255);
  }
  else if(cm < 45)
  {
    analogWrite(led, 0);
    analogWrite(led1, 130);
    analogWrite(led2, 255);
  }
  else if(cm < 210)
  {
    analogWrite(led, 0);
    analogWrite(led1, 255);
    analogWrite(led2, 0);
  }
  else
  {
    analogWrite(led, 0);
    analogWrite(led1, 0);
    analogWrite(led2, 0);
  }

}
