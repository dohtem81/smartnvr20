cmake_minimum_required(VERSION 3.1)
project( smartnvr20 )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_CURRENT_SOURCE_DIR /usr/smartnvr20/src)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package( hiredis REQUIRED )
include_directories( ${hiredis_INCLUDE_DIRS} )
find_package( spdlog REQUIRED )
include_directories( ${spdlog_INCLUDE_DIRS} )
find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})
find_package(Protobuf CONFIG REQUIRED)
find_package(utf8_range REQUIRED)
find_package(gRPC CONFIG REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Proto files
set(PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/grpc/protos/heartbeat.proto
)
# Generate gRPC files for heartbeat.proto
add_custom_command(
    OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/heartbeat.pb.cc"
        "${CMAKE_CURRENT_BINARY_DIR}/heartbeat.pb.h"
        "${CMAKE_CURRENT_BINARY_DIR}/heartbeat.grpc.pb.cc"
        "${CMAKE_CURRENT_BINARY_DIR}/heartbeat.grpc.pb.h"
    COMMAND protoc
        --grpc_out="${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out="${CMAKE_CURRENT_BINARY_DIR}"
        -I="${CMAKE_CURRENT_SOURCE_DIR}/interfaces/grpc/protos"
        --plugin=protoc-gen-grpc=`which grpc_cpp_plugin`
        ${PROTO_FILES}
    DEPENDS ${PROTO_FILES}
)

# Create library for generated files
add_library(proto_gen
    ${CMAKE_CURRENT_BINARY_DIR}/heartbeat.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/heartbeat.grpc.pb.cc
)
target_link_libraries(proto_gen
    protobuf::libprotobuf
    utf8_range
    gRPC::grpc++
)

add_executable( commbus_test_01
    ./infrastructure/RedisClient/busclient.cpp
    ./infrastructure/framehandlerconfig.cpp
    ./tests/infrastructure/commbus_test_01.cpp)
target_link_libraries(commbus_test_01 ${OpenCV_LIBS} ${hiredis_LIBRARIES} ${spdlog_LIBS} ${nlohmann_json_LIBS} ${GTEST_LIBRARIES} proto_gen pthread) 

add_executable( framehandler_test_01
    ./infrastructure/framehandler.cpp 
    ./infrastructure/framehandlerconfig.cpp
    ./infrastructure/RedisClient/busclient.cpp
    ./tests/infrastructure/framehandler_test_01.cpp)
target_link_libraries(framehandler_test_01 
    ${OpenCV_LIBS} 
    ${hiredis_LIBRARIES} 
    ${spdlog_LIBS} 
    ${nlohmann_json_LIBS} 
    ${GTEST_LIBRARIES} 
    proto_gen 
    protobuf::libprotobuf
    utf8_range
    gRPC::grpc++    
    pthread) 

add_executable( camera_test_01 
    ./domain/cameraDevice.cpp 
    ./tests/domain/camera_test_01.cpp)    
target_link_libraries( camera_test_01 ${OpenCV_LIBS} ${hiredis_LIBRARIES} ${spdlog_LIBS} ${nlohmann_json_LIBS} ) 

add_executable( filelocation_test_01  
    ./tests/lib/filelocation_test_01.cpp)    
target_link_libraries( filelocation_test_01 ${OpenCV_LIBS} ${hiredis_LIBRARIES} ${spdlog_LIBS} ${nlohmann_json_LIBS} ) 