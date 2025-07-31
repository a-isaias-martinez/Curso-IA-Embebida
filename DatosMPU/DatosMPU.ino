#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

#define CONVERT_G_TO_MS2    1.0f
#define MAX_ACCEPTED_RANGE  25.0f  


const float accelerationThreshold = 20; 
const int numSamples = 200;

int samplesRead = numSamples;

void setup() {
  Serial.begin(115200);
  while (!Serial);

      while (!Serial);
    delay(10); 

  Serial.println("Adafruit MPU6050");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Fallo en encontrar el MPU6050");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 encontrado");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Rango de aceleracion en: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Rango de giro en: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filtro pasabandas en: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
  
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;
  
  while (samplesRead == numSamples) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

  aX=a.acceleration.x;
  aY=a.acceleration.y;
  aZ=a.acceleration.z; 
  gX=g.gyro.x;
  gY=g.gyro.y;
  gZ=g.gyro.z;
 // delay(50);

      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      if (aSum >= accelerationThreshold) {

        samplesRead = 0;
        break;
      } 
  
  } 

  while (samplesRead < numSamples) {

     sensors_event_t a, g, temp;
     mpu.getEvent(&a, &g, &temp);
     aX=a.acceleration.x;
     aY=a.acceleration.y;
     aZ=a.acceleration.z; 
     gX=g.gyro.x;
     gY=g.gyro.y;
     gZ=g.gyro.z;
     
     samplesRead++;

      // Formato CSV
      Serial.print(aX, 3);
      Serial.print(',');
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(',');
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();

      if (samplesRead == numSamples) {
        Serial.println();
      }
  }
}
