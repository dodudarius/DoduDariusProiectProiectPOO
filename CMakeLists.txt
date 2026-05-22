cmake_minimum_required(VERSION 3.10)
project(SistemMonitorizareDepozit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sursa
set(SRCS src/Produs.cpp src/Depozit.cpp src/Furnizor.cpp)
set(HEADERS include/Produs.h include/Depozit.h include/Exceptii.h include/Tranzactie.h include/Furnizor.h)

# Include directory
include_directories(include)

# Executabil Principal
add_executable(depozit src/main.cpp ${SRCS} ${HEADERS})

# Executabil Teste
add_executable(teste tests/test_main.cpp ${SRCS} ${HEADERS})
