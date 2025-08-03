

#define CLOCK_PIN 12
#define DATA_PIN  11


void setup() 
{
  Serial.begin(115200);                                                   
  pinMode(CLOCK_PIN, INPUT);
  pinMode(DATA_PIN, INPUT);
  
}

char buf[20];
unsigned long tmpTime;
int sign;
int inches;
long value;
double result;
bool mm = true; //define mm to false if you want inces values

void loop()
{
  while(digitalRead(CLOCK_PIN)==LOW) {}
  tmpTime=micros();
  while(digitalRead(CLOCK_PIN)==HIGH) {} 
  if((micros()-tmpTime)<500) return;
  readCaliper(); 
  buf[0]=' ';
  dtostrf(result,6,3,buf+1); strcat(buf," in ");  
  dtostrf(result*2.54,6,3,buf+1); strcat(buf," cm "); 

  if(mm)
  {
    Serial.print(result,4); Serial.println(" mm");    
    delay(100);
  }
  else
  {
    Serial.print(result); Serial.println(" in");    
    delay(100);
  }
}
void readCaliper()
{
  sign=1;
  value=0;
  inches=0;
  for(int i=0;i<24;i++) {
    while(digitalRead(CLOCK_PIN)==LOW) {}
    while(digitalRead(CLOCK_PIN)==HIGH) {}
    if(digitalRead(DATA_PIN)==HIGH) {
      if(i<20) value|=(1<<i);
      if(i==20) sign=-1;
      if(i==23) inches=1; 
    }
  }
  if(mm)
  {
    result=(value*sign)/100.00;
  }
  else
  {
  result=(value*sign)/(inches?2000.0:100.0); //We map the values for inches, define mm to false if you want inces values
  }
  
}
