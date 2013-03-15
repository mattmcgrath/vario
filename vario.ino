
#include <Wire.h>
#include <BMP085.h>

const int N = 30; // Number of samples to average

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
  
  long Average_Altitude = 0;
  
  for(int i = 0; i < N; i++) {
   pressure_sensor.getAltitude(&Altitude);
   Average_Altitude = Average_Altitude + Altitude;
  }
  
  Average_Altitude = Average_Altitude / N;
  
  Serial.print(Time);
  Serial.print(",");
  Serial.println(Altitude);
}
