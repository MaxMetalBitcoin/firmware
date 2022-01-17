# sh scripts/inside_docker/cmake_and_build_simcatalina.sh


cd Builds/SimCatalina
cmake -DCMAKE_TOOLCHAIN_FILE=sim_catalina.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true
make
