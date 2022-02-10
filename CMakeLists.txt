cmake_minimum_required(VERSION 3.7)
project(firmware VERSION 0.0.1)

set(EXECUTABLE ${CMAKE_PROJECT_NAME})
# Change these for your own project
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(SIM_CATALINA_DIR "${SRC_DIR}/Platforms/SimCatalina")
set(F3_DISCO_DIR "${SRC_DIR}/Platforms/F3Disco")
set(LVGL_DIR "${SIM_CATALINA_DIR}/lvgl-sdl/lvgl")
set(LVDRV_DIR "${SIM_CATALINA_DIR}/lvgl-sdl/lv_drv")
set(DEMO_DIR "${SIM_CATALINA_DIR}/lvgl-sdl/example")
set(PROJECT_DIR "${SRC_DIR}/PROJECT")
set(MICRO_BITCOIN_DIR "${SRC_DIR}/Libs/uBitcoin/src")

set(MCU_FAMILY STM32F3xx)
set(MCU_MODEL STM32F303xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -march=armv7e-m
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard)

set(STARTUP_SCRIPT ${F3_DISCO_DIR}/Core/Startup/startup_stm32f303vctx.s)
set(MCU_LINKER_SCRIPT ${F3_DISCO_DIR}/STM32F303VCTX_FLASH.ld)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS_RELEASE "-g3")

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Remove this for your own project
add_definitions(-DMAKE_EXAMPLE)

if(${IS_SIM})
  file(GLOB LVGL_DRIVER_SOURCE_FILES
      # My lvgl driver source files
      "${LVDRV_DIR}/lv_sdl_drv_input.c"
      "${LVDRV_DIR}/lv_sdl_drv_display.c"
      "${LVDRV_DIR}/lv_if_drv_filesystem.c"
  )
endif()


file(GLOB LVGL_SOURCE_FILES
    # Main lvgl source files
    "${LVGL_DIR}/src/lv_core/*.c"
    "${LVGL_DIR}/src/lv_draw/*.c"
    "${LVGL_DIR}/src/lv_font/*.c"
    "${LVGL_DIR}/src/lv_gpu/*.c"
    "${LVGL_DIR}/src/lv_hal/*.c"
    "${LVGL_DIR}/src/lv_misc/*.c"
    "${LVGL_DIR}/src/lv_themes/*.c"
    "${LVGL_DIR}/src/lv_widgets/*.c"
)

file(GLOB DEMO_SOURCE_FILES
    "${DEMO_DIR}/example.c"
    "${DEMO_DIR}/input_test.c"
    "${DEMO_DIR}/lv_examples/src/lv_demo_benchmark/*.c"
    "${DEMO_DIR}/lv_examples/src/lv_demo_stress/*.c"
    "${DEMO_DIR}/lv_examples/src/lv_demo_widgets/*.c"
    "${DEMO_DIR}/lv_examples/src/lv_ex_get_started/*.c"
    "${DEMO_DIR}/lv_examples/src/lv_ex_style/*.c"
    "${DEMO_DIR}/lv_examples/src/lv_ex_widgets/*.c"
    "${DEMO_DIR}/lv_examples/assets/*.c"
)

file(GLOB PROJECT_SOURCE_FILES
    "${PROJECT_DIR}/*.c"
)

file(GLOB PLATFORM_F3DISCO_FILES
    "${F3_DISCO_DIR}/*.c"
)

file(GLOB_RECURSE STM32CUBEMX_SOURCES
    ${F3_DISCO_DIR}/Core/*.c
    ${F3_DISCO_DIR}/Drivers/*.c
    ${F3_DISCO_DIR}/Middlewares/*.c)


file(GLOB_RECURSE UBTC_SRCS FOLLOW_SYMLINKS
    # ${MICRO_BITCOIN_DIR}/Bitcoin.cpp
    # ${MICRO_BITCOIN_DIR}/Conversion.cpp
    # ${MICRO_BITCOIN_DIR}/Hash.cpp
    # ${MICRO_BITCOIN_DIR}/*.cpp
    # ${MICRO_BITCOIN_DIR}/c_interface/interface_w_c.cpp
    # ${MICRO_BITCOIN_DIR}/utility/*.c
    ${MICRO_BITCOIN_DIR}/utility/trezor/*.c
    # ${PROJECT_DIR}/*.cpp
)

if(${IS_SIM})
  add_executable(${EXECUTABLE}
                 ${LVGL_DRIVER_SOURCE_FILES}
                 ${LVGL_SOURCE_FILES}
                 ${UBTC_SRCS}
                 ${DEMO_SOURCE_FILES}
  )
endif()
if(${IS_STM32F3DISC})
  add_executable(${EXECUTABLE}
                 ${STM32CUBEMX_SOURCES}
                 ${PLATFORM_F3DISCO_FILES}
                 ${UBTC_SRCS}
                 ${PROJECT_SOURCE_FILES}
  )
endif()

set(CUBEMX_INCLUDE_DIRECTORIES
    ${F3_DISCO_DIR}/Core/Inc
    ${F3_DISCO_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${F3_DISCO_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
    ${F3_DISCO_DIR}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${F3_DISCO_DIR}/Drivers/CMSIS/Include
    ${F3_DISCO_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
    ${F3_DISCO_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${F3_DISCO_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2)



# Add lv_sdl_drv_display lib
if(${IS_SIM})
  list(APPEND CMAKE_MODULE_PATH ${SRC_DIR}/Libs/sdl2)

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
  find_package(SDL2 REQUIRED)
  include_directories(${SDL2_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE} ${SDL2_LIBRARY})
endif()

if(${IS_SIM})
  # My example project includes (Change this for your own project)
  target_include_directories(${EXECUTABLE} PRIVATE ${DEMO_DIR})
  target_include_directories(${EXECUTABLE} PRIVATE ${DEMO_DIR}/lv_examples/)
endif()

if(${IS_SIM})
  # My lvgl driver includes
  target_include_directories(${EXECUTABLE} PRIVATE ${LVDRV_DIR})
endif()


# Main lvgl lib includes
# for now sim only
if(${IS_SIM})
  target_include_directories(${EXECUTABLE} PRIVATE ${LVGL_DIR}/src/)
  target_include_directories(${EXECUTABLE} PRIVATE ${LVGL_DIR}/../)
endif()

if(${IS_SIM})
  target_include_directories(${EXECUTABLE} PRIVATE ${SIM_CATALINA_DIR})
endif()
if(${IS_STM32F3DISC})
  target_include_directories(${EXECUTABLE} PRIVATE ${F3_DISCO_DIR})
  target_include_directories(${EXECUTABLE} PRIVATE ${CUBEMX_INCLUDE_DIRECTORIES})
endif()

target_include_directories(${EXECUTABLE} PRIVATE ${PROJECT_DIR})
target_include_directories(${EXECUTABLE} PRIVATE ${MICRO_BITCOIN_DIR}/utility/trezor)

target_compile_features(firmware PUBLIC cxx_std_20)

# custom for the builds to embedded
if(${IS_STM32F3DISC})
  target_compile_definitions(${EXECUTABLE} PRIVATE
      ${MCU_MODEL}
      USE_HAL_DRIVER)

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


endif()