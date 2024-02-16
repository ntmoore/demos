/* 
This code runs an Arduino circuit that acts like an arcade/Chuck-E-Cheese style 
"Love Meter".  sensor input is the voltage from an LM34 temperature sensor, output
is a bank of 4 LED's.  As the sensor temp increases, the LED's rise (through eg RGB 
style pattern).

Sensor data is also sent to Serial cable.

Nathan Moore 2024-02-16
*/

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.print(sensorValue);
  float voltage_mV = 5000 * (sensorValue / 1023.0);
  Serial.print("\t");
  Serial.print(voltage_mV);
  // LM34 is 10mV/F = 0.010 V/F 
  // or scale factor(1F/10mV)
  float t_f = voltage_mV / 10;
  Serial.print("\t");
  Serial.println(t_f);

  delay(1000);

  // Love-meter loop

  if (t_f < 80) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  if (t_f > 80 and t_f < 85) {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  if (t_f > 85 and t_f < 90) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  // fingertips are not generally very hot
  if (t_f > 90) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(7, HIGH);
  }
}
