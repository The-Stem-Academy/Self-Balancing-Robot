# Self Balancing Robot Project Files
## By The STEM Academy

### This site provides a place for you to access project files and code - free of charge!

If you have any questions please visit our [5-minute Youtube Guide](https://youtu.be/3z8Bph11x7s) and we encourage you to comment :)

## Required Hardware
You will need the following:  

* 1x L298N motor driver  
* 1x ESP-32 or similar board  
* 1x 7 ish volt battery since voltage is lost in the motor driver but whatever works for you is fine  
* 1x MPU 6050  
* 2x DC gear motors (with weels)  
* Loads of wires  
* 2x 0.96 OLED displays*  
* 1x Perfboard PCB (you can use a breadboard or whatever method you wish to connect the components)  

## Assembly
The assembly process is relatively straightforward and requires a handful of different screws. If you don’t have them, superglue can be used as an alternative—though it’s not ideal, for reasons I explain in the YouTube guide. Feel free to make your own version out of wood or cardboard, I’d love to see what you come up with.
[File](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_WITHOLED_Code.ino)

### Mounting the motors
First you must put some superglue in the small rectangular divots on the bottom plate (1) (be generous with the glue here). Then place the rectangular motor mounts (2) into those holes (I needed to use a hammer). Then using (~130mm M3 screws and bolts) screw the motors to the mounts. Then mount your battery to the middle of the bottom plate (you could drill holes for screws for your battery or just glue it tight). 
It should look something like this: 

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_1.png?raw=true" width="50%" style="" alt="Mounting the Motors">

### Logic Board
Next we make the main logic board for the robot. According to this schematic, I left connections for the L298N and OLEDs as empty pin headers so that I can attach jumper wires too later (but you could use a breadboard).

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Schematic_Wiring_Image.jpg?raw=true" width="50%" style="" alt="Mounting the Motors">


I use a piece of perfboard and some random breadboard power supply but you could probably use the 5v from the L298N (details about this are in the video).

This is how mine looked (Ignore the extra cables and USB-C port – I broke the one on the ESP32):

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_2.png?raw=true" width="50%" style="" alt="Mounting the Motors">

You can then attach your logic board to the second layer plate. (3) through the use of M3 screws or just glue. Make sure the MPU605 is horizontally level and if you are screwing use stand offs (I 3D printed mine)


### The motor driver
Attach the L298N to the third plate (4) in the orientation shown in the image and attach some jumper wires to the corresponding parts on the L298N and route through the hole., also you can attach jumper wires to both OLEDs and using hot glue attach them to the front of the board and run the wires through the cable routing hole also shown bellow:

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_3.jpeg?raw=true" width="50%" style="" alt="Mounting the Motors">

### Final assembly
Using some M3 * 15mm wood screws as shown bellow:

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_4.jpeg?raw=true" width="20%" style="" alt="Mounting the Motors">

Screw your logic board plate onto the motor base plate and make sure you route the motor wires up to the logic board as you can see next to both motors in the image.

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_5.png?raw=true" width="50%" style="" alt="Mounting the Motors">


## Code
The code will broadcast a WIFI network from your ESP-32 called "Self Balancing Robot Tuner" with the password "12345678" if you connect to this network on any device and go to your web browser and enter "192.168.4.1" to the search bar you will be able to fine tune many values for your robot, over WIFI which will streamline the PID tuning process. Once you have found ideal values you can enter them manually in the code as constants (lines 28 to 38) and then start the robot and just ignore the network. You will also need to install the [roboEyes library](https://github.com/FluxGarage/RoboEyes)

## Final notes
Thank you for visiting this page; this is a 3/5** difficulty project so be patient and have fun building  


##  
(*)This one is optional but a nice touch   




