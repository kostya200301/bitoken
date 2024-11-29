cmake_minimum_required(VERSION 3.10)
project(bitocen)


set(SOURCES
        CryptoHelper.cpp
        openFHE/KeysGenerator.cpp
        openFHE/CryptoContext.cpp
)

add_library(crypto STATIC ${SOURCES})

message("FFFFFF: ${PKELIBS}") # PUBLIC;OPENFHEpke;PUBLIC;OPENFHEcore;PUBLIC;OPENFHEbinfhe;-Xpreprocessor -fopenmp -lomp -Wno-unused-command-line-argument

#target_link_libraries(crypto PUBLIC )
target_link_libraries (crypto PUBLIC OPENFHEpke OPENFHEcore OPENFHEbinfhe)

#add_dependencies(crypto OPENFHEpke)
