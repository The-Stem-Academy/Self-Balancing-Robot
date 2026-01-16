#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <FluxGarage_RoboEyes.h>

// OLEDs
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

roboEyes roboEyes;

// Mpu6050
TwoWire I2CMPU = TwoWire(1);
Adafruit_MPU6050 mpu;

// Motor
const int ENA = 23, IN1 = 25, IN2 = 26;
const int ENB = 18, IN3 = 27, IN4 = 4;
const int PWM_FREQ = 1000, PWM_RES = 8;

// Pid constants
float setpoint = 0.0;
float Kp = 14.0;
float Ki = 0.0;
float Kd = 1.2;

float integral = 0.0;
float angleDeg = 0.0;
float gyroRateDeg = 0.0;
float lastOutput = 0.0;

float powerMultiplier = 1.0;
int minPWM = 80;
float tiltGain = 1.0;

unsigned long lastMicrosTs = 0;

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while (1);
  display.setRotation(2);
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Self Balancing Robot"));

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(F("Please Hold Upright"));

  display.setCursor(0, 30);
  display.println(F("Robot Will Start Soon"));
  display.display();
  delay(3000);

  display.clearDisplay();
  display.display();

  // RoboEyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
  roboEyes.setCyclops(ON);
  roboEyes.setAutoblinker(ON, 2, 3);
  roboEyes.setIdleMode(ON, 3, 2);

  // MPU6050 start
  I2CMPU.begin(32, 33, 400000);
  if (!mpu.begin(0x68, &I2CMPU)) while (1);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Motors start
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);

  lastMicrosTs = micros();
}

void loop() {
  roboEyes.update();

  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicrosTs) / 1e6f;
  if (dt <= 0) dt = 0.001f;
  lastMicrosTs = nowUs;

  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  float accelAngleDeg = -atan2(a.acceleration.x, a.acceleration.z) * 180.0f / PI;
  gyroRateDeg = g.gyro.y * (180.0f / PI);

  // Complementary filter
  angleDeg = 0.98f * (angleDeg + gyroRateDeg * dt) + 0.02f * accelAngleDeg;

  // PID
  float error = setpoint - angleDeg;
  integral += error * dt;
  lastOutput = (Kp * error + Ki * integral - Kd * gyroRateDeg) * tiltGain;

  driveMotors(lastOutput);
}

void driveMotors(float cmd) {
  float boostedCmd = cmd * powerMultiplier;
  if (fabsf(boostedCmd) < 80) boostedCmd *= 1.5;

  int pwm = constrain((int)fabsf(boostedCmd), 0, 255);
  if (pwm > 0 && pwm < minPWM) pwm = minPWM;

  if (boostedCmd > 0) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (boostedCmd < 0) {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  }

  ledcWrite(ENA, pwm);
  ledcWrite(ENB, pwm);
}
