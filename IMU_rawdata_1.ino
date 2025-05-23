#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>



/* This driver reads raw data from the BNO055

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(9600);

  while (!Serial) delay(10);  // wait for serial port to open!

  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{

  /* Display calibration status for each sensor. */
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  Serial.print("CALIBRATION: Sys=");
  Serial.print(system, DEC);
  Serial.print(" Gyro=");
  Serial.print(gyro, DEC);
  Serial.print(" Accel=");
  Serial.print(accel, DEC);
  Serial.print(" Mag=");
  Serial.println(mag, DEC);

  delay(BNO055_SAMPLERATE_DELAY_MS);
  delay(2000);
  
  if(system == 3 & gyro == 3 & mag == 3){
      Serial.println("Sensor is fully callibrated!!!");
      delay(1000);
      Serial.println("Loading data....");
      // Possible vector values can be:
      // - VECTOR_ACCELEROMETER - m/s^2
      // - VECTOR_MAGNETOMETER  - uT
      // - VECTOR_GYROSCOPE     - rad/s
      // - VECTOR_EULER         - degrees
      // - VECTOR_LINEARACCEL   - m/s^2
      // - VECTOR_GRAVITY       - m/s^2
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      imu::Vector<3> ACCEL = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
      imu::Vector<3> GYRO = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
      imu::Vector<3> MAGN = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
      imu::Vector<3> LINE_ACC = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
      imu::Vector<3> GRAVITY = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
        delay(2000);

      /* Display the floating point data */
      Serial.print("X: ");
      Serial.print(euler.x());
      Serial.print(" Y: ");
      Serial.print(euler.y());
      Serial.print(" Z: ");
      Serial.print(euler.z());
      Serial.print("\t\t");
      
      delay(1000);
      
      Serial.print("X: ");
      Serial.print(GYRO.x());
      Serial.print(" Y: ");
      Serial.print(GYRO.y());
      Serial.print(" Z: ");
      Serial.print(GYRO.z());
      Serial.print("\t\t");
      
      delay(1000);

      Serial.print("X: ");
      Serial.print(GRAVITY.x());
      Serial.print(" Y: ");
      Serial.print(GRAVITY.y());
      Serial.print(" Z: ");
      Serial.print(GRAVITY.z());
      Serial.print("\t\t");

      delay(1000);
      
      Serial.print("X: ");
      Serial.print(MAGN.x());
      Serial.print(" Y: ");
      Serial.print(MAGN.y());
      Serial.print(" Z: ");
      Serial.print(MAGN.z());
      Serial.print("\t\t");

       delay(1000);
       
      Serial.print("X: ");
      Serial.print(ACCEL.x());
      Serial.print(" Y: ");
      Serial.print(ACCEL.y());
      Serial.print(" Z: ");
      Serial.print(ACCEL.z());
      Serial.print("\t\t");

       delay(1000);

      Serial.print("X: ");
      Serial.print(MAGN.x());
      Serial.print(" Y: ");
      Serial.print(MAGN.y());
      Serial.print(" Z: ");
      Serial.print(MAGN.z());
      Serial.print("\t\t");

       delay(1000);
       
      Serial.print("X: ");
      Serial.print(LINE_ACC.x());
      Serial.print(" Y: ");
      Serial.print(LINE_ACC.y());
      Serial.print(" Z: ");
      Serial.print(LINE_ACC.z());
      Serial.print("\t\t");

      delay(1000);
      
      // Quaternion data
      imu::Quaternion quat = bno.getQuat();
      Serial.print("qW: ");
      Serial.print(quat.w(), 4);
      Serial.print(" qX: ");
      Serial.print(quat.x(), 4);
      Serial.print(" qY: ");
      Serial.print(quat.y(), 4);
      Serial.print(" qZ: ");
      Serial.print(quat.z(), 4);
      Serial.print("\t\t");
  }
}
