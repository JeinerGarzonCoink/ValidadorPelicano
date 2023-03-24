g++ -c ../ValidatorPelicano.cpp -o ValidatorPelicano.o

cmake -S . -B build

cmake --build build

cd build && ctest