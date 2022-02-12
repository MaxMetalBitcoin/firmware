# sh scripts/inside_docker/cmake_and_build_simcatalina.sh
echo "hi"
mkdir -p build-ninja/SimCatalina
cd build-ninja/SimCatalina
cmake ../.. -GNinja -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_TOOLCHAIN_FILE=../../toolchains/sim_catalina.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true
cmake --build .
