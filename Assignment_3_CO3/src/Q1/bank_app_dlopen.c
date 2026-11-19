#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

typedef const char *(*ver_fn_t)(void);
typedef uint64_t (*enc_fn_t)(uint64_t, uint64_t);

int main(int argc, char *argv[]) {
    const char *so_path = (argc > 1) ? argv[1] : "./libcrypto_bank.so";
    void *handle = dlopen(so_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "[SECURITY ALERT] dlopen() failed: %s\n", dlerror());
        return 2;
    }
    ver_fn_t get_ver = (ver_fn_t)(uintptr_t)dlsym(handle, "crypto_version");
    enc_fn_t encrypt = (enc_fn_t)(uintptr_t)dlsym(handle, "aes256_encrypt_block");
    printf("[dlopen] Loaded %s\n", get_ver());
    printf("[Transaction] Ciphertext = 0x%016llx\n",
           (unsigned long long)encrypt(409102ULL, 0xA5A5F0F012345678ULL));
    dlclose(handle);
    return 0;
}
