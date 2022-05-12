/*
Name of program: Reverse Pendulum
Author: Andrew Zhou, Maryam Nisar, Ben Miller
Date Created: 4/15/2022
Date last updated: 4/15/2022
Function: Control the overall function of the reverse pendulum
Modules: N/A
*/
#include <cstdio>
#include <mbed.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <Servo.h>
#include <string.h>

DigitalOut trigger(PA_1);
DigitalIn IR(PB_3);
InterruptIn echo(PA_2);
Timer timer; 

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
  if(store > 100 && store <= 1004){
      printf("%d BIG NUMBER INCOMING: \n", store);
      return store;
  }

  else if (store > 100 && store >= 1005){
      return 3;
  }

  else if(store > 25){
      return 25;
  }
  
  return store;
}

// int checkIR()
// {
//   // grab value of the ir sensor
//   // convert to digital
//   // poll every 200 ms and average the value? adjust the time value as necessary
  
//   //Wait for echo to change to high
//   while (IR.read() == 0) {
//       ;
//   }
//   //Start the timer and let it run until echo is 0 again.
//   timer.reset();
//   timer.start();

//   //Wait for echo to change to low
//   while (IR.read() == 1) {
//       ;
//   }
//   timer.stop();
//   int state;
//   //Calculate the distance from the time
//   state = timer.read_us();
//   return state;

// }

int main(int argc, char *argv[])
{
  // initialize ports
  RCC->AHB2ENR |= 0x3;  // Initialize port A and B
  GPIOB->MODER &= ~(0x000F0000);    // Set up Registers PB8 and PB9 as inputs
  
  //Output: PA_7 (pwm) -> SERVO
  Servo servo(PA_7);

  //Input: IR sensor (PB_3)
  IR.mode(PullNone);

  //Distance sensor (PA_1/PA_2) - Initialized above

  //servo.calibrate(.001, 45);

  int positionAngle = 0;
  trigger=0;
  

  while(true) {
  // begin infinite polling for the sensors
    // update position based on results from sensors
    // i.e. if sensors indicate the ball is further from the servo, move the pendulum down
    // this part is probably functionality in a subfunction

    int dist = checkDistance(); // returned in millimeters
    while(dist >= 100){
        dist = checkDistance();
    }
    printf("%d\n", dist);
    // int ir = checkIR(); // 0 = IR detected somthing. 1 = nothing detected.
    
    
    // Default position for testing purposes
    //servo.position(0);
    //wait_us(5000000);


    // positionAngle = -15;

    if (3 <= dist && dist <= 6){
        // formula 1 (A into B)
        // -45 to -30
        positionAngle = 25/2*dist - 165/2;
    }

    else if (7 <= dist && dist <= 10){
        // formula 2 (B into C)
        // -30 to -20
        positionAngle = 5*dist - 80;
    }

    else if (11 <= dist && dist <= 17){
        // formula 3 (C, balance)
        // -20 to -15 to -10
        positionAngle = -10;
    }

    else if (18 <= dist && dist < 21){
        // formula 4 (C into B)
        // -10 to 0
        positionAngle = 5*dist - 90;
    }

    else if (22 <= dist && dist <= 25){
        // formula 5 (B into A)
        // 5 to 20
        positionAngle = 5/2*dist - 95/2;
    }

    


    //printf("positionAngle = %d\n", positionAngle);
    servo.position(positionAngle);
    wait_us(20000);

  }


  return 0;
}
