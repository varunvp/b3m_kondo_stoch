set(_srcs b3m.cpp)

set(_demo_srcs demo.cpp)
#add_compile_options(-DUSE_LONG_INTEGERS)

include_directories(/home/varun/stoch_2_0/qpOASES/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libaqua/include)

find_package(Threads)
find_library(LIBQPOASES qpOASES /home/varun/stoch_2_0/qpOASES/bin)

link_directories(/home/varun/stoch_2_0/qpOASES/bin)
add_library(${PROJECT_NAME} SHARED ${_srcs})

add_executable(${PROJECT_NAME}_demo ${_demo_srcs})
target_link_libraries(${PROJECT_NAME}_demo ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_demo
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} 
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} 
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} )
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)


# Position
add_executable (position position.cpp)
target_link_libraries(position ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# Velocity
add_executable (velocity velocity.cpp)
target_link_libraries(velocity ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# Torque
add_executable (torque torque.cpp)
target_link_libraries(torque ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )

#Impedance
add_executable (impedance impedance.cpp)
target_link_libraries(impedance ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_executable (example1 example1.cpp)
target_link_libraries(example1 ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} /home/varun/stoch_2_0/qpOASES/bin/libqpOASES.a blas lapack)

add_executable (qp_test qp_test.cpp)
target_link_libraries(qp_test ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} qpOASES)
# /home/varun/stoch_2_0/qpOASES/bin/libqpOASES.so blas lapack)

add_executable (pd_test pd_test.cpp)
target_link_libraries(pd_test ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} qpOASES)