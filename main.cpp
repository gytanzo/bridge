/*
Name of program: Reverse Pendulum
Author: Andrew Zhou, Maryam Nisar, Ben Miller
Date Created: 4/15/2022
Date last updated: 4/15/2022
Function: Control the overall function of the reverse pendulum
Modules: N/A
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>

DigitalOut trigger(PA_8);
DigitalIn IR(PB_3);
InterruptIn echo(PA_9);
Timer timer; 

int main(int argc, char *argv[])
{
  // initialize ports
  RCC->AHB2ENR |= 0x3;  // Initialize port A and B
  GPIOB->MODER &= ~(0x000F0000);    // Set up Registers PB8 and PB9 as inputs
  
  //Output: PA_7 (pwm) -> SERVO
  PwmOut servo(PA_7);

  //Input: IR sensor (PB_8)
  IR.mode(PullNone);

  //Distance sensor (PB_9) - Initialized above
  
  while(true) {
  // begin infinite polling for the sensors
    // update position based on results from sensors
    // i.e. if sensors indicate the ball is further from the servo, move the pendulum down
    // this part is probably functionality in a subfunction
    int dist = checkDistance(); // returned in millimeters
    int ir = checkIR(); // 0 = IR detected somthing. 1 = nothing detected.
    if(dist<50 && ir==1){
        //distance sensor and IR is on the left
        //tilt servo right 
        //ball is on the left side (close side)

    }
    else if(dist > 50 && ir==0){
        //distance sensor and IR is on the left
        //tilt servo left 
        //ball is on the right side (far side)

    }
  }


  return 0;
}



int checkDistance(void) {

//writing high (1) to trigger for 10 us initially to turn it on
  trigger.write(1);
  wait_us(10); 
//writing low (0) to trigger to turn it off
  trigger.write(0);

  //Wait for echo to change to high
  while (echo.read() == 0) {
      ;
  }
  //Start the timer and let it run until echo is 0 again.
  timer.reset();
  timer.start();
  //Wait for echo to change to low
  while (echo.read() == 1) {
      ;
  }
  timer.stop();
  int store;
  //Calculate the distance from the time
  store = timer.read_us();
  store = store * 0.0340 / 2;
  //Finally return the distance of the object from sensor.
  return store;
}

int checkIR()
{
  // grab value of the ir sensor
  // convert to digital
  // poll every 200 ms and average the value? adjust the time value as necessary

  return IR.read();

}
