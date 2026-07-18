cmake_minimum_required(VERSION 3.20)

project(idp-engine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

add_executable(idp-engine
    src/main.cpp
    src/idp/image/grayscale.cpp
    src/idp/quality/brightness.cpp
    src/idp/quality/blur.cpp
    src/idp/quality/status.cpp
    src/idp/quality/resolution.cpp
    src/idp/document/edge_detector.cpp
)

target_link_libraries(idp-engine PRIVATE ${OpenCV_LIBS})
target_link_libraries(idp-engine PRIVATE fmt::fmt)
target_include_directories(idp-engine PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)