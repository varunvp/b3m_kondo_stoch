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
  float time_loop = 5;
  qpOASES::real_t desired_pos= 200;
  qpOASES::real_t Ko = 1;
  qpOASES::real_t Kp = 80;
  qpOASES::real_t Kd = 0;
  qpOASES::real_t H[2*2] = {1.0, 0.0, 0.0, 1.0};
  qpOASES::real_t g[2] = {0.0, 0.0};
  qpOASES::real_t lb[2] = {-qpOASES::INFTY,-3000};
  qpOASES::real_t ub[2] = {qpOASES::INFTY, 3000};
  qpOASES::real_t lbA[1] = {-qpOASES::INFTY};
  float set_torque = SET_TORQUE;
  while(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_loop).count() < time_loop) 
  {
    // auto start = std::chrono::steady_clock::now();

    // current = pb3m->getActualCurrent(0);

    float current_vel = pb3m->getActualVelocity(0);
    // std::cout<<"vel: "<<vel<<std::endl;
    // auto end = std::chrono::steady_clock::now();
    float encoder_raw = pb3m->getEncoderCount(0);
    qpOASES::real_t current_pos = (encoder_raw / 4096) * 360;

    qpOASES::real_t error= desired_pos- current_pos;

    qpOASES::real_t A[1*2]={-1, Ko * error + current_vel};
    qpOASES::real_t ubA[1] = {-1 * (Ko*error + current_vel)*(Kp*error + Kd * current_vel)};
    qpOASES::QProblem solver(2,1);
    qpOASES::Options options;
    options.printLevel = qpOASES::PL_NONE;
    solver.setOptions( options );

    int nWSR = 100;
    solver.init(H,g,A,lb,ub,lbA, ubA, nWSR);

    qpOASES::real_t xOpt[2];
    solver.getPrimalSolution( xOpt );


    // example.init(SymmetricMatrix *_H, const real_t *const _g, Matrix *_A, const real_t *const _lb, const real_t *const _ub, const real_t *const _lbA, const real_t *const _ubA, int_t &nWSR)
    // total_encoder = pb3m->getEncoderTotalCount(0);
    // motor_temp2 = pb3m->getMotorTemperature(0);
    // mcu_temp = pb3m->getMCUTemperature(0);

    ssr::Thread::Sleep(1);  

    // auto end = std::chrono::steady_clock::now();
    // std::cout << current << ","  << encoder << "," 
    std::cout << "error: " << error<< " Optimal Set Torque: "<< error * Kp << " Current Velocity: "<<current_vel<<std::endl;
    set_torque = xOpt[1];

    pb3m->setTargetCurrent(0, error * Kp);

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
