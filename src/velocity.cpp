#include <iostream>


#include "b3m.h"
#include "Console.h"


using namespace kondo;

#define BAUDRATE 1500000


B3M* pb3m;

int  main(int argc, char* argv[]) {
  try {
    ssr::init_scr();

  std::cout << "---- B3M Test Program ----" << std::endl;
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

  
 /** 
  ----------------> Do Your Stuff Here <-----------------------

  1. 10000

**/

  pb3m->setTargetVelocity(id, 15000); // 10 deg/sec * 100
  ssr::Thread::Sleep(5000); 

  // for (;;) {
  //   ssr::Thread::Sleep(500);  

  // }
  
  ssr::exit_scr();
  pb3m->setTargetVelocity(id, 0);
  pb3m->setMode(id, OPERATION_MODE_FREE);

  std::cout << "---- B3M Test Program End----" << std::endl;
  } catch (std::exception& e) {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  return 0;
}