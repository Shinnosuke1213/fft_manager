cmake_minimum_required(VERSION 3.26)
project(rt_audio)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)

link_directories(dlls)

add_executable(rt_audio main.cpp
        fft_manager.hpp
        fft_manager.cpp
        rt_manager.hpp
        rt_manager.cpp)

target_link_libraries(rt_audio
        librtaudio
        libfftw3f
        libportaudio
)