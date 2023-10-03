#ifndef ENCODE_H
#define ENCODE_H

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

unsigned long long gcd(unsigned long long a, unsigned long long b);
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus);
void generateRSAKeys(unsigned long long *publicKey, unsigned long long *privateKey, unsigned long long *n);
unsigned long long encrypt(unsigned long long plaintext, unsigned long long publicKey, unsigned long long n);
unsigned long long decrypt(unsigned long long ciphertext, unsigned long long privateKey, unsigned long long n);
int encode();

#endif