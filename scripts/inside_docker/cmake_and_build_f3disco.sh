echo "hi"
mkdir -p build/DebugF3Disco
cd build/DebugF3Disco
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../toolchains/gcc-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true
make
