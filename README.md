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

### Mounting the motors
First you must put some superglue in the small rectangular divots on the bottom plate (1) (be generous with the glue here). Then place the rectangular motor mounts (2) into those holes (I needed to use a hammer). Then using (~130mm M3 screws and bolts) screw the motors to the mounts. Then mount your battery to the middle of the bottom plate (you could drill holes for screws for your battery or just glue it tight). 
It should look something like this: 

<img src="https://github.com/The-Stem-Academy/Self-Balancing-Robot/blob/main/Mounting_The_Motors_IMG.png?raw=true" width="50%" style="" alt="Mounting the Motors">

## Code
The code will broadcast a WIFI network from your ESP-32 called "Self Balancing Robot Tuner" with the password "12345678" if you connect to this network on any device and go to your web browser and enter "192.168.4.1" to the search bar you will be able to fine tune many values for your robot, over WIFI which will streamline the PID tuning process. Once you have found ideal values you can enter them manually in the code as constants (lines 28 to 38) and then start the robot and just ignore the network. You will also need to install the [roboEyes library](https://github.com/FluxGarage/RoboEyes)

## Final notes
Thank you for visiting this page; this is a 3/5** difficulty project so be patient and have fun building  


##  
(*)This one is optional but a nice touch   


