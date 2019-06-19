#include <iostream>
#include "b3m.h"
#include "Console.h"

#include <iostream>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <cstring>

using namespace kondo;

#define BAUDRATE 1500000

#define VELOCITY_MIN -32768 
#define VELOCITY_MAX 32767

#define SET_VELOCITY 1000 // Units: (Value/100) deg/sec 


B3M* pb3m;


void signalHandler( int signum ) {
  
  std::cout << "Program Ended.\n";

   // cleanup and close up stuff here  
   // terminate program 
  pb3m->setTargetVelocity(0, 0);
  pb3m->setMode(0, OPERATION_MODE_FREE);
  // ssr::exit_scr();
  // ssr::exit(signum);  
}

int  main(int argc, char* argv[]) {
  try {
    ssr::init_scr();

  std::cout << "---- Velocity Test Program ----" << std::endl;
  if (argc <= 1) {
    std::cout << "Invalid Usage." << std::endl;
    std::cout << std::endl;
    std::cout << "Usgae:  $ demo [DEVICE_FILE]" << std::endl;
    std::cout << std::endl;
    return -1;
  }

  const ID_t id = 0;
  pb3m = new B3M(argv[1], BAUDRATE);

  pb3m->setMode(id, OPERATION_MODE_FREE);
  pb3m->setGainPresetNumber(id, 1);
  pb3m->setMode(id, OPERATION_MODE_NORMAL | CONTROL_MODE_VELOCITY );

  
 /** ----------------> Do Your Stuff Here <----------------------- **/ 
  signal(SIGINT, signalHandler);
  
  pb3m->setTargetVelocity(id, SET_VELOCITY);

  auto start_loop = std::chrono::steady_clock::now();
  float time_loop = 50;

  while(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_loop).count() < time_loop) {
    int16_t vel = pb3m->getActualVelocity(0);
    std::cout << vel << "," << pb3m->getActualCurrent(0) << std::endl;
  }
  

  std::cout << "---- B3M Test Program End----" << std::endl;
  } catch (std::exception& e) {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  pb3m->setTargetCurrent(0, 0);
  pb3m->setMode(0, OPERATION_MODE_FREE);

  return 0;
}