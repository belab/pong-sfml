cmake_minimum_required(VERSION 3.6)
project(pong-sfml)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(pong-sfml main.cpp)

target_compile_features(pong-sfml PRIVATE cxx_std_17)

target_compile_options(pong-sfml PRIVATE 
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>)

target_compile_definitions(pong-sfml PRIVATE $<$<CONFIG:Debug>:DEBUG>)

target_link_libraries(pong-sfml PRIVATE sfml-graphics)