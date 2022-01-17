cd Builds/DebugF3Disco
cmake -DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true
make
