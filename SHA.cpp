#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

void sha1_transform(uint32_t state[5], const unsigned char buffer[SHA1_BLOCK_SIZE]) {
    uint32_t a, b, c, d, e, temp, i;
    uint32_t w[80];
    const uint32_t k[] = {
        0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6
    };

    
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];

    
    for (i = 0; i < 16; ++i) {
        w[i] = (buffer[i * 4] << 24) | (buffer[i * 4 + 1] << 16) | (buffer[i * 4 + 2] << 8) | buffer[i * 4 + 3];
    }

    
    for (i = 16; i < 80; ++i) {
        w[i] = (w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]);
        w[i] = (w[i] << 1) | (w[i] >> 31);
    }

    
    for (i = 0; i < 80; ++i) {
        if (i < 20) {
            temp = (a << 5) + ((b & c) | ((~b) & d)) + e + w[i] + k[0];
        } else if (i < 40) {
            temp = (a << 5) + (b ^ c ^ d) + e + w[i] + k[1];
        } else if (i < 60) {
            temp = (a << 5) + ((b & c) | (b & d) | (c & d)) + e + w[i] + k[2];
        } else {
            temp = (a << 5) + (b ^ c ^ d) + e + w[i] + k[3];
        }

        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = temp;
    }

  
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}

void sha1(const char *message, unsigned char digest[SHA1_DIGEST_SIZE]) {
    uint32_t state[5];
    uint64_t message_length;
    unsigned char buffer[SHA1_BLOCK_SIZE];
    int i;

    state[0] = 0x67452301;
    state[1] = 0xEFCDAB89;
    state[2] = 0x98BADCFE;
    state[3] = 0x10325476;
    state[4] = 0xC3D2E1F0;

    message_length = strlen(message);

    int chunk_count = (message_length + 9) / 64 + 1;
    uint64_t total_length = message_length * 8;

    for (i = 0; i < chunk_count * 64; ++i) {
        if (i < message_length) {
            buffer[i] = message[i];
        } else if (i == message_length) {
            buffer[i] = 0x80;
        } else {
            buffer[i] = 0;
        }
    }

   
    buffer[chunk_count * 64 - 8] = (total_length >> 56) & 0xFF;
    buffer[chunk_count * 64 - 7] = (total_length >> 48) & 0xFF;
    buffer[chunk_count * 64 - 6] = (total_length >> 40) & 0xFF;
    buffer[chunk_count * 64 - 5] = (total_length >> 32) & 0xFF;
    buffer[chunk_count * 64 - 4] = (total_length >> 24) & 0xFF;
    buffer[chunk_count * 64 - 3] = (total_length >> 16) & 0xFF;
    buffer[chunk_count * 64 - 2] = (total_length >> 8) & 0xFF;
    buffer[chunk_count * 64 - 1] = total_length & 0xFF;

    for (i = 0; i < chunk_count; ++i) {
        sha1_transform(state, &buffer[i * 64]);
    }

    for (i = 0; i < SHA1_DIGEST_SIZE; ++i) {
        digest[i] = (state[i >> 2] >> ((3 - (i & 3)) * 8)) & 0xFF;
    }
}

int main() {
    char input[100];
    printf("Enter string to hash: ");
    scanf("%s", input);

    unsigned char hash[SHA1_DIGEST_SIZE];
    sha1(input, hash);

    printf("SHA1(\"%s\") = ", input);
    for (int i = 0; i < SHA1_DIGEST_SIZE; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
