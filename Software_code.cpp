/* Name: Zain Hasan
   Code for RC car project
   Zephyr308
*/


#include "mbed.h"
#include "ultrasonic.h"


Serial pc(USBTX, USBRX); // tx, rx

PwmOut steering(p21);                       // Pin configuration for the car
PwmOut velocity(p22);
DigitalOut red (p23);                       // Setup for LEDs, Change it to desired pins
DigitalOut green (p24);
DigitalOut yellow (p25);

AnalogIn trig_1 (p17);                      // This will configure the trigger pins
AnalogIn trig_2 (p16);                      // of ultrasonic sensor
AnalogIn trig_3 (p6);                       // Each AnalogIn correspond to one sensor
AnalogIn trig_4 (p6);                       // So add or remove it based on number of sensor that you will be using.

AnalogOut echo_1 (p18);                     // This set up the echo pins of ultrasonic sensor
AnalogOut echo_2 (p18);                     // Similar to trigger pins, each AnalogOut match with one sensor
AnalogOut echo_3 (p8);                      // Add or remove based on nunmber of sensors willing to be used.
AnalogOut echo_4 (p8);
 
float vo=0;
 
// Velocity expects -1 (reverse) to +1 (forward)
void Velocity(float v) {
  v=v+1;
  if (v>=0 && v<=2) {
    if (vo>=1 && v<1) {                     //
      velocity.pulsewidth(0.0014);          // this is required to
      wait(0.1);                            //
      velocity.pulsewidth(0.0015);          // move into reverse
      wait(0.1);                            //
    }                                       //
    velocity.pulsewidth(v/2000+0.001);
    vo=v;
  }
}
// Steering expects -1 (left) to +1 (right)
void Steering(float s){
  s=s+1;
  if (s>=0 && s<=2){
    steering.pulsewidth(s/2000+0.001);
  }
}

void Movement(int value){                   // Contained a case statement which gave car a particular action
  int num = value;                          // depending the value being called.
  switch(num){                              // this controlled the car wheel movement when called for
        
    case 1: // forward
      for(int i=0; i<25; i++){
        Velocity(i/100.0);
        wait(0.1);
      }
      break;
        
    case 2: // Reverse
      for(int i=25; i>-25; i--){
        Velocity(i/100.0);
        wait(0.1);
      } 
                
    case 3: // Steer right
      for(int i=0; i<30; i++){          
        Steering(i/100.0);
        wait(0.1);
      }
      break;
            
    case 4: // Steer left
      for(int i = 0; i>-30; i--){
        Steering(i/100.0);
        wait(0.1);
      }
      break;
                
    case 5: // Stop
      for(int i = 0; i < 0; i++){
        Velocity(i/100.0);
        wait(0.1);
      }
      break;  
  }   
}

int data[4];                                        // Storage for holding sensor measurement, size is based on number of sensor using
// Front sensor (middle)
void front_dist(int distance){                      // the next four function indicate the action of the car
                                                    // the arguement is distance measured in real-time.
  pc.printf("Front_sensor = %d\r\n", distance);     // if parameter is met, the function is called
  data[0] = distance;                               // which is used to control the car movement
  if(distance < 200){                               // illuminate LEDs, depending on the responses
    
    red = 1;                                        // Note: this section is where you would write the code to execute
    green = 0;                                      // particular action after distance is measured from corresponding sensors.
    yellow = 1;         
    
    Movement(5); 
  }
  else if(distance > 200){
    Movement(1);
  }
}
// Left sensor
void left_dist(int distance){
  data[1] = distance;
  pc.printf("left_sensor = %d\r\n", distance); 
  
  if(distance < 150){                               // The car will steer to right
    red = 1;
    green = 0;
    wait(0.5);
    yellow = 1;
    wait(0.5);
    yellow = 0;
    Movement(3);
  }
}
// Right sensor
void right_dist(int distance){
  data[2] = distance;
  
  if(distance < 150){                               // The car will steer to left
    red = 1;
    green = 0;
    wait(0.5);
    yellow = 1;
    wait(0.5);
    yellow = 0;
    Movement(2);
  }
}

void back_dist(int distance){                       // The car will reverse
  data[3] = distance;
  if(distance > 200 && data[0] < 200){
    wait(0.5);
    red = 1;
    wait(0.50);
    red = 0;
    green = 0;
    yellow = 0;
    Movement(2);                                    
  }
  else{
    red = 1;
    green = 0;
    yellow = 0;
    Movement(5);
  } 
}




ultrasonic mu1(p17, p18, .1, 1, &front_dist);       // Arguement: trigger, echo, setup time, time delay, 'dist function mentioned above'
                                        
ultrasonic mu2(p17, p18, .1, 1, &left_dist);
                                                    // Initiliasing all four sensor
ultrasonic mu3(p13, p14, .1, 1, &right_dist);       // This code use a library which setup the ultrasonic sensor.

ultrasonic mu4(p16, p17, .1, 1, &back_dist);        // Each represent one sensor initialised in its own variable and respond to
                                                    // own 'dist' function.
int main(){
  
  mu1.startUpdates();                               // Starting measuring the distance
  mu2.startUpdates();
  mu3.startUpdates(); 
  mu4.startUpdates();
   
  velocity.period(0.02);
  steering.period(0.02);
  Velocity(0);                                      // initiate the drive motor (this must be done)
  Steering(0);                                      // centre steering 
  wait(0.5);
  int i = 1;
    
  while(1) {
    yellow = 0;                                     // Green LED indicate power ON
    red = 0;
    green = 1;
    while(i<25){                                    // Car's premilinary action: Move forward continuously
      Velocity(i/100.0);
      wait(0.1);
      i++;
    }
    mu1.checkDistance();                            // Observe the surrounding and response accordingly
    mu2.checkDistance();                            // from all four sensors
    mu3.checkDistance(); 
    mu4.checkDistance();         
  }

}
