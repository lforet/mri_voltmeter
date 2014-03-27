/*
DC Voltmeter 
An Arduino DVM based on voltage divider concept
T.K.Hareendran
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int analogInput = 1;
int sensorPin = 1;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!
float value = 0;
int num_of_readings = 100;
int delay_per_reading = 2;

void setup(){
   pinMode(analogInput, INPUT);
   pinMode(sensorPin, INPUT);
   lcd.begin(16, 2);
   lcd.print("DC VOLTMETER");
   Serial.begin(115200);
}
void loop(){
   // read the value at analog input
   //value = analogRead(analogInput);
   value = read_sensor();
   vout = value * (5.0 / 1024.0); // see text
   vin = vout / (R2/(R1+R2)); 
   if ( (vin < 0.09) || (vin > 6.0) ) {
     vin=0.0;//statement to quash undesired reading !
   } 
   
  lcd.setCursor(0, 1);
  lcd.print("INPUT V= ");
  lcd.print(vin, 3);
  //if (Serial.available() > 0) {
    //Serial.println(vin, 3);
  //}
  //delay(250);
}

float read_sensor()
{
  int sum_of_readings = 0;
  float avg_reading = 0.0;
  int raw_value =0;
  for (int i= 0; i < num_of_readings; i++) {  
    raw_value = analogRead(sensorPin);
    //Serial.print("Raw:");
    //Serial.println(raw_value);
    sum_of_readings = sum_of_readings + raw_value;
    //Serial.print("sum_of_readings: ");
    //Serial.println(sum_of_readings);
    delay(delay_per_reading);
  }
  avg_reading = (sum_of_readings  /  num_of_readings);
  //Serial.print("avg:");
  //Serial.println(avg_reading, 3);
  return (avg_reading);
}
