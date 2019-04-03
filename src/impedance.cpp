#include <iostream>


#include "b3m.h"
#include "Console.h"


using namespace kondo;
#define BAUDRATE 1500000


#define TORQUE_MIN -32768
#define TORQUE_MAX 32768

#define SET_TORQUE 1000  // mili Newton meter

int16_t prev_val;
float stiffness;

#define SET_POINT 9000


B3M* pb3m;


void signalHandler( int signum ) {
  
  std::cout << "Program Ended.\n";

   // cleanup and close up stuff here  
   // terminate program  
  ssr::exit_scr();
  pb3m->setTargetCurrent(0, 0);
  pb3m->setMode(0, OPERATION_MODE_FREE);
  
  ssr::exit(signum);  
}

int  main(int argc, char* argv[]) {
  try {
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

  signal(SIGINT, signalHandler);



  pb3m->setTargetCurrent(0, 0);

  // prev_val = 0;
  // stiffness = 0;

  while (1) {


  /** Get the Joint Angle and Filter It **/
  int16_t curr_val  = pb3m->getActualPosition(0);
  int16_t diffi_pos  = (curr_val - prev_val);
  int16_t filtrd_val = (prev_val + (0.5*diffi_pos) ); 
    
  std::cout <<"Actual Value is :"<<curr_val<<" Filter Value is :"<<filtrd_val<<std::endl;


  /** Calculate the error and fix the stiffness **/
  int16_t error_pos  =  filtrd_val - SET_POINT;

    if (error_pos < 20 && error_pos > -20)

    {
      stiffness = 0;
      // std::cout<<"If \n";
    }
    else {
      stiffness = 0.09;// 
    }


  /**Set the Current Vvalue **/
  int16_t set_current = -stiffness*error_pos;
  std::cout <<" Set Current :"<< set_current <<" Stiffness :"<< stiffness<<" Error Pos :"<<error_pos<< "\n";
  

  pb3m->setTargetCurrent(0, set_current);
  

  /**Set [the Current Value to the previous value **/
  prev_val = curr_val;


  }
  
  // ssr::exit_scr();
  // pb3m->setTargetCurrent(0, 0);
  // pb3m->setMode(id, OPERATION_MODE_FREE);

  std::cout << "---- B3M Test Program End----" << std::endl;
  } catch (std::exception& e) {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  return 0;
}