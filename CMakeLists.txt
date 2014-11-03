cmake_minimum_required(VERSION 2.8.4)

project(mesolua CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(LibFindMacros)

libfind_pkg_detect(MESOS mesos FIND_PATH mesos/mesos.hpp FIND_LIBRARY mesos)
libfind_process(MESOS)

include(deps/luajit.cmake)
include_directories(${LUA_INCLUDE_DIR} deps/picojson /usr/local/include)

luajit_add_executable(mesolua
  src/main.cpp
  src/flags.cpp
  src/module.cpp
  src/test_scheduler.cpp
)

luajit_add_executable(mesolua-executor
  src/main_executor.cpp
  src/task_executor.cpp
  src/lua_runner.cpp
)

target_link_libraries(mesolua lua51 ${MESOS_LIBRARY})
target_link_libraries(mesolua-executor lua51 ${MESOS_LIBRARY})


