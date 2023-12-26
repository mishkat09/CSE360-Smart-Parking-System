#include <SPI.h>
#include <RFID.h>
#include <Servo.h>


Servo myservo; 
int pos = 0; 

#define SDA_DIO 9
#define RESET_DIO 8
#define IR1 4
#define IR2 3
#define IR3 0
#define led1 22
#define led2 23
#define led3 24
#define mq2 A1
#define buzzerPin 10 
#define motorA 44
#define motorB 45
String userInput = "18812921020732";
bool allOccupied = false;
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 


void setup()
{ 
  Serial.begin(9600);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(mq2,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorA,OUTPUT);
  pinMode(motorA,OUTPUT);
  myservo.attach(6);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
}

void loop()
{
  /* Has a card been detected? */
  String cardSerialNumber = "";
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.println("Card detected:");
     
    for(int i=0;i<5;i++)
    {
    // Serial.print(RC522.serNum[i],DEC);
     cardSerialNumber += String(RC522.serNum[i], DEC);
    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
  }


    int ir_read1 = digitalRead(IR1);
    // Serial.println(ir_read1);
    int ir_read2 = digitalRead(IR2);
    // Serial.println(ir_read2);
    int ir_read3 = digitalRead(IR3);
    // Serial.println(ir_read3);
    if(ir_read1==0){
      
      digitalWrite(led1,HIGH);
    }
    else
    {
      digitalWrite(led1,LOW);
    }
        if(ir_read2==0){
      digitalWrite(led2,HIGH);
    }
        else
    {
      digitalWrite(led2,LOW);
    }
        if(ir_read3==0){
      digitalWrite(led3,HIGH);
    }
    else
    {
      digitalWrite(led3,LOW);
    }
    /////////////////////////////////////////////////////////////////////

    if (ir_read1==0 && ir_read2==0 && ir_read3==0){
      allOccupied=true;
    }
    else{
      allOccupied=false;
    }
    if (cardSerialNumber == userInput && allOccupied==false) {
      Serial.println("Servo UP");
      servoUp();
    } 
    else{
      Serial.println("Servo Down");
      servoDown();
    }


    
  unsigned int sensorValue = analogRead(mq2);  // Read the analog value from sensor
  unsigned int mq2_read = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
  Serial.println(mq2_read);
    if (mq2_read>80){
      Serial.println("Gas Detected");
      buzzerOn();
      motorStart();
    }
}


void servoUp(){
  myservo.write(0);
  delay(5000);
  servoDown();
}
void servoDown(){
  myservo.write(120);
}


void buzzerOn(){
  tone(buzzerPin, 1000);
  delay(3000);
  noTone(buzzerPin);
  
}


void motorStart(){
  digitalWrite(motorA,HIGH);
  digitalWrite(motorB,LOW);
  delay(10000);
  digitalWrite(motorA,LOW);
  digitalWrite(motorB,LOW);
}