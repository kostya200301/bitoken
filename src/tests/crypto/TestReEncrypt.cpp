//
// Created by Константин Беляков on 22.11.2024.
//
#include "catch2/catch.hpp"
extern "C" {

#include "ecc.h"
#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void ecc_pre_schema1_re_encrypt_test() {

    // client A setup public/private keys and signing keys
    byte_t pkA[ecc_pre_schema1_PUBLICKEYSIZE];
    byte_t skA[ecc_pre_schema1_PRIVATEKEYSIZE];
    byte_t spkA[ecc_pre_schema1_SIGNINGPUBLICKEYSIZE];
    byte_t sskA[ecc_pre_schema1_SIGNINGPRIVATEKEYSIZE];
    ecc_pre_schema1_KeyGen(pkA, skA);
    ecc_pre_schema1_SigningKeyGen(spkA, sskA);

    // client B setup public/private keys and signing keys
    byte_t pkB[ecc_pre_schema1_PUBLICKEYSIZE];
    byte_t skB[ecc_pre_schema1_PRIVATEKEYSIZE];
    byte_t spkB[ecc_pre_schema1_SIGNINGPUBLICKEYSIZE];
    byte_t sskB[ecc_pre_schema1_SIGNINGPRIVATEKEYSIZE];
    ecc_pre_schema1_KeyGen(pkB, skB);
    ecc_pre_schema1_SigningKeyGen(spkB, sskB);

    // proxy server setup signing keys
    byte_t spkSrv[ecc_pre_schema1_SIGNINGPUBLICKEYSIZE];
    byte_t sskSrv[ecc_pre_schema1_SIGNINGPRIVATEKEYSIZE];
    ecc_pre_schema1_SigningKeyGen(spkSrv, sskSrv);

    // client A select a plaintext message, this message
    // in itself is random, but can be used as a seed
    // for symmetric encryption keys
    byte_t m[ecc_pre_schema1_MESSAGESIZE];
    ecc_pre_schema1_MessageGen(m);

    // client A encrypts the message to itself, making it
    // possible to send this ciphertext to the proxy.
    byte_t C_A[ecc_pre_schema1_CIPHERTEXTLEVEL1SIZE];
    ecc_pre_schema1_Encrypt(
            C_A,
            m,
            pkA,
            spkA,
            sskA
    );

    // client A sends C_A to the proxy server and eventually client A
    // allows client B to see the encrypted message, in this case the
    // proxy needs to re-encrypt C_A (without ever knowing the plaintext).
    // In order to do that, the client A needs to create a re-encryption
    // key that the proxy can use to perform such operation.

    // client A creates a re-encryption key that the proxy can use
    // to re-encrypt the ciphertext (C_A) in order for client B be
    // able to recover the original message
    byte_t tk_A_B[ecc_pre_schema1_REKEYSIZE];
    ecc_pre_schema1_ReKeyGen(
            tk_A_B,
            skA,
            pkB,
            spkA,
            sskA
    );

    // the proxy re-encrypt the ciphertext C_A with such a key that
    // allows client B to recover the original message
    byte_t C_B[ecc_pre_schema1_CIPHERTEXTLEVEL2SIZE];
    int r1 = ecc_pre_schema1_ReEncrypt(
            C_B,
            C_A,
            tk_A_B,
            spkA,
            pkB,
            spkSrv,
            sskSrv
    );
//    assert_int_equal(r1, 0);
    CHECK(r1 == 0);


    // client B is able to decrypt C_B and the result is the original
    // plaintext message
    byte_t mB[ecc_pre_schema1_MESSAGESIZE];
    int r = ecc_pre_schema1_DecryptLevel2(
            mB,
            C_B,
            skB,
            spkSrv
    );
//    assert_int_equal(r, 0);
    CHECK(r == 0);

    // now both client A and client B share the same plaintext message
//    assert_memory_equal(mB, m, ecc_pre_schema1_MESSAGESIZE);
}

TEST_CASE("Test re-encrypt", "[crypto][unit][coverage]") {
    ecc_pre_schema1_re_encrypt_test();
}

};