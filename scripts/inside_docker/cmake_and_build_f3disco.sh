echo "hi"
mkdir -p build-ninja/DebugF3Disco
cd build-ninja/DebugF3Disco
cmake ../.. -GNinja -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_TOOLCHAIN_FILE=../../toolchains/gcc-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true
cmake --build .
