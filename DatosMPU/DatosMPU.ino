//////////// Librerias //////////////////
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

//////////// Constantes //////////////////

const float umbralAceleracion = 20; 
const int numMuestras = 225;
int muestrasLeidas = numMuestras;



void setup() {
  Serial.begin(115200);
  while (!Serial);

      while (!Serial);
    delay(10); 

  Serial.println("Adafruit MPU6050");

  if (!mpu.begin()) {
    Serial.println("Fallo en encontrar el MPU6050");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 encontrado");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  /* Rangos del acelerometro disponibles
  MPU6050_RANGE_2_G
  MPU6050_RANGE_4_G
  MPU6050_RANGE_8_G
  MPU6050_RANGE_16_G
  */
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  /* Rangos del giroscopio disponibles
  MPU6050_RANGE_250_DEG
  MPU6050_RANGE_500_DEG
  MPU6050_RANGE_1000_DEG
  MPU6050_RANGE_2000_DEG
  */

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  /* Rangos del giroscopio disponibles
  MPU6050_BAND_5_HZ
  MPU6050_BAND_10_HZ
  MPU6050_BAND_21_HZ
  MPU6050_BAND_44_HZ
  MPU6050_BAND_94_HZ
  MPU6050_BAND_184_HZ
  MPU6050_BAND_260_HZ
  */
  Serial.println("");
  delay(100);
  
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;
  
  while (muestrasLeidas == numMuestras) {
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

        if (aSum >= umbralAceleracion) {
          muestrasLeidas = 0;
          break;
      } 
  
  } 

  while (muestrasLeidas < numMuestras) {

     sensors_event_t a, g, temp;
     mpu.getEvent(&a, &g, &temp);
     aX=a.acceleration.x;
     aY=a.acceleration.y;
     aZ=a.acceleration.z; 
     gX=g.gyro.x;
     gY=g.gyro.y;
     gZ=g.gyro.z;
     
     muestrasLeidas++;

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

      if (muestrasLeidas == numMuestras) {
        Serial.println("");
      }
  }
}
