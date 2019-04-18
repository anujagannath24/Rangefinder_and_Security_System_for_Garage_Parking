# Rangefinder and Security System for Garage Parking
## Contents:
- Overview
- Sensors and Actuators
- Schematic diagrams
- Bill of Materials

## Overview
The device consists of two modules. One is security system and the other is rangefinder. Security system allows only authorized users to enter the garage. The authenticity of the user is checked by having the user to enter a password before entering the garage. The user has to enter a 4-digit password through IR remote control. The display used for user interaction is an LCD display.

Rangfinder module is assists the driver to park the vehicle in the desired spot. The driver would not be unable to see/estimate the distance of the vehicle from the wall. This device will measure the distance of the vehicle from the wall using an ultrasonic sensor. Depending on the distance the RGB will display different colors. When it is far, it displays green. As the vehicle approaches the wall, it will turn yellow and when it is time to stop it displays red and buzzer goes off. 

![alt text](https://raw.githubusercontent.com/anujagannath24/Rangefinder_and_Security_System_for_Garage_Parking/master/schematics/block_diagram.jpg)

## Sensors and Actuators
### IR transmitter-receiver pair
IR remote and IR LED pair is used as IR transmitter and receiver here. User enters the password to enter the garage using the IR remote. It is a 4-digit password.
### LCD Display
The LCD display used here is a 16x2 display. It consists of 2 lines of 16 characters each. It is used for user interface. It works as a user interface for security system to display the messages like if the password is right or not.
### LED
The garage light will be turned on if the password entered by the user is correct. Here an LED represents the lights in the garage.

### Ultrasonic sensor
It is a proximity sensor. It has a transducer which emits ultrasonic sound waves and senses the reflected sound. The time lapses between the sending and the receiving of ultrasonic pulse is calculated to determine the exact distance from an object. 
The ultrasonic sensor used here is a 4-pin device and the pins are Vcc, ground, Trigger and echo.
### RGB LED
RGB LED is similar to the regular LED except that it has 4 pins and 3 diodes in it. One pin is ground and the rest three are red, green and blue. The color of the LED is varied by sending different values to different pins. The desired color is obtained by mixing the primary colors red, green and blue. The color is decided based on the distance from the object.
![color](https://user-images.githubusercontent.com/44581838/56327528-f00d2680-6137-11e9-8a28-d852463e0687.jpg)
### Buzzer
It is a passive buzzer. When a tone signal is sent to the actuator i.e. the piezo buzzer, it turns on. The signal is generated using the TimerFreeTone() function from the TimerFreeTone library.
Piezo buzzer turns on when the vehicle is less than 15cm near from the device. It is to indicate that the vehicle should stop at this point.

## Schematic Diagrams

<img src="https://raw.githubusercontent.com/anujagannath24/Rangefinder_and_Security_System_for_Garage_Parking/master/schematics/fig1.jpg" width="600">

<img src="https://raw.githubusercontent.com/anujagannath24/Rangefinder_and_Security_System_for_Garage_Parking/master/schematics/fig2.jpg" width="600">

## Bill of Materials
