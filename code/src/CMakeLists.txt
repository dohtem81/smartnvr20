cmake_minimum_required(VERSION 3.1)
project( smartnvr20 )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package( hiredis REQUIRED )
include_directories( ${hiredis_INCLUDE_DIRS} )
find_package( spdlog REQUIRED )
include_directories( ${spdlog_INCLUDE_DIRS} )

add_executable( camera_mod 
    ./camera/application/camera.cpp 
    ./camera/main.cpp)
target_link_libraries( camera_mod ${OpenCV_LIBS} ${hiredis_LIBRARIES} ${spdlog_LIBS} ) 