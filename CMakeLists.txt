cmake_minimum_required(VERSION 3.28.0)
################################################################################
 # @file           :  CMakeLists.txt
 # @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 # @brief          : IsmailRTOS Project Structure CMake Build
 # IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 # www.learn-in-depth.com
 ###############################################################################

# Configure Arm Cortex-M Bare-metal Cross Toolchain

# Set Target System as Generic for bare-metal application
set(CMAKE_SYSTEM_NAME Generic)

# Set Target Processor as Arm
set(CMAKE_SYSTEM_PROCESSOR arm)

#Based on user entry for env variable ARMCMX we set the appropriate target cpu for the compiler
if(${ARMCMX} STREQUAL ARMCM4)
    set(MCPU cortex-m4)
elseif(${ARMCMX} STREQUAL ARMCM3)
    set(MCPU cortex-m3)
elseif(${ARMCMX} STREQUAL ARMCM0)
    set(MCPU cortex-m0)
elseif(${ARMCMX} STREQUAL ARMCM0plus)
    set(MCPU cortex-m0)
elseif(${ARMCMX} STREQUAL ARMCM1)
    set(MCPU cortex-m1)
elseif(${ARMCMX} STREQUAL ARMCM7)
    set(MCPU cortex-m7)
else()
    message(FATAL_ERROR "You must specify target ARM Processor in this syntax ARMCMX")
endif()


set(CPUFLAGS "-mcpu=${MCPU} -mthumb " ) # Target Processor Flags
set(CFLAGS "-D${ARMCMX} --specs=nosys.specs ") # gcc/g++ compiler Flags
set(DFLAGS "-g -gdwarf-2 ") # Debugging Flags
set(CC arm-none-eabi-)
set(CMAKE_CXX_COMPILER ${CC}g++ ${CPUFLAGS} ${CFLAGS} ${DFLAGS})
set(CMAKE_C_COMPILER ${CC}gcc   ${CPUFLAGS} ${CFLAGS} ${DFLAGS})
set(CMAKE_ASM_COMILER ${CC}as   ${CPUFLAGS} ${DFLAGS})
set(CMAKE_CXX_COMPILER_WORKS TRUE) # This is to skip testing the compiler
set(CMAKE_C_COMPILER_WORKS TRUE)

set(CMAKE_EXECUTABLE_SUFFIX_C ".elf") # Target executable format

# Sub-directories for children CMake
add_subdirectory(${CMAKE_SOURCE_DIR}/Kernel) 
add_subdirectory(${CMAKE_SOURCE_DIR}/CortexMX_Porting) 
#add_subdirectory(${CMAKE_SOURCE_DIR}/CortexMX_Porting/Core/${ARMCMX}) # Target Processor Core Directory


project("IsmailRTOS")


# Set Executable Name for your application
set(EXE_NAME "IsmailRTOS")

# add additional application source files according to your project.
set(APP_SRC_FILES app.c)

# add additional source files directories according to your project (e.g additional HAL directories)
add_executable(${EXE_NAME}
               ${APP_SRC_FILES}
               ${KERNEL_SRC_FILES}
               ${PORTING_SRC_FILES}
)

# add additional include files directories according to your project (e.g additional HAL directories)
target_include_directories(${EXE_NAME} PUBLIC
                           ${KERNEL_INC_FILES}
                           ${PORTING_INC_FILES}
)

target_link_options(${EXE_NAME} BEFORE
                    PUBLIC -T ${CMAKE_SOURCE_DIR}/linker_script.ld 
)

add_custom_command(TARGET ${EXE_NAME}
                   DEPENDS POST_BUILD
                   COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXE_NAME}> ${EXE_NAME}.bin
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/output

)

add_custom_command(TARGET ${EXE_NAME}
                   DEPENDS POST_BUILD
                   COMMAND cp $<TARGET_FILE:${EXE_NAME}> ${EXE_NAME}.axf
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/output

)



