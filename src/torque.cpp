#include <iostream>


#include "b3m.h"
#include "Console.h"


using namespace kondo;
#define BAUDRATE 1500000


#define TORQUE_MIN -32768
#define TORQUE_MAX 32768

#define SET_TORQUE 1000  // mili Newton meter




B3M* pb3m;


void signalHandler( int signum ) {
  
  std::cout << "Program Ended.\n";

   // cleanup and close up stuff here  
   // terminate program  
  pb3m->setTargetCurrent(0, 0);
  pb3m->setMode(0, OPERATION_MODE_FREE);
  ssr::exit_scr();
  ssr::exit(signum);  
}

int  main(int argc, char* argv[]) {
 
    ssr::init_scr();

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


  for (;;) {

      pb3m->setTargetCurrent(0, SET_TORQUE);
      ssr::Thread::Sleep(500);  


  }
  
  return 0;
}