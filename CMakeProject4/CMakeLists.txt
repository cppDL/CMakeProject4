# CMakeList.txt : CMake project for CMakeProject4, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeProject4 "CMakeProject4.cpp" "CMakeProject4.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject4 PROPERTY CXX_STANDARD 20)
endif()

project ("RobotCleaner")

set(SOURCE_EXE main.cpp)

add_library(RobotCleaner STATIC ${SOURCE_LIB})
add_executable(main ${SOURCE_EXE})
target_link_libraries(main CMakeRobot)

# TODO: Add tests and install targets if needed.
