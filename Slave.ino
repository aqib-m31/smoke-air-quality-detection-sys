#include <SoftwareSerial.h>
SoftwareSerial BTSerial(18, 19);  // RX, TX
int motor1pin1 = 2;
int motor1pin2 = 3;
int en1 = A1;  //pwm

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  Serial.println("Slave ready");
}

void loop() {
  if (BTSerial.available()) {
    //String msg = BTSerial.readStringUntil('\n');
    Serial.println("recieved");
    char c = BTSerial.read();
    Serial.println(c);
    if (c == 'S') {
      //High Smoke
      Serial.println(c);
      //code for LCD
    }
    if (c == 'A') {
      //Low Air Quality
      Serial.println(c);
      //code for LCD
    }

    //turn on ventilation
    analogWrite(A1, 150);  //ENA  pin

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);

    delay(500);  // delay for sometime
  } else {
    analogWrite(en1, 0);  //ENA  pin
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
  }
}
