cmake_minimum_required(VERSION 3.19)
project(sha512)

set(CMAKE_CXX_STANDARD 14)
set(wxWidgets_CONFIGURATION mswu)

include_directories("D:/Program Files/cpp libraries/wxWidgets-3.1.5/include")
link_directories("D:/Program Files/cpp libraries/wxWidgets-3.1.5/lib/vc_lib")

# Request the required wxWidgets libs
find_package(wxWidgets 3.1 COMPONENTS core base REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_executable(sha512 main.cpp sha512.cpp sha512.h myApp.cpp myApp.h frames.cpp frames.h sha2.cpp sha2.h sha384.cpp sha384.h sha224.cpp sha224.h sha256.cpp sha256.h hashCalculator.cpp hashCalculator.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS /SUBSYSTEM:WINDOWS
        )