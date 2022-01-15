# Template CMakeLists.txt configuration for STM32 MCUS
cmake_minimum_required(VERSION 3.12)
# ##############################################################################
# Edit your MCU information up to the next border
project(mmbtc_firmware)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/PROJECT)
set(MICRO_BITCOIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Libs/uBitcoin/src)

set(MCU_FAMILY STM32F3xx)
set(MCU_MODEL STM32F303xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -march=armv7e-m
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Core/Startup/startup_stm32f303vctx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/STM32F303VCTX_FLASH.ld)
# ##############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Headers
set(CUBEMX_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Drivers/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Middlewares/Third_Party/FreeRTOS/Source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2)
set(PROJECT_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
    # ${MICRO_BITCOIN_DIR}/utility/trezor
    ${MICRO_BITCOIN_DIR}/c_interface
    ${PROJECT_DIR})

# Sources
file(GLOB_RECURSE STM32CUBEMX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Core/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Drivers/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms/F3Disco/Middlewares/*.c)
file(GLOB_RECURSE PROJECT_SOURCES FOLLOW_SYMLINKS
    # ${MICRO_BITCOIN_DIR}/Bitcoin.cpp
    # ${MICRO_BITCOIN_DIR}/Conversion.cpp
    # ${MICRO_BITCOIN_DIR}/Hash.cpp
    ${MICRO_BITCOIN_DIR}/*.cpp
    # ${MICRO_BITCOIN_DIR}/c_interface/interface_w_c.cpp
    ${MICRO_BITCOIN_DIR}/utility/*.c
    ${MICRO_BITCOIN_DIR}/utility/trezor/*.c
    ${PROJECT_DIR}/*.cpp
    ${PROJECT_DIR}/*.c)

# Executable files
add_executable(${EXECUTABLE}
    ${STM32CUBEMX_SOURCES} 
    ${PROJECT_SOURCES}
    ${STARTUP_SCRIPT})

# Embedded macros(defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    ${MCU_MODEL}
    USE_HAL_DRIVER)

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${CUBEMX_INCLUDE_DIRECTORIES}
    ${PROJECT_INCLUDE_DIRECTORIES})

target_compile_features(mmbtc_firmware PUBLIC cxx_std_20)

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)

