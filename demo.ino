#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#define led 3;
#define buzzer 2;

// Declare variables to store gyro data
float xGyro, yGyro, zGyro;
float threshold;
void setup(void) {
  Serial.begin(115200);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Store gyro data in the variables
  threshold = g.gyro.x + g.gyro.y + g.gyro.z;

  while(threshold >= abs(0.35))
  {
    alarm();
  }


  xGyro = g.gyro.x;
  yGyro = g.gyro.y;
  zGyro = g.gyro.z;

  // Print temperature and acceleration data
  Serial.print("Accuracy:");
  Serial.print(threshold);
  Serial.print("\tTemperature:");
  Serial.print(temp.temperature);
  Serial.print("\tx-acceleration:");
  Serial.print(a.acceleration.x);
  Serial.print("\ty-acceleration:");
  Serial.print(a.acceleration.y);
  Serial.print("\tz-acceleration:");
  Serial.print(a.acceleration.z);
  
  Serial.print("\tx-gyro:");
  Serial.print(xGyro);
  Serial.print("\ty-gyro:");
  Serial.print(yGyro);
  Serial.print("\tz-gyro:");
  Serial.println(zGyro);

  delay(50);
}


void alarm()
{
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(100);
}
