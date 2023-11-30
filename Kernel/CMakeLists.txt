cmake_minimum_required(VERSION 3.25.0)

set(KERNEL_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/kernel.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/fifo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/scheduler.c
    PARENT_SCOPE)

set(KERNEL_INC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PARENT_SCOPE)