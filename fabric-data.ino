#include <Arduino.h>
#include <TinyMPU6050.h>


#define HALL_SENSOR_PIN 4
#define LED_PIN1 13
#define LED_PIN2 11
#define LED_PIN3 8
#define LED_PIN4 7
const int piezoPin = A0; // Piezo sensor connected to analog pin A0
const int flexPin = A1;  // Flex sensor connected to analog pin A1
int threshold = 300;     // Adjust this threshold according to your sensor and environment
int flexThreshold = 1022; // Adjust this threshold for the flex sensor
String forPrint = "";
String intenseSpin = "normalspeed";
String pause = "pause";

MPU6050 mpu(Wire);

void PrintGets() {
  if (abs(mpu.GetGyroX()) > 450 && abs(mpu.GetGyroY()) > 450) {
    //Serial.println("Spinning on XY Plane");
    digitalWrite(LED_PIN1, HIGH);
    //Serial.println("1");
    intenseSpin = "fastforward";
  } else if (abs(mpu.GetGyroY()) > 450 && abs(mpu.GetGyroZ()) > 450) {
    //Serial.println("Spinning on YZ Plane");
    digitalWrite(LED_PIN1, HIGH);
    //Serial.println("1");
    intenseSpin = "fastforward";

  } else if (abs(mpu.GetGyroX()) > 450 && abs(mpu.GetGyroZ()) > 450) {
    //Serial.println("Spinning on XZ Plane");
    digitalWrite(LED_PIN1, HIGH);
    //Serial.println("1");
    intenseSpin = "fastforward";
  } else {
    digitalWrite(LED_PIN1, LOW); // Turn off LED if no spinning detected
    //Serial.println("0");
    intenseSpin = "normalspeed";
  }
//   if (abs(mpu.GetGyroX()) > 800 && abs(mpu.GetGyroY()) > 800) {
//     Serial.println("Spinning on XY Plane");
//     digitalWrite(LED_PIN1, HIGH);
//   } else if (abs(mpu.GetGyroY()) > 800 && abs(mpu.GetGyroZ()) > 800) {
//     Serial.println("Spinning on YZ Plane");
//     digitalWrite(LED_PIN1, HIGH);
//   } else if (abs(mpu.GetGyroX()) > 800 && abs(mpu.GetGyroZ()) > 800) {
//     Serial.println("Spinning on XZ Plane");
//     digitalWrite(LED_PIN1, HIGH);
//   } else {
//     digitalWrite(LED_PIN1, LOW); // Turn off LED if no spinning detected
//   }


}

void setup() {
  pinMode(HALL_SENSOR_PIN, INPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  mpu.Initialize();
  
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");
}

void loop() {
    int sensorValue = digitalRead(HALL_SENSOR_PIN);
     int piezoValue = analogRead(piezoPin); // Read piezo sensor value
    //Serial.print("Piezo Sensor Value: ");
    //Serial.println(piezoValue);  
    //delay(300);
   int flexValue = analogRead(flexPin);   // Read flex sensor value
    //Serial.print("Flex Sensor Value: ");
    //Serial.println(flexValue); 
    //delay(300);
    digitalWrite(LED_PIN4, HIGH);

    if (piezoValue > threshold )//|| flexValue > flexThreshold) 
    {
    digitalWrite(LED_PIN3, HIGH);  // Turn on LED if either sensor value exceeds threshold
  } else {
    digitalWrite(LED_PIN3, LOW);   // Otherwise, turn off LED
  }
  
  if (sensorValue == HIGH) {
    //Serial.println("Pause");
    pause = "pause";
    digitalWrite(LED_PIN2, HIGH);
    //delay(300);
  } else {
    //Serial.println("Play");
    pause = "play";

    digitalWrite(LED_PIN2, LOW);
    //delay(300);
  }
  mpu.Execute();
  PrintGets();
  forPrint = intenseSpin + " " + pause;
  Serial.println(forPrint);
  delay(100);  // 0.1 sec delay
}