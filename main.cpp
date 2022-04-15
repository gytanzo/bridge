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
 
int main(int argc, char *argv[])
{
  // initialize distance and ir sensors
  
  // begin infinite polling for the sensors
    // update position based on results from sensors
    // i.e. if sensors indicate the ball is further from the servo, move the pendulum down
    // this part is probably functionality in a subfunction
    int dist = checkDistance();
    int ir = checkIR();
  return 0;
}

int checkDistance()
{
  // check the distance sensor every XX ms/sec
  
  return 0; // update with result
}

int checkIR()
{
  // grab value of the ir sensor
  // convert to digital
  // poll every 200 ms and average the value? adjust the time value as necessary
  
}
