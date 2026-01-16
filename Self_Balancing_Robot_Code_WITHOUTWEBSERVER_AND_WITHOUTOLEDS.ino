//MIT License

//Copyright (c) 2026 How To STEM

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// MPU 6050
Adafruit_MPU6050 mpu;

// Motor
const int ENA = 23, IN1 = 25, IN2 = 26;
const int ENB = 18, IN3 = 27, IN4 = 4;
const int PWM_FREQ = 1000, PWM_RES = 8;

// PID CONSTANTS (this is the bit where you put the details from your website testing
float Kp = 14.0;
float Ki = 0.0;
float Kd = 1.2;

float setpoint = 0.0;
float powerMultiplier = 1.0;
int minPWM = 80;
float tiltGain = 1.0;

// Control states
float integral = 0.0;
float angleDeg = 0.0;
float gyroRateDeg = 0.0;
float lastOutput = 0.0;
unsigned long lastMicrosTs = 0;

void setup() {
  Serial.begin(115200);

  //I2c
  Wire.begin();

  if (!mpu.begin(0x68)) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // motors start
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);

  lastMicrosTs = micros();
}

void loop() {
  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicrosTs) / 1e6f;
  if (dt <= 0) dt = 0.001f;
  lastMicrosTs = nowUs;

  mpu.getEvent(&a, &g, &t);

  float accelAngleDeg = -atan2(a.acceleration.x, a.acceleration.z) * 180.0f / PI;
  gyroRateDeg = g.gyro.y * (180.0f / PI);

  // complementary filter
  angleDeg = 0.98f * (angleDeg + gyroRateDeg * dt) + 0.02f * accelAngleDeg;

  // PID
  float error = setpoint - angleDeg;
  integral += error * dt;

  lastOutput = (Kp * error + Ki * integral - Kd * gyroRateDeg) * tiltGain;

  driveMotors(lastOutput);
}

void driveMotors(float cmd) {
  float boostedCmd = cmd * powerMultiplier;

  if (fabsf(boostedCmd) < 80)
    boostedCmd *= 1.5;

  int pwm = constrain((int)fabsf(boostedCmd), 0, 255);
  if (pwm > 0 && pwm < minPWM) pwm = minPWM;

  if (boostedCmd > 0) {
    // forward
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (boostedCmd < 0) {
    // backward
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  } else {
    // stop
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  }

  ledcWrite(ENA, pwm);
  ledcWrite(ENB, pwm);
}
