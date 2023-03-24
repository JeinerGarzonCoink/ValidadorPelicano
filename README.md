#!/bin/bash

# Compilar archivos en C++
g++ -o main main.cpp StateMachine.cpp ValidatorPelicano.cpp -I/home/coink/Documents/ValidadorPelicano/Oink-Validator-Pelicano-main/Pelicano/spdlog/include/

# Correr main
./main