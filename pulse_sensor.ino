/* this doesn't work yet! */
/*
reading pulse from Adafruit Pulse sensor
https://www.adafruit.com/product/1093

Nathan Moore
Winona State Physics, 2024-04-10

*/

int sensorPin = A0;
int s, sum, avg_sensor_reading;
float seconds_per_beat;
float beats_per_minute;
int s0, s1, s2;
int t0, t1, t2;
int slope1, slope2;
int old_peak_time, new_peak_time;

void setup() {
  Serial.begin(9600);
  Serial.println("put your finger on the sensor");
  delay(1000);
  Serial.println("sensor setup");
  // Find the average value from the sensor
  sum = 0;
  for (int i = 0; i < 10; i++) {
    s0 = (int)analogRead(sensorPin);
    sum = sum + s0;
    Serial.print(s0);
    Serial.print("\t");
    Serial.print(sum);
    Serial.println("\t");
    delay(200);
  }
  avg_sensor_reading = sum / 10;
  Serial.print("avg analog input is ");
  Serial.println(avg_sensor_reading);

  // read sensor
  s0 = analogRead(sensorPin);
  t0 = millis();
  //Serial.println(s);
  delay(50);

  // read sensor
  s1 = analogRead(sensorPin);
  t1 = millis();
  //Serial.println(s);
  delay(50);

  s2 = analogRead(sensorPin);
  t2 = millis();
  //Serial.println(s);
  delay(50);

  //slope1 = (s1 - s0) / (t1 - t0);
  //slope2 = (s2 - s1) / (t2 - t1);
  // make this an integer change instead
  slope1 = (s1 - s0);
  slope2 = (s2 - s1);

  Serial.print(t0);
  Serial.print('\t');
  Serial.print(s0);
  Serial.println('\t');

  Serial.print(t1);
  Serial.print('\t');
  Serial.print(s1);
  Serial.println('\t');

  Serial.print(t2);
  Serial.print('\t');
  Serial.print(s2);
  Serial.println('\t');

  Serial.println(slope1);
  Serial.println(slope2);
  delay(10000);
}

void loop() {

  // recycle old values
  //t2 is the newest, t0 is the oldest
  s0 = s1;
  t0 = t1;
  s1 = s2;
  t1 = t2;

  // read sensor
  s2 = analogRead(sensorPin);
  t2 = millis();
  //Serial.println(s);
  delay(50);

  //  slope1 = (s1 - s0) / (t1 - t0);
  //  slope2 = (s2 - s1) / (t2 - t1);
  // make this an integer change instead
  slope1 = (s1 - s0);
  slope2 = (s2 - s1);

  if (slope1 > 0 && slope2 < 0 && s1 > avg_sensor_reading) {
    // then a peak has been found.
    old_peak_time = new_peak_time;
    new_peak_time = t2;
    seconds_per_beat = (new_peak_time - old_peak_time) / 1000.0;
    beats_per_minute = 60 / seconds_per_beat;
  }
  Serial.print(old_peak_time);
  Serial.print("\t");
  Serial.print(new_peak_time);
  Serial.print("\t");
  Serial.print(seconds_per_beat);
  Serial.print("\t");
  Serial.println(beats_per_minute);
}
