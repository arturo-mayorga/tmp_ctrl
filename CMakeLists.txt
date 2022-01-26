cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  src/tests/hello_test.cc

  src/tests/logger-test-impl.cpp

  src/tests/temp-sensor-system.t.cpp
  src/temp-sensor-system.cpp

  src/tests/scr-system.t.cpp
  src/scr-system.cpp

  src/tests/rotor-system.t.cpp
  src/rotor-system.cpp

  src/tests/message_reader_test.cc
  src/message-reader.cpp

  src/tests/pid-controller.t.cpp
  src/pid-controller.cpp

  src/tests/pid-system.t.cpp
  src/pid-system.cpp

  src/tests/servo-system.t.cpp
  src/servo-system.cpp

  src/tests/bt-message-system.t.cpp
  src/bt-message-system.cpp
)

target_link_libraries(
  hello_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
