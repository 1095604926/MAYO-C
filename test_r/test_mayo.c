// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <randombytes.h>
#include <mayo.h>
#include <stdalign.h>

static void print_hex(const unsigned char *hex, int len) {
    for (int i = 0; i < len;  ++i) {
        printf("%02x", hex[i]);
    }
    printf("\n");
}

static int test_mayo(const mayo_params_t *p) {
    unsigned char _pk[CPK_BYTES_MAX + 1] = {0};  
    unsigned char _sk[CSK_BYTES_MAX + 1] = {0};
    unsigned char _sig[SIG_BYTES_MAX + 32 + 1] = {0};
    unsigned char _msg[32+1] = { 0 };

    // Enforce unaligned memory addresses
    unsigned char *pk  = (unsigned char *) ((uintptr_t)_pk | (uintptr_t)1);
    unsigned char *sk  = (unsigned char *) ((uintptr_t)_sk | (uintptr_t)1);
    unsigned char *sig = (unsigned char *) ((uintptr_t)_sig | (uintptr_t)1);
    unsigned char *msg = (unsigned char *) ((uintptr_t)_msg | (uintptr_t)1);

    for (int i = 0; i < 32; i++) {
        msg[i] = i;
    }

    unsigned char seed[48] = { 0 };
    size_t msglen = 32;

    randombytes_init(seed, NULL, 256);

    printf("Testing Keygen, Sign, Open: %s\n", PARAM_name(p));

    int res = mayo_keypair(p, pk, sk);
    if (res != MAYO_OK) {
        res = -1;
        printf("keygen failed!\n");
        goto err;
    }


    size_t smlen = PARAM_sig_bytes(p) + 32;

    res = mayo_sign(p, sig, &smlen, msg, 32, sk);
    if (res != MAYO_OK) {
        res = -1;
        printf("sign failed!\n");
        goto err;
    }

    printf("pk: ");
    print_hex(pk, PARAM_cpk_bytes(p));
    printf("sk: ");
    print_hex(sk, PARAM_csk_bytes(p));
    printf("sm: ");
    print_hex(sig, smlen);


    res = mayo_open(p, msg, &msglen, sig, smlen, pk);
    if (res != MAYO_OK) {
        res = -1;
        printf("verify failed!\n");
        goto err;
    }

    printf("verify success!\n");

    sig[0] = ~sig[0];
    res = mayo_open(p, msg, &msglen, sig, smlen, pk);
    if (res != MAYO_ERR) {
        res = -1;
        printf("wrong signature still verified!\n");
        goto err;
    } else {
        res = MAYO_OK;
    }

err:
    return res;
}

int main(int argc, char *argv[]) {
    int rc = 0;

#ifdef ENABLE_PARAMS_DYNAMIC
    printf("ENABLE_PARAMS_DYNAMIC = ON\n");
    rc = test_mayo(&MAYO_VARIANT);
#else
    printf("ENABLE_PARAMS_DYNAMIC = OFF\n");
    rc = test_mayo(NULL);
#endif

    if (rc != MAYO_OK) {
        printf("test failed for %s\n", argv[1]);
    }
    return rc;
}

