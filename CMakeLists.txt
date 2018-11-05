cmake_minimum_required(VERSION 2.6)
project(trem)


IF(CMAKE_COMPILER_IS_GNUCC)
SET(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -std=c++0x -DBUILD_SHARED_LIBS=OFF")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

FIND_PACKAGE( OpenCV REQUIRED )

find_package( Threads )

add_executable(trem main.cpp class/threads/sema.cpp class/threads/task.cpp class/threads/taskparam.cpp class/threads/thread.cpp class/mapatrem.cpp class/draw.cpp class/linep.cpp class/path.cpp class/threadtest.cpp)

target_link_libraries(trem ${OpenCV_LIBS} ${OpenCV_INSTALL_PATH} ${CMAKE_THREAD_LIBS_INIT} )

install(TARGETS trem RUNTIME DESTINATION bin)
