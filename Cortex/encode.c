#include "encode.h"

// Función para calcular el máximo común divisor (GCD)
unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Función para calcular (base^exponent) % modulus de manera eficiente
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus)
{
    unsigned long long result = 1;
    base %= modulus;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Función para generar claves RSA de 16 bits
void generateRSAKeys(unsigned long long *publicKey, unsigned long long *privateKey, unsigned long long *n)
{
    unsigned long long p, q, phi, e, d;

    // Elegir dos números primos p y q (16 bits cada uno)
    p = 251;
    q = 239;

    // Calcular n y phi(n)
    *n = p * q;
    phi = (p - 1) * (q - 1);

    // Elegir un número e coprimo con phi(n) (16 bits)
    e = 65521;

    // Calcular d, el inverso multiplicativo de e modulo phi(n)
    d = 1;
    while (1)
    {
        if ((d * e) % phi == 1)
            break;
        d++;
    }

    *publicKey = e;
    *privateKey = d;
}

// Función para cifrar un valor utilizando RSA
unsigned long long encrypt(unsigned long long plaintext, unsigned long long publicKey, unsigned long long n)
{
    return mod_pow(plaintext, publicKey, n);
}

// Función para descifrar un valor utilizando RSA
unsigned long long decrypt(unsigned long long ciphertext, unsigned long long privateKey, unsigned long long n)
{
    return mod_pow(ciphertext, privateKey, n);
}

int encode()
{
    unsigned long long publicKey, privateKey, n;

    // Generar claves RSA de 16 bits
    generateRSAKeys(&publicKey, &privateKey, &n);
    printf("Public key (e): %llu\n", publicKey);
    printf("Private key (d): %llu\n", privateKey);
    printf("Modulo (n): %llu\n", n);

    // Ruta del archivo de texto original
    const char *inputFilePath = "images/image.txt";
    // Ruta del archivo de texto cifrado
    const char *outputFilePath = "images/encoded.txt";

    // Leer el archivo de texto original
    FILE *inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL)
    {
        perror("Error opening the base file.");
        return 1;
    }

    // Crear el archivo de texto cifrado
    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL)
    {
        perror("Error opening the encoded file.");
        fclose(inputFile);
        return 1;
    }

    // Leer el contenido del archivo de texto original y cifrarlo
    char buffer[1024];
    unsigned long long plaintext;
    int isFirstValue = 1; // Para evitar agregar una coma antes del primer valor
    int counter = 1;
    while (fscanf(inputFile, "%llu,", &plaintext) != EOF)
    {
        // Cifrar el valor
        unsigned long long ciphertext = encrypt(plaintext, publicKey, n);

        // Imprimir y escribir el valor cifrado en el archivo de salida
        if (isFirstValue)
        {
            isFirstValue = 0;
        }
        else
        {
            fprintf(outputFile, ",");
        }
        if (counter <= 2)
        {
            fprintf(outputFile, "%llu", plaintext);
            counter = counter + 1;
        }
        else
        {
            fprintf(outputFile, "%llu", ciphertext);
        }
    }

    // Cerrar los archivos
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
