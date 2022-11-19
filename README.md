# Technical Diagrams
### Flowchart
<image src="Code_flowchart.png" width="3500">

# Description
**Purpose**: _Build a car that works on its own and can avoid obstacles in its path, as well as recognize walls and not crash into them._


The program makes the use of Mbed OS C language to write an algorithm to program a racing car equipped with ultrasonic sensors and LEDs which would monitor the surroundings and respond accordingly while navigating toward certain destinations. To start off, we would need to initialize series of functions written to allow the car to work properly.  

First is setting the pin to 'PwnOut’ input for steering and velocity of the wheel itself. Next, assigning pins for LEDs to ‘DigitalOut’ output for each colour being used. You would then need to pick pins to assign to trigger and echo pins of ultrasonic sensors individually and operate, using AnalogIn and AnalogOut respectively. 

The original author of the code which run the car, created functions called, velocity() and steering() which is responsible for driving the car by manipulating the wheel. Those two functions will perform calculations which submit the value which determines the RPM of a wheel of a car at a given speed. 

The custom-made function, Movement (), is written by me, is to send instructions to the car itself to perform a driving action. This makes the use of case statement which is split into different direction that wheel can make:  
- Forward, Reverse, Right – Steer, Light – Steer and Stop. 

It will use velocity() and steering() to allow the car to move in one direction based on the value of switch() assigned. 

Utilising the libraries from background research, which allow us to use ultrasonic sensor for Mbed board, would need to create 'dist’ variables based on number of sensors being used.
- Note: this is an important section of code where it allows us to write an instruction to be performed after the distance is measured. 
- ‘dist’ variable: front_dist(), left_dist(), right_dist(), back_dist(), ...etc

As such, I would write the parameter based on the measurement and then call the function Movement() to drive the car accordingly to the range detected from the sensors.

With all function written properly, now we can operate the class developed in the header file to manipulate the ultrasonic sensor by assigning the arguments: trigger, echo, setup time, time delay and ‘dist’ function to be called. Again, number of variables used is based on number of sensors using. 

Inside the main() function, we used the class-defined function, startUpdate() to signal the sensor to start measuring then initialize the car. We wrote a preliminary action which drive the car forward, using the while loop to keep it running. Another class-defined function, checkDistance() will start calling the ‘dist’ function to respond based on the readings obtained. This section of code just mentioned, is kept inside the infinity loop so car can now move on its own. 


# Imported libraries
Constributer - https://os.mbed.com/components/HC-SR04/
- ultrasonic_cpp - List of functions which give the program an algorithm for utilising ultrasonic sensors
- ultrasonic_h - Header file which define the class 'ultrasonic'



# Issues

- When experimenting the ultrasonic sensors, one of them turn out to be faulty as evidence is given in a form of odd readings obtained, shown to be theoretically impossible.

- Further analysis and testing will be needed for this programmed car, as not enough trial is taken in different scenario for car's traversal path. As such, the code may be not work properly and more debugging and restudying will be needed. 
