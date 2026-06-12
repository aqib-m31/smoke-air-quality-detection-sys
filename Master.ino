#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX, TX

const int mqPin135 = A0;     // MQ-135 analog pin
const int mqPin3 = A1;     // MQ-3 analog pin
int val135 = 0;
int val3 = 0;

char S = 'S';
char A = 'A';


void setup() {
  Serial.begin(9600);   // Serial monitor
  BTSerial.begin(38400); // Bluetooth
  pinMode(mqPin135, INPUT);
  pinMode(mqPin3, INPUT);
  Serial.println("Master ready");
}

void loop() {
  val135 = analogRead(mqPin135);               // 0 - 1023
  float voltage135 = val135 * (5.0 / 1023.0);
  Serial.print("Analog135: ");
  Serial.print(val135);
  Serial.print("  | V135: ");
  Serial.println(voltage135, 3);

  val3 = analogRead(mqPin3);               // 0 - 1023
  float voltage3 = val3 * (5.0 / 1023.0);
  Serial.print("Analog3: ");
  Serial.print(val3);
  Serial.print("  | V3: ");
  Serial.println(voltage3, 3);

  delay(1000); // for getting the tolerance values, remove when done
  // BTSerial.write('T');
  // Serial.println('T');
  if (val135 > 800) {
      Serial.println(">>> ALERT: Reading high (possible gas component), Alerting and venting now");

      BTSerial.write(S);
      Serial.println(S);
      //delay(500);
  }        
  if (val3 > 500) {
      Serial.println(">>> ALERT: Reading high (smoke component) Alerting and venting now");
      BTSerial.write(A);
      Serial.println(A);
      
      
      //delay(500);
  } 
               
}
