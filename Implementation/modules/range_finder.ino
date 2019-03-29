int trig = 12; 
int echo = 11; 
long var_echo; 
long cm;
int led = A2;
int led1 = A1;
int led2 = A0;
void setup() 
{ 
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  Serial.begin(9600); 
}
void loop() 
{ 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  var_echo = pulseIn(echo, HIGH); 
  cm = var_echo / 58; 
  Serial.print("Distance in cm : "); 
  Serial.println(cm); 
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
    
  delay(1000); 
}
