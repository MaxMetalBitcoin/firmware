# sh scripts/inside_docker/cmake_and_build_simcatalina.sh
echo "hi"
mkdir -p build/SimCatalina
cd build/SimCatalina
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../toolchains/sim_catalina.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true
cmake --build .
