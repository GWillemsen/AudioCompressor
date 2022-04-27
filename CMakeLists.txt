project(AudioCompressor C)
cmake_minimum_required(VERSION 3.15)


set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    ${SOURCE_DIR}/processor.c
    ${SOURCE_DIR}/Curves/sine_curve.c
)

set(HEADERS ${INCLUDE_DIR}/curve.h
    ${INCLUDE_DIR}/processor.h
    ${INCLUDE_DIR}/Curves/sine_curve.h
)


add_library(AudioCompressor STATIC ${SOURCES} ${HEADERS})
target_include_directories(AudioCompressor PUBLIC ${INCLUDE_DIR})
target_compile_options(AudioCompressor PRIVATE -g)

add_executable(app ${SOURCE_DIR}/main.c)
target_link_libraries(app PRIVATE AudioCompressor)