cmake_minimum_required(VERSION 3.10)
project(bitocen)


set(SOURCES
        CryptoHelper.cpp
        openFHE/KeysGenerator.cpp
        openFHE/CryptoContext.cpp
        openFHE/KeyPair.cpp
        openFHE/PlainText.cpp
        openFHE/Ciphertext.cpp
        openFHE/PublicKey.cpp
        openFHE/SecretKey.cpp
        openFHE/RecryptKey.cpp
)

add_library(crypto STATIC ${SOURCES})


#target_link_libraries(crypto PUBLIC )
target_link_libraries (crypto PUBLIC OPENFHEpke OPENFHEcore OPENFHEbinfhe)

#add_dependencies(crypto OPENFHEpke)
