# require minimum version of cmake
cmake_minimum_required(VERSION 2.8)

project(pomoduino2test)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(GOOGLE_MOCK_RELATIVE modules/googletest/googlemock)
set(GOOGLE_TEST_RELATIVE modules/googletest/googletest)

add_subdirectory(${GOOGLE_MOCK_RELATIVE})

include_directories(${PROJECT_SOURCE_DIR}/${GOOGLE_MOCK_RELATIVE}/include)
include_directories(${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_RELATIVE}/include)

add_subdirectory(src)

set(tests
    tests/Timer_Test.cpp
    tests/Button_Test.cpp
    tests/Pomodoro_Test.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${tests})
target_link_libraries(${CMAKE_PROJECT_NAME} gmock_main sources_lib)

