# Self Balancing Robot Project Files
## By The STEM Academy

### This site provides a place for you to access project files and code — free of charge!

If you have any questions, please visit our [5‑minute YouTube video](https://youtu.be/apsqejE4Z7I) and leave a comment.

---

## Required Hardware

You will need the following:

* 1× L298N motor driver  
* 1× ESP‑32 or similar board  
* 1× ~7 V battery (voltage is lost in the motor driver, but anything around this works)  
* 1× MPU‑6050  
* 2× DC gear motors (with wheels)  
* Loads of jumper wires  
* 2× 0.96" OLED displays*  
* 1× Perfboard PCB (or a breadboard — any method of connecting components is fine)

Fasteners:

* 4× ~30 mm M3 bolts + nuts (for the motors)**  
* 8–10× ~10–15 mm M3 bolts + nuts (for attaching components)**  
* 12× ~15 mm M3 wood screws (for attaching the 3D‑printed parts)**  

\* Optional, but a nice touch. If you’re not using OLEDs, make sure you use the correct wiring and code — details at the bottom of the page.  
\** Whatever screws work for you are fine. Glue is possible, but not recommended (explained in the video).

---

## Assembly

The assembly process is straightforward and only requires a few screws. If you don’t have them, superglue can be used as an alternative — though it’s not ideal. Feel free to make your own version out of wood or cardboard; I’d love to see what you come up with.

---

### The 3D Print

You’ll need a chassis for the robot. My preferred method is 3D printing, since it’s accessible and produces a rigid, strong frame. If you don’t have a 3D printer, you can build one from wood or cardboard.

The STL and Fusion 360 files are available free of charge:

- [Fusion 360 file](Self_Balancing_Robot_Fusion360.f3d)

For the STL files you will need:

* 2× [Motor Mounts](Motor_Mount.stl)  
* 1× [Layer 1](Layer_1.stl)  
* 1× [Layer 2](Layer_2.stl)  
* 1× [Layer 3](Layer_3.stl)  
* 1× [Layer 4](Layer_4.stl)

All parts fit on an Ender 3 Pro print bed with **no supports** at **0.12 mm layer height**.

<img src="IMG_0.png?raw=true" width="50%" alt="IMG0">

---

### Mounting the Motors

1. Add superglue to the rectangular divots on the bottom plate (1).  
2. Press the motor mounts (2) into place (I needed a hammer).  
3. Use ~30 mm M3 bolts (3) to secure the motors.  
4. Mount your battery in the centre — either with screws or glue.

It should look like this:

<img src="IMG_1.png?raw=true" width="50%" alt="IMG1">

---

### Logic Board

Next, make the main logic board for the robot. According to the correct schematic for your version, I left connections for the L298N and OLEDs as empty pin headers so I could attach jumper wires later (you can also use a breadboard).

<img src="Schematic.png?raw=true" width="50%" alt="Schematic">

---

### **IMPORTANT: MPU‑6050 Wiring**

#### If you are **NOT** using OLED displays:
* SDA → GPIO 21  
* SCL → GPIO 22  
* Motor driver pins remain the same  
* No pull‑up resistors required  

#### If you **ARE** using OLED displays:
* SDA → GPIO 32  
* SCL → GPIO 23  
* Add 4.7 kΩ pull‑up resistors from VCC to SDA and SCL (the second I²C bus has no internal pull‑ups)  
* If you’re unsure, a quick Google search will definitely help — it’s simple  

<img src="IMG_11.jpg?raw=true" width="15%" alt="IMG11">

I used a piece of perfboard and a small breadboard power supply, but you can also use the 5 V output from the L298N (explained in the video).

Here’s how mine looked (ignore the extra cables and USB‑C port — I broke the one on the ESP32):

<img src="IMG_2.png?raw=true" width="50%" alt="IMG2">

Attach your logic board to the second layer plate (4) using M3 bolts (5) or glue. Make sure the MPU‑6050 is level and the same orientation. If using screws, add standoffs (I 3D‑printed mine).

---

### The Motor Driver

Attach the L298N to the correct plate (6) in the orientation shown. Add jumper wires and route them through the hole. If using OLEDs, glue them to the front (7) and route their wires through the cable hole (8).

<img src="IMG_3.jpeg?raw=true" width="50%" alt="IMG3">

---

### Final Assembly

Use M3 × 15 mm wood screws (9) as shown below:

<img src="IMG_4.jpeg?raw=true" width="20%" alt="IMG4">

Attach the logic board plate to the motor base plate and route the motor wires upward:

<img src="IMG_5.png?raw=true" width="50%" alt="IMG5">

Connect the OLED and L298N wires to the logic board through the cable routing hole:

<img src="IMG_6.jpg?raw=true" width="50%" alt="IMG6">

Attach the top of the logic board layer and screw it down:

<img src="IMG_7.jpeg?raw=true" width="50%" alt="IMG7">

Connect the power and motor wires to the L298N:

<img src="IMG_8.jpeg?raw=true" width="50%" alt="IMG8">

Finally, screw on the top lid plate:

<img src="IMG_9.jpeg?raw=true" width="50%" alt="IMG9">

You have now built your self‑balancing robot. Time to upload the code.

---

## Code

### It is **VERY important** that you use the correct code variant:


| Web Server | OLEDs | Code varient                        |
|------------|--------|-------------------------------------|
| ✅         | ✅     | [STANDARD](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code.ino)                            |
| ✅         | ❌     | [WITHOUTOLEDS](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code_WITHOUTOLEDs.ino)                        |
| ❌         | ✅     | [WITHOUTWEBSERVER](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code_WITHOUTWEBSERVER.ino)                    |
| ❌         | ❌     | [WITHOUTWEBSERVER_AND_WITHOUTOLEDS](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code_WITHOUTWEBSERVER_AND_WITHOUTOLEDS.ino)  |


## Setup With the WiFi Server

When the code runs, the ESP32 will broadcast a WiFi network named **“Self Balancing Robot Tuner”** with password **12345678**.

Connect to it, open a browser, and go to:
192.168.4.1


You can fine‑tune PID values over WiFi. Once you find ideal values, switch to the **non‑web‑server** code variant and enter your P, I, and D constants manually.

If using OLEDs, install the [RoboEyes library](https://github.com/FluxGarage/RoboEyes).

---

## Setup Without the WiFi Server

You will need to manually adjust the P, I, and D constants in the code and re‑upload until the robot balances.  
Install the RoboEyes library if using OLEDs.

---

## Final Notes

Thank you for visiting this page. I hope you enjoy your build, and don’t get too disheartened if it doesn’t balance straight away — PID tuning takes time (I spent days on it). If you get stuck, check the video, and if you’re still unsure, feel free to leave a comment.

Many thanks,  
**The STEM Academy**
