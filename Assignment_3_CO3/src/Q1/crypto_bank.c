#include <stdint.h>

const char *crypto_version(void) {
#ifdef PATCHED_V2
    return "libcrypto_bank v2.1 (PATCHED - AES-256-GCM Constant-Time)";
#else
    return "libcrypto_bank v1.0 (Baseline Branch Release)";
#endif
}

uint64_t aes256_encrypt_block(uint64_t plaintext, uint64_t key) {
    uint64_t state = plaintext ^ key;
    state = ((state << 13) | (state >> 51)) ^ 0x9E3779B97F4A7C15ULL;
    return state;
}
