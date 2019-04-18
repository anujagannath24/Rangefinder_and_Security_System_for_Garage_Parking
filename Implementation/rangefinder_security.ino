/* header file for LCD interfacing */
#include <LiquidCrystal.h>
/* header file infrared remote */
#include <IRremote.h>
/* header file for tone generation */
#include <TimerFreeTone.h>

/* IR sensor */
int IR_rec = 13;
IRrecv irrecv(IR_rec);
/* stores the received value by IR sensor */
decode_results results;

/* Ultrasonic sensor pins */
int trig = 7;
int echo = 6;
long var_echo;
long cm;

/* RGB led pins */
int led = A2; /* blue */
int led1 = A1; /* green */
int led2 = A0; /* red */

/* LCD pins */
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* Piezo buzzer pin */
int buzzerPin = 10;

/* Garage light */ 
const int lightPin = 8;

/* array for storing password */
int arr[4];
/* counter for array */
int count = 0;

void setup() 
{ 
  /* set the pins of RGB LED as output */
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  /* set the pins of ultrasonic sensor */
  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  
  /* set the baud rate of the serial port */
  Serial.begin(9600);
  
  /* set up the IR receiver */
  irrecv.enableIRIn();
  
  /* set up the number of rows and columns of LCD */
  lcd.begin(16, 2);  

  /* set the buzzer pin as an OUTPUT */
  pinMode(buzzerPin, OUTPUT);
}

/* mapping the value received from the IR sensor to the actual
   number pressed on the remote. It takes the hex value received
   as the input and returns the number pressed. Only numbers 1 - 9
   are considered here as the other values are not required to be 
   checked in this project. Any key other than 1-9 will return an 
   error code which is 10 */
int find_val(int var)
{
  switch (var) 
  {
    case 0xFF6897:
      return 0;
    case 0xFF30CF:
      return 1;
    case 0xFF18E7:
      return 2;
    case 0xFF7A85:
      return 3;
    case 0xFF10EF:
      return 4;
    case 0xFF38C7:
      return 5;
    case 0xFF5AA5:
      return 6;
    case 0xFF42BD:
      return 7;
    case 0xFF4AB5:
      return 8;
    case 0xFF52AD:
      return 9;
    default:
      /* error */
      return 10;
  }
}

void loop() 
{ 
    int val;
    if(irrecv.decode(&results)) 
    {
      /* Receive value from IR sensor and check if it is 9. 
         9 is used to turn on the security system */
      val = find_val(results.value);
      /* value is printed on the serial port as well for debugging */
      Serial.print(val);
      Serial.print("\n");
      /* ready to receive next value from IR sensor */
      irrecv.resume();
      /* checking if value received is 9 to turn ON the security system */
      if(val == 9)
      {
        /* Initializing the LCD cursor to position 0,0 */
        lcd.setCursor(0, 0);
        lcd.print("Enter password");
        /* moves the cursor to next row */
        lcd.setCursor(0, 1);
       
        while(1)
        {
          /* reading the password character by character */
          if(irrecv.decode(&results))
          {
            /* mapping the hex code to the number pressed */
            val = find_val(results.value);
            /* checking if it is a valid number.
               10 is the error code */
            if(val != 10)
            {
              /* storing the value in array */
              arr[count] = val;
              /* incrementing the array counter */
              count++;
              /* printing * on the LCD for each character received so that 
                 the password remains hidden */
              lcd.print("*");
              Serial.print(val);
              /* Checking if 4 digits are received as it is a 4 digit password */
              if(count == 4)
              {
                /* checking the password entered with the actual password */
                if((arr[0] == 1) && (arr[1] == 2) 
                  && (arr[2] == 3) && (arr[3] == 4))
                {
                  /* clear the LCD screen */
                  lcd.clear();
                  /* setting cursor to the position 0,0 */
                  lcd.setCursor(0, 0);
                  /* prints password is successful */
                  lcd.print("Successful");
                  /* turns ON the garage light */
                  digitalWrite(lightPin, 1); 
                  count = 0;
                }
                /* if password is wrong */
                else
                {
                  /* prints that the password is wrong on the LCD */ 
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Password wrong");
                  count = 0;
                }
                break;
              }
            }
            /* ready to receive next value from IR sensor */
            irrecv.resume();
          }
        }
      }
    }
    /* sending pulse on trigger pin of ultrasonic sensor */
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig, LOW); 
    /* receiving the reflected pulse */
    var_echo = pulseIn(echo, HIGH); 
    /* calculating the distance in cm. The value is calibrated by reading the 
       value from ultrasonic sensor and adjusting it based on the actual distance
       measured manually */
    cm = var_echo / 56; 

    /* checking if the object is in the particular range */
    if(cm < 15)
    {
      /* writing output to RGB LED - red color */
      analogWrite(led, 0);
      analogWrite(led1, 0);
      analogWrite(led2, 255);
      /* turning ON the buzzer */
      TimerFreeTone(buzzerPin, 261, 250);
    }
    else if(cm < 45)
    {
      /* writing output to RGB LED - yellow color */
      analogWrite(led, 0);
      analogWrite(led1, 200);
      analogWrite(led2, 255);
    }
    else if(cm < 210)
    {
      /* writing output to RGB LED - green color */
      analogWrite(led, 0);
      analogWrite(led1, 255);
      analogWrite(led2, 0);
    }
    else
    {
      /* turning OFF the RGB LED */
      analogWrite(led, 0);
      analogWrite(led1, 0);
      analogWrite(led2, 0);
    }
}
