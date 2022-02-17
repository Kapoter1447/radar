//For bluetooth
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX


// For rotation calibration:
  const int timeSwitchPin = 8;
  int timeSwitch = 0;
// I setup: pinMode(timeSwitchPin,INPUT);
// I loop: timeSwitch = digitalRead(switchPin);

  const int calibrationPin = 9;
  int calibrationSwitch = 0;

  unsigned long time1;

  int tg = 1000;

  int grader = 0;


// For distance:
  const int triggerPin = 10;
  const int echoPin = 11;

void setup() 
{
  pinMode(7,OUTPUT);
  
  // put your setup code here, to run once:
  Serial.begin(57600);

  // Calibration:
  pinMode(timeSwitchPin,INPUT);
  int timeSwitch = HIGH;

  pinMode(calibrationPin,INPUT);
  int calibrationSwitch = HIGH;


  //Distance:
  pinMode(triggerPin, OUTPUT);
  pinMode (echoPin, INPUT);
  

  Serial.println("----------------------------------------------------------------");

//Bluetooth start
  // Open serial communications and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

 pinMode(5, INPUT);

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

//Bluetooth end 

}

void loop() {


// For rotation calibration:
timeSwitch = digitalRead(timeSwitchPin);
calibrationSwitch = digitalRead(calibrationPin);

  if(calibrationSwitch == 1)
    {
      Serial.println("Kalibrering påbörjad...");
      grader = 0;
     // Ifall kalibreringsknapp är intryckt: Ta tid på ett varv och sedan spara det i Time. Ta Time delat på 360 och få tid/grader. 
     // Detta sätts sedan i en loop med en delay = tid/grader. Varje tid/grader adderas 1 grad och räknar upp till 360, sedan återställs. 
      time1 = pulseIn(timeSwitchPin, HIGH, 10000000);

      Serial.print("Tid: ");
      Serial.println(time1);
      tg = time1/360;
      Serial.print("Tid per grad: ");
      Serial.println(tg);
     //Serial.println(calibrationSwitch);

      if(time1 == 0)
      {
        Serial.println("Kalibrering gick fel. Försök igen..");
        // Ifall kalibrering går fel beror det på att det tog för lång tid mellan knappen klickades på. Speeda up motorn eller ändra TIMEOUT (tredje variabel in pulsen) till något längre.
      }
   }

    delayMicroseconds(tg);
    grader = grader+1;
 //   Serial.print("Grader: ");
 //   Serial.println(grader);

    if(grader == 360)
    {
      grader = 0;
    }

//For distance meter:
  digitalWrite(triggerPin, LOW);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

long duration = pulseIn(echoPin, HIGH); 

 
long r = 3.4 * duration / 2;      // here we calculate the distance

float distance = r / 100.00;

  Serial.println(distance);

  mySerial.write(distance);
//  mySerial.write('\n'); Använd inte skikcar 10 av nån anledning

  //Bluetooth start
  if (mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  if (digitalRead(5)== LOW )
  {
  //  mySerial.write("toggle");
  //  mySerial.write('\n');
  //  delay(500);
  }
//Bluetooth end 
  digitalWrite(7,LOW);
  delay(200);
  digitalWrite(7, HIGH);

  
}
