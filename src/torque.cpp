#include <iostream>

#include <chrono>

#include "b3m.h"
#include "Console.h"
#include <qpOASES.hpp>

using namespace kondo;
#define BAUDRATE 1500000


#define TORQUE_MIN -32768
#define TORQUE_MAX 32768

#define SET_TORQUE 1500  // mili Newton meter

B3M* pb3m;
int current;
int encoder;
void signalHandler( int signum ) {
  
  std::cout << "Program Ended.\n";

   // cleanup and close up stuff here  
   // terminate program  
  pb3m->setTargetCurrent(0, 0);
  pb3m->setMode(0, OPERATION_MODE_FREE);
  // ssr::exit_scr();
  // ssr::exit(signum);  
}

int  main(int argc, char* argv[]) {
 
    // ssr::init_scr();

  std::cout << "---- Torque Test Program ----" << std::endl;
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
  pb3m->setGainPresetNumber(id, 2);
  pb3m->setMode(id, OPERATION_MODE_NORMAL | CONTROL_MODE_TORQUE );

  
 /**  Do Your Stuff Here  **/


  // pb3m->setTargetCurrent(0, SET_TORQUE);

  signal(SIGINT, signalHandler);

  auto start_loop = std::chrono::steady_clock::now();
  float time_loop = 10;

  while(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_loop).count() < time_loop) 
  {
    // auto start = std::chrono::steady_clock::now();

    pb3m->setTargetCurrent(0, SET_TORQUE);

    // current = pb3m->getActualCurrent(0);

    int16_t vel = pb3m->getActualVelocity(0);
    // std::cout<<"vel: "<<vel<<std::endl;
    // auto end = std::chrono::steady_clock::now();
    // encoder = pb3m->getEncoderCount(0);
    // total_encoder = pb3m->getEncoderTotalCount(0);
    // motor_temp = pb3m->getMotorTemperature(0);
    // mcu_temp = pb3m->getMCUTemperature(0);
    ssr::Thread::Sleep(1);  

    // auto end = std::chrono::steady_clock::now();
    // std::cout << current << ","  << encoder << "," 
    std::cout << vel <<  std::endl;
    // std::cout << "vel:" << vel << std::endl;
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    //<< total_encoder << "\t\t" << motor_temp << "\t\t" << std::endl;


  }

  std::cout << "Program Ended.\n";

   // cleanup and close up stuff here  
   // terminate program  
  pb3m->setTargetCurrent(0, 0);
  pb3m->setMode(0, OPERATION_MODE_FREE);
  return 0;
}