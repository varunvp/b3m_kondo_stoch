#include <iostream>


#include "b3m.h"
#include "Console.h"


using namespace kondo;

#define BAUDRATE 1500000


#define POSITION 18000



// -32000  Mini Position
// 32000 Max Position
#define VERTICAL_DOWN 0
#define VERTICAL_UP   18000

#define HORIZONTAL_OPPOSITE_LED -8000
#define HORIZONTAL_TOWARDS_LED   9000

B3M* pb3m;

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

  

  // for (;;) {
      
  //   // Up and Down
  //   pb3m->setTargetPosition(id, VERTICAL_UP); // 10 deg/sec * 100
  //   ssr::Thread::Sleep(700);  
  //   pb3m->setTargetPosition(id, VERTICAL_DOWN);
  //   ssr::Thread::Sleep(700);

  // }
  

  for (;;) {

    // Horizontal
    pb3m->setTargetPosition(id, HORIZONTAL_TOWARDS_LED); // 10 deg/sec * 100
    ssr::Thread::Sleep(700);  
    pb3m->setTargetPosition(id, HORIZONTAL_OPPOSITE_LED);
    ssr::Thread::Sleep(700);
  }
 


  
  ssr::exit_scr();
  pb3m->setMode(id, OPERATION_MODE_FREE);

  std::cout << "---- B3M Test Program End----" << std::endl;
  } catch (std::exception& e) {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  return 0;
}