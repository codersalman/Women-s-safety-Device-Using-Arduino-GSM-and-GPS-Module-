#include <TinyGPS.h>

//replace *********** with your number

TinyGPS gps;

float flat, flon;

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);


int Buzzer = 13;
int sw = 5;

void setup(){
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);

  pinMode(Buzzer, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
}


void loop(){


  if (digitalRead(sw) == LOW ) { SendMessage(); }
}



void ReadGPS(){
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  
  while (Serial.available()){
    char c = Serial.read();  
    if (gps.encode(c)) { newData = true; }
    }

  if (newData){
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    } 

}


void SendMessage(){
  digitalWrite(Buzzer,LOW);
  Serial.println("AT+CMGF=1"); delay(1000);           digitalWrite(Buzzer,HIGH);
  Serial.println("AT+CMGS=\"+91**********\"\r");      digitalWrite(Buzzer,HIGH); delay(1000);   
  Serial.println("I NEED HELP  MY LOCATION IS: ");    digitalWrite(Buzzer,LOW);  delay(100);
  Serial.print("https://maps.google.com/maps/place/");
  Serial.print(" ");                             digitalWrite(Buzzer,HIGH); delay(100);
  Serial.println(flat,6);                        digitalWrite(Buzzer,LOW);  delay(100);
  Serial.print(" ");                             digitalWrite(Buzzer,HIGH); delay(100);
  Serial.println(flon,6);                        digitalWrite(Buzzer,LOW);  delay(100);
  Serial.println(" FROM WOMEN SAFETY DEVICE ");
  
  Serial.println((char)26); digitalWrite(Buzzer,HIGH); delay(1000); digitalWrite(Buzzer,LOW);
}
