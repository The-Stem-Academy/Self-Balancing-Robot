# Self Balancing Robot Project Files
## By The STEM Academy

### This site provides a place for you to access project files and code - free of charge!

If you have any questions please visit our [5-minute Yotube Guide](https://youtu.be/3z8Bph11x7s) and we encorage you to comment :)

## Required Hardware
You will need the following:  

* 1x L298N motor driver  
* 1x ESP-32 or simlar board  
* 1x 7 ish volt batter since voltage is lost in the motor driver but whatver works for you is fine  
* 1x MPU 6050  
* 2x DC gear motors (with weels)  
* Loads of wires  
* 2x 0.96 OLED displays*  
* 1x Perfboard PCB (you can use a breadboard or whatever method you wish to connect the components)  

## Assembly
The assembly process is relitavly straightfoward and requires a handful of various screws which if you dont have - superglue can be use but is not ideal for reasons I state in the Yotube Guide. Feel free to make your own out of wood or carboard; I would be interested to see.

## Code
The code will broadcast a WIFI network from your ESP-32 called "Self Balancing Robot Tuner" with the password "12345678" if you connect to this network on any device and go to your web brower and enter "192.168.4.1" to the search bar you will be able to fine tune many values for your robot, over WIFI which will streamline the PID tuning process. Once you have found ideal values you can enter them manually in the code as constants (lines 28 to 38) and then start the robot and just ignore the network.

## Final notes
Thank your for visiting this page; this is a 3/5** difficulty project so be patient and have fun building  


##  
(*)This one is optional but a nice touch  
(**)The difficulty rating ranges from 1-5 out of 5, Five being the hardest and One the easiest.  
