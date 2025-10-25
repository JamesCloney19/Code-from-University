#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

Adafruit_MPU6050 mpu;

BleMouse bleMouse("ESP32 Air Mouse", "Your Name", 100);

// Sensitivity multiplier - adjust these to change mouse speed
float SENSITIVITY_X = 3.0;
float SENSITIVITY_Y = 3.0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32 BLE Mouse");

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Configure MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Start BLE Mouse
  bleMouse.begin();
  Serial.println("Bluetooth mouse started. Waiting for connection...");
}

void loop() {
  // Check if BLE mouse is connected
  if (bleMouse.isConnected()) {
    // Get sensor readings
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Calculate mouse movement from gyroscope data
    // Gyro gives rotation rate in radians/sec
    int moveX = (int)(g.gyro.y * SENSITIVITY_X);  // Tilt left/right
    int moveY = (int)(g.gyro.x * SENSITIVITY_Y);  // Tilt forward/back

    // Only move if there's significant movement (reduces jitter)
    if (abs(moveX) > 1 || abs(moveY) > 1) {
      bleMouse.move(moveX, moveY);
    }

    // Debug output
    Serial.print("X: "); Serial.print(moveX);
    Serial.print(" Y: "); Serial.println(moveY);
  } else {
    Serial.println("Waiting for BLE connection...");
  }

  delay(10);  // 100Hz update rate
}
