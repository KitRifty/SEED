
#include <iostream>
#include <vector>
#include <assert.h>
#include "seed.h"

void test_seed(unsigned* key, unsigned* iv, const char* plaintext, size_t plaintextSize, const char* ciphertext)
{
    SEED seed;
    size_t bytesWritten;
    char* encrypted;
    char* decrypted;

    seed.Encrypt(plaintext, sizeof(plaintext), NULL, 0, &bytesWritten);

    encrypted = new char[bytesWritten];
    decrypted = new char[bytesWritten];
    seed.Initialize(key, iv);
    seed.Encrypt(plaintext, plaintextSize, encrypted, bytesWritten, &bytesWritten);

    for (int i = 0; i < bytesWritten; i++) {
        assert(encrypted[i] == ciphertext[i]);
    }

    seed.Initialize(key, iv);
    seed.Decrypt(encrypted, bytesWritten, decrypted, bytesWritten, &bytesWritten);

    for (int i = 0; i < plaintextSize; i++) {
        assert(decrypted[i] == plaintext[i]);
    }

    delete[] encrypted;
    delete[] decrypted;
}

int main()
{
    unsigned vec_key[4];

    vec_key[0] = 0;
    vec_key[1] = 0;
    vec_key[2] = 0;
    vec_key[3] = 0;

    char plaintext_b1[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
    char ciphertext_b1[] = { 0x5E, 0xBA, 0xC6, 0xE0, 0x05, 0x4E, 0x16, 0x68, 0x19, 0xAF, 0xF1, 0xCC, 0x6D, 0x34, 0x6C, 0xDB };

    test_seed(vec_key, NULL, plaintext_b1, sizeof(plaintext_b1), ciphertext_b1);

    vec_key[0] = 0x03020100;
    vec_key[1] = 0x07060504;
    vec_key[2] = 0x0b0a0908;
    vec_key[3] = 0x0f0e0d0c;

    char plaintext_b2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    char ciphertext_b2[] = { 0xC1, 0x1F, 0x22, 0xF2, 0x01, 0x40, 0x50, 0x50, 0x84, 0x48, 0x35, 0x97, 0xE4, 0x37, 0x0F, 0x43 };

    test_seed(vec_key, NULL, plaintext_b2, sizeof(plaintext_b2), ciphertext_b2);

    vec_key[0] = 0x08480647;
    vec_key[1] = 0xe81be651;
    vec_key[2] = 0xb3bf745d;
    vec_key[3] = 0x856195fd;

    char plaintext_b3[] = { 0x83, 0xA2, 0xF8, 0xA2, 0x88, 0x64, 0x1F, 0xB9, 0xA4, 0xE9, 0xA5, 0xCC, 0x2F, 0x13, 0x1C, 0x7D };
    char ciphertext_b3[] = { 0xEE, 0x54, 0xD1, 0x3E, 0xBC, 0xAE, 0x70, 0x6D, 0x22, 0x6B, 0xC3, 0x14, 0x2C, 0xD4, 0x0D, 0x4A };

    test_seed(vec_key, NULL, plaintext_b3, sizeof(plaintext_b3), ciphertext_b3);

    vec_key[0] = 0xbcc3db28;
    vec_key[1] = 0x7dd8ff49;
    vec_key[2] = 0xb109a5cf;
    vec_key[3] = 0xe72b421d;

    char plaintext_b4[] = { 0xB4, 0x1E, 0x6B, 0xE2, 0xEB, 0xA8, 0x4A, 0x14, 0x8E, 0x2E, 0xED, 0x84, 0x59, 0x3C, 0x5E, 0xC7 };
    char ciphertext_b4[] = { 0x9B, 0x9B, 0x7B, 0xFC, 0xD1, 0x81, 0x3C, 0xB9, 0x5D, 0x0B, 0x36, 0x18, 0xF4, 0x0F, 0x51, 0x22 };

    test_seed(vec_key, NULL, plaintext_b4, sizeof(plaintext_b4), ciphertext_b4);

    return 0;
}