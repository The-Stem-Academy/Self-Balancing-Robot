#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// Oled definitions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <FluxGarage_RoboEyes.h>

// Create RoboEyes instance
roboEyes roboEyes;

// MPU 6050 on second I2C bus
TwoWire I2CMPU = TwoWire(1);
Adafruit_MPU6050 mpu;

// Motor pins
const int ENA = 23;
const int IN1 = 25;
const int IN2 = 26;
const int ENB = 18;
const int IN3 = 27;
const int IN4 = 4;

// PWM setting
const int PWM_FREQ = 1000;
const int PWM_RES  = 8;

// PID constants
float setpoint = 0.0;
float Kp = 55, Ki = 0.8, Kd = 0.01;
float lastError = 0.0, integral = 0.0;
float angleDeg = 0.0;
unsigned long lastMicrosTs = 0;

void setup() {
  Serial.begin(115200);

  // Init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Boot splash
  display.setRotation(2);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Booting.."));

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(F("Please hold robot"));
  display.setCursor(0, 30);
  display.println(F("upright"));

  display.display();
  delay(3000);

    // Clear oled and start RoboEyes
  display.clearDisplay();
  display.display();

  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
  roboEyes.setCyclops(ON);
  roboEyes.setAutoblinker(ON, 2, 3);
  roboEyes.setIdleMode(ON, 3, 2);

    // Init MPU6050 on pins 32/33
  I2CMPU.begin(32, 33, 400000);
  if (!mpu.begin(0x68, &I2CMPU)) {
    Serial.println("MPU6050 not found!");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    // --- Init motors ---
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);

  lastMicrosTs = micros();
}

void loop() {
  // Update RoboEyes
  roboEyes.update();

  // Balancing
  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicrosTs) / 1e6f;
  if (dt <= 0) dt = 0.001f;
  lastMicrosTs = nowUs;

  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  // Forward/back pitch
  float accelAngleDeg = -atan2(a.acceleration.x, a.acceleration.z) * 180.0f / PI;
  float gyroRateDeg   = g.gyro.y * (180.0f / PI);

  // Complementary filter
  angleDeg = 0.98f * (angleDeg + gyroRateDeg * dt) + 0.02f * accelAngleDeg;

  // PID control
  float error = setpoint - angleDeg;
  integral += error * dt;
  float derivative = (error - lastError) / dt;
  float output = Kp * error + Ki * integral + Kd * derivative;
  lastError = error;

  driveMotors(output);
}

void driveMotors(float cmd) {
  int pwm = constrain((int)fabsf(cmd), 0, 255);
  if (pwm > 0 && pwm < 30) pwm = 30; // overcome stiction

  if (cmd > 0) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (cmd < 0) {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);
  }

  ledcWrite(ENA, pwm);
  ledcWrite(ENB, pwm);
}
