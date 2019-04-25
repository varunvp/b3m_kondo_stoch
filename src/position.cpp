#include <iostream>


#include "b3m.h"
#include "Console.h"


using namespace kondo;

#define BAUDRATE 1500000
#define VERTICAL_DOWN 0
#define VERTICAL_UP   18000
#define HORIZONTAL_OPPOSITE_LED -9000
#define HORIZONTAL_TOWARDS_LED   9000

B3M* pb3m;

void signalHandler( int signum ) {
  
  std::cout << "Program Ended.\n";

   // cleanup and close up stuff here  
   // terminate program  
  ssr::exit_scr();
  pb3m->setMode(0, OPERATION_MODE_FREE);
  ssr::exit(signum);

}

int  main(int argc, char* argv[]) {
  try {
    ssr::init_scr();

  std::cout << "---- Position Test Program ----" << std::endl;
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
  pb3m->setGainPresetNumber(id, 0);
  pb3m->setMode(id, OPERATION_MODE_NORMAL | CONTROL_MODE_POSITION );

  

 
  signal(SIGINT, signalHandler);


  for (;;) {

    // Horizontal
    pb3m->setTargetPosition(id, HORIZONTAL_TOWARDS_LED); // 10 deg/sec
    ssr::Thread::Sleep(700);  
    pb3m->setTargetPosition(id, HORIZONTAL_OPPOSITE_LED);
    ssr::Thread::Sleep(700);
  }
 

  } 
  catch (std::exception& e) {
  std::cout << "Exception : " << e.what() << std::endl;
  }
  return 0;
}