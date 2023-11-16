#include <stdio.h>
#include <stdint.h>


#define N 16
#define MAX_KEY_LEN 56

typedef uint32_t word;
typedef uint8_t byte;


typedef struct {
    word P[N + 2];
    word S[4][256];
} blowfish_context;


void blowfish_init(blowfish_context *ctx, const byte *key, size_t keylen) {
 
}

void blowfish_encrypt_block(blowfish_context *ctx, const byte *in, byte *out) {
    word left = *(word *)in;
    word right = *((word *)in + 1);

    for (int i = 0; i < 16; ++i) {
        left ^= ctx->P[i];
        right ^= ctx->P[i + 1];
    }

    *(word *)out = left;
    *((word *)out + 1) = right;
}


void blowfish_decrypt_block(blowfish_context *ctx, const byte *in, byte *out) {
    
    blowfish_encrypt_block(ctx, in, out);
}

int main() {
    blowfish_context ctx;
    byte key[MAX_KEY_LEN] = {0x12, 0x34, 0x56, 0x78}; 
    byte plaintext[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    byte encrypted[8], decrypted[8];

    blowfish_init(&ctx, key, sizeof(key));

    printf("Original plaintext block: ");
    for (int i = 0; i < 8; ++i) {
        printf("%02x ", plaintext[i]);
    }
    printf("\n");

    blowfish_encrypt_block(&ctx, plaintext, encrypted);

    printf("Encrypted block: ");
    for (int i = 0; i < 8; ++i) {
        printf("%02x ", encrypted[i]);
    }
    printf("\n");

    blowfish_decrypt_block(&ctx, encrypted, decrypted);

    printf("Decrypted block: ");
    for (int i = 0; i < 8; ++i) {
        printf("%02x ", decrypted[i]);
    }
    printf("\n");

    return 0;
}
