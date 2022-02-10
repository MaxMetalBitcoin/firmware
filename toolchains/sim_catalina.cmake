# set(CMAKE_SYSTEM_NAME Mac)

# Some default GCC settings
set(FLAGS
    "")
set(CPP_FLAGS
    "")

set(CMAKE_C_COMPILER gcc ${FLAGS})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER g++ ${FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY objcopy)
set(CMAKE_SIZE size)

# set the config of which target
set(IS_SIM true)
set(IS_STM32F3DISC false)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
