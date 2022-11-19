#include "mbed.h"
 
PwmOut steering(p21);
PwmOut velocity(p22);
 
float vo=0;
 
// Velocity expects -1 (reverse) to +1 (forward)
void Velocity(float v) {
    v=v+1;
    if (v>=0 && v<=2) {
        if (vo>=1 && v<1) {                 //
            velocity.pulsewidth(0.0014);    // this is required to
            wait(0.1);                      //
            velocity.pulsewidth(0.0015);    // move into reverse
            wait(0.1);                      //
        }                                   //
        velocity.pulsewidth(v/2000+0.001);
        vo=v;
    }
}
// Steering expects -1 (left) to +1 (right)
void Steering(float s) {
    s=s+1;
    if (s>=0 && s<=2) {
        steering.pulsewidth(s/2000+0.001);
    }
}
 
int main() { 
    velocity.period(0.02);
    steering.period(0.02);
    Velocity(0); // initiate the drive motor (this must be done)
    Steering(0); // centre steering 
    wait(0.5);
    while(1) {
        for(int i=0; i<100; i++) {          // stop to full forward
            Velocity(i/100.0);
            wait(0.1);
        }
        for(int i=100; i>-100; i--) {       // full forward to full reverse
            Velocity(i/100.0);
            wait(0.1);
        }
        for(int i=-100; i<0; i++) {         // full reverse to stop
            Velocity(i/100.0);
            wait(0.1);
        }
        for(int i=0; i<100; i++) {          // centre to full right
            Steering(i/100.0);
            wait(0.1);
        }
        for(int i=100; i>-100; i--) {       // full right to full left
            Steering(i/100.0);
            wait(0.1);
        }
        for(int i=-100; i<0; i++) {         // full left to centre
            Steering(i/100.0);
            wait(0.1);
        }
    }
}
 
   

