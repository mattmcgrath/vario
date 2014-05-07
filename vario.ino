
#include <Wire.h>
#include <BMP085.h>

const int N = 30; // Number of samples to average
static long k[N]; //array storing data for moving average

long Time = 0;

BMP085 pressure_sensor = BMP085(); // Create an instance of the BMP085 digital pressure sensor

long Temperature = 0, Pressure = 0, Altitude = 0; // State variables for pressure sensor

static long filter(long input);
static long filter(long input) {
  long sum = 0;
	
  for (int i = 0; i < N; i++) {
    k[i] = k[i+1];
  }

  k[N - 1] = input;

  for (int i = 0; i < N; i++) {
    sum += k[i];
  }
  
  return ( sum / N );
}

////////////
// SETUP //
///////////

void setup(void) {
  Serial.begin(57600);
  Wire.begin();
  delay(1000);
  pressure_sensor.init(MODE_ULTRA_HIGHRES, 101850, false);  // Initialize in highest resolution mode at standard pressure.
}            

////////////////
// MAIN LOOP //
///////////////

void loop(void) {
  Time = millis();
  
  // Get five readings before sending; this means the moving average will be sent after every fifth reading.
  for(int i = 0; i < 5; i++) {
   pressure_sensor.getAltitude(&Altitude);
   Altitude = filter(Altitude);
  }
  
  // Print to serial console in CSV format.
  // If xBee is connected, this will be echoed to the base station.
  Serial.print(Time);
  Serial.print(",");
  Serial.println(Altitude);
}
