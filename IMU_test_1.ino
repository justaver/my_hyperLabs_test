#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);
/**************************************************************************/
/*
    Display sensor calibration status
*/
/**************************************************************************/
void displayCalStatus(void)
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print("\t");
  if (!system)
  {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.println(mag, DEC);

}

float xOffset = 0, yOffset = 0, zOffset = 0;

void setup() {
  Serial.begin(9600);
  if (!bno.begin()) {
    Serial.println("BNO055 not detected!");
    while (1);
  }

  delay(1000);
  bno.setExtCrystalUse(true);

  // Get current orientation and store as offsets
  sensors_event_t event;
  bno.getEvent(&event);
  xOffset = event.orientation.x;
  yOffset = event.orientation.y;
  zOffset = event.orientation.z;
}

void loop() {
 
  displayCalStatus();
  delay(2000);
  
  
  
  sensors_event_t event;
  bno.getEvent(&event);

  float x = event.orientation.x - xOffset;
  float y = event.orientation.y - yOffset;
  float z = event.orientation.z - zOffset;

  Serial.print("X: "); Serial.print(x);
  Serial.print("\tY: "); Serial.print(y);
  Serial.print("\tZ: "); Serial.println(z);

  Serial.println("YEAH! I'm positioned at zero.");
  delay(500);
  

  
}
