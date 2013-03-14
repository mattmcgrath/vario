
#include <Wire.h>
#include <BMP085.h>


long Time = 0;

BMP085 pressure_sensor = BMP085(); // Create an instance of the BMP085 digital pressure sensor

long Temperature = 0, Pressure = 0, Altitude = 0; // State variables for pressure sensor

void setup(void) {
  Serial.begin(9600);
  Wire.begin();
  delay(1000);

  pressure_sensor.init(MODE_ULTRA_HIGHRES, 101850, false);  // Initialize in highest resolution mode at standard pressure.
}            

void loop(void) {
  Time = millis(); 
  pressure_sensor.getAltitude(&Altitude);
  Serial.print(Time);
  Serial.print(",");
  Serial.println(Altitude);
}
