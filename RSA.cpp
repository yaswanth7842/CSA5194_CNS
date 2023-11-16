#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int num) {
    int i;
    for (i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int generatePrime() {
    int num = rand() % 100 + 50;
    while (!isPrime(num)) {
        num++;
    }
    return num;
}

int calculatePublicKey(int phi) {
    int e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) {
            return e;
        }
        e++;
    }
    return -1; // Error, couldn't find public key
}

int calculatePrivateKey(int e, int phi) {
    int d = 1;
    while ((d * e) % phi != 1 || d == e) {
        d++;
    }
    return d;
}

int modPow(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    int p, q, n, phi, e, d, message, encrypted, decrypted;

    // Generate two random prime numbers
    srand(time(NULL));
    p = generatePrime();
    q = generatePrime();

    n = p * q;
    phi = (p - 1) * (q - 1);

    e = calculatePublicKey(phi);
    d = calculatePrivateKey(e, phi);

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    printf("Enter a message to encrypt: ");
    scanf("%d", &message);

    // Encryption
    encrypted = modPow(message, e, n);
    printf("Encrypted message: %d\n", encrypted);

    // Decryption
    decrypted = modPow(encrypted, d, n);
    printf("Decrypted message: %d\n", decrypted);

    return 0;
}
