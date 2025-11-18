# Self Balancing Robot Project Files
## By The STEM Academy

### This site provides a place for you to access project files and code - free of charge!

If you have any questions please visit our [5-minute Youtube Video](https://youtu.be/3z8Bph11x7s) and leave a comment

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

* 4x ~300mm M3 bolts and their corresponding nuts (for the motors)**
* 8-10x ~1-1.5mm M3 bolts and their corresponding nuts (for attaching various components)**
* 12x ~15mm M3 wood screws (for attaching each 3d printed part)**

(*)This one is optional but a nice touch if your not going to use them make sure you get the correct code and wiring, there are more IMPORTANT details about this at the bottom of the page. <br>
(**)Whatever screws work for you, maybe even glue but I wouldn't advice that (its covered in the video)

## Assembly
The assembly process is relatively straightforward and requires a handful of different screws. If you don’t have them, superglue can be used as an alternative—though it’s not ideal, for reasons I explain in the YouTube guide. Feel free to make your own version out of wood or cardboard, I’d love to see what you come up with.

### The 3D print
You will need some sort of chassis for the robot, my preferred method is 3D printing since it is accessible for me and provides a rigid and strong chassis. If you don't have a 3D printer you could try making something out of wood or cardboard – I would be interested to see what you made.

The STL and Fusion360 files are available free of charge:
[Fusion360 file](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Fusion360.f3d)

For the STL you will need:
* 2x [Motor mounts](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Motor_Mount.stl)
* 1x [Layer 1](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Layer_1.stl)
* 1x [Layer 2](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Layer_2.stl)
* 1x [Layer 3](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Layer_3.stl)
* 1x [Layer 4](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Layer_4.stl) \
I was able to fit them all on one print bed on my ender 3 pro so with NO SUPPORTS and a 0.12mm layer height but everything should work, its pretty simple to print.

<img src="IMG_0.png?raw=true" width="50%" style="" alt="IMG0">

### Mounting the motors
First you must put some superglue in the small rectangular divots on the bottom plate (1) (be generous with the glue here). Then place the rectangular motor mounts (2) into those holes (I needed to use a hammer). Then using (~300mm M3 nuts and bolts(3)) screw the motors to the mounts. Then mount your battery to the middle of the bottom plate (you could drill holes for screws for your battery or just glue it tight). 
It should look something like this: 

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_1.png?raw=true" width="50%" style="" alt="IMG1">

### Logic Board
Next we make the main logic board for the robot. According to this schematic, I left connections for the L298N and OLEDs as empty pin headers so that I can attach jumper wires too later (but you could use a breadboard).

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Schematic_Wiring_Image.jpg?raw=true" width="50%" style="" alt="Scematic">


I use a piece of perfboard and some random breadboard power supply but you could probably use the 5v from the L298N (details about this are in the video).

This is how mine looked (Ignore the extra cables and USB-C port – I broke the one on the ESP32):

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_2.png?raw=true" width="50%" style="" alt="IMG2">

You can then attach your logic board to the second layer plate. (4) through the use of M3 nuts and bolts (5) or just glue. Make sure the MPU605 is horizontally level and if you are screwing use stand offs (I 3D printed mine)


### The motor driver
Attach the L298N to the correct plate (6) in the orientation shown in the image and attach some jumper wires to the corresponding parts on the L298N and route through the hole., also you can attach jumper wires to both OLEDs and using hot glue attach them to the front of the board (7) and run the wires through the cable routing hole (8) also shown bellow:

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_3.jpeg?raw=true" width="50%" style="" alt="IMG3">

### Final assembly
Using some M3 * 15mm wood screws (9) as shown bellow:

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_4.jpeg?raw=true" width="20%" style="" alt="IMG4">

Screw your logic board plate onto the motor base plate and make sure you route the motor wires up to the logic board as you can see next to both motors in the image.

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_5.png?raw=true" width="50%" style="" alt="IMG5">

Connect the routed jumper wired from the OLEDs and L298N from the previous step to the corresponding connections on the logic board through the cable routing hole and the motor wires and any power cables to the L298N as demonstrated below.

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_6.jpg?raw=true" width="50%" style="" alt="IMG6">

Next push that part onto the top of the logic board layer and screw it down, this might be a bit fiddly but it should end up illustrated as below.

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_7.jpeg?raw=true" width="50%" style="" alt="IMG7">

Then connect the power and motor wires to the L298N

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_8.jpeg?raw=true" width="50%" style="" alt="IMG8">

Finally screw on the top lid plate

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/IMG_9.jpeg?raw=true" width="50%" style="" alt="IMG9">

## You have now made your self balancing robot. Time upload the code.

## Code

There are a few variations of the code and it is **VERY important** that you use the correct one:

* If you **DO want the web server** for PID tuning AND you **DO want OLEDs** then choose the [STANDARD varient](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code.ino)
* If you **DO want the web server** for PID tuning AND you **DO NOT want OLEDs** then choose the [WITHOUTOLEDS varient](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code_WITHOUTOLEDs.ino)
* If you are using a non wifi enabled board or you just **don't want the web server** for PID tuning but you **DO want OLED displays** the coose the [WITHOUTWEBSERVER varient](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code_WITHOUTWEBSERVER.ino)
* If you are using a non wifi enabld board or you just **don't want the web server** for PID tuning but you **DO NOT want OLED displays** then choose the [WITHOUTWEBSERVER_AND_WITHOUTOLEDS varient](https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Self_Balancing_Robot_Code_WITHOUTWEBSERVER_AND_WITHOUTOLEDS.ino)


Upon running the code a WIFI network will be broadcasted from your ESP32 named “Self Balancing Robot Tuner” with the password “12345678” if you connect to this network on any device and go to your web browser and enter "192.168.4.1" to the search bar you will be able to fine tune many values for your robot, over WIFI which will streamline the PID tuning process. Once you have found ideal values you can enter them manually in the code as constants (lines 28 to 38) and then start the robot and just ignore the network. You will also need to install the [roboEyes library](https://github.com/FluxGarage/RoboEyes)

## Final notes
Thank you for visiting this page, I hope you enjoy your build, and don't get too disheartened when it doesn't balance straight away after uploading the code (I spent days tuning). If you get stuck just check out the video and if you're still not sure feel free to leave a comment.

Many thanks,
The STEM Academy 




