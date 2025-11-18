#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// MPU6050
Adafruit_MPU6050 mpu;

// Motor Pins
const int ENA = 23, IN1 = 25, IN2 = 26;
const int ENB = 18, IN3 = 27, IN4 = 4;
const int PWM_FREQ = 1000, PWM_RES = 8;

// PID constants
float setpoint = 0.0;
float Kp = 14.0, Ki = 0.0, Kd = 1.2;
float integral = 0.0;
float angleDeg = 0.0;
float gyroRateDeg = 0.0;
float lastOutput = 0.0;
float powerMultiplier = 1.0;
int minPWM = 80;
float tiltGain = 1.0;
unsigned long lastMicrosTs = 0;

// Wifi setup
WebServer server(80);
const char* ssid = "Self Balancing Robot Tuner";
const char* password = "12345678";

// Webpage
const char* html = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="UTF-8"><title>PID Tuner</title>
<style>body{font-family:sans-serif;text-align:center;}input{width:80px;}</style></head>
<body><h2>Self Balancing Robot PID Tuner</h2>
<form onsubmit="send();return false;">
Kp: <input id="kp" type="number" step="any" value="14.0"><br>
Ki: <input id="ki" type="number" step="any" value="0.0"><br>
Kd: <input id="kd" type="number" step="any" value="1.2"><br>
Setpoint: <input id="sp" type="number" step="any" value="0.0"><br>
Power Multiplier: <input id="pm" type="number" step="any" value="1.0"><br>
Min PWM: <input id="mpwm" type="number" step="any" value="80"><br>
Tilt Gain: <input id="tg" type="number" step="any" value="1.0"><br><br>
<button type="submit">Send</button></form><br>
<div id="telemetry">Waiting for data...</div>
<script>
function send(){
  let url = `/set?kp=${kp.value}&ki=${ki.value}&kd=${kd.value}&sp=${sp.value}&pm=${pm.value}&mpwm=${mpwm.value}&tg=${tg.value}`;
  fetch(url).then(r=>r.text()).then(t=>console.log(t));
}
setInterval(()=>fetch("/telemetry").then(r=>r.text()).then(t=>telemetry.innerText=t), 100);
</script></body></html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  // begin i2c
  Wire.begin();  // SDA/SCL on ESP32 defaults (GPIO21 / GPIO22)

  if (!mpu.begin(0x68)) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // motor
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);

  // Wifi AP
  WiFi.softAP(ssid, password);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // web routes
  server.on("/", [](){ server.send(200, "text/html", html); });

  server.on("/set", [](){
    if (server.hasArg("kp")) Kp = server.arg("kp").toFloat();
    if (server.hasArg("ki")) Ki = server.arg("ki").toFloat();
    if (server.hasArg("kd")) Kd = server.arg("kd").toFloat();
    if (server.hasArg("sp")) setpoint = server.arg("sp").toFloat();
    if (server.hasArg("pm")) powerMultiplier = server.arg("pm").toFloat();
    if (server.hasArg("mpwm")) minPWM = server.arg("mpwm").toInt();
    if (server.hasArg("tg")) tiltGain = server.arg("tg").toFloat();
    server.send(200, "text/plain", "OK");
  });

  server.on("/telemetry", [](){
    String out = "Angle: " + String(angleDeg, 2);
    out += " | Gyro: " + String(gyroRateDeg, 2);
    out += " | Output: " + String(lastOutput, 2);
    out += " | PowerMult: " + String(powerMultiplier, 2);
    out += " | MinPWM: " + String(minPWM);
    out += " | TiltGain: " + String(tiltGain, 2);
    server.send(200, "text/plain", out);
  });

  server.begin();

  lastMicrosTs = micros();
}

void loop() {
  server.handleClient();

  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicrosTs) / 1e6f;
  if (dt <= 0) dt = 0.001f;
  lastMicrosTs = nowUs;

  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  float accelAngleDeg = -atan2(a.acceleration.x, a.acceleration.z) * 180.0f / PI;
  gyroRateDeg = g.gyro.y * (180.0f / PI);

  // Complementary filter (98% gyro, 2% accel)
  angleDeg = 0.98f * (angleDeg + gyroRateDeg * dt) + 0.02f * accelAngleDeg;

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
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (boostedCmd < 0) {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  }

  ledcWrite(ENA, pwm);
  ledcWrite(ENB, pwm);
}
